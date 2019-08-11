
#include "utils/message.h"

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"
#include "helpers/json.h"
#include "identities/keys.hpp"
#include "utils/hex.hpp"

Ark::Crypto::Utils::Message::Message(
    std::string msg,
    const PublicKey& pubKey,
    std::vector<uint8_t> sig)
    : message(std::move(msg)),
      publicKey(pubKey),
      signature(std::move(sig)) {};

/**/

bool Ark::Crypto::Utils::Message::sign(
    std::string newMessage,
    const char *const passphrase) {
  this->message = std::move(newMessage);

  /* Get the KeyPair */
  const auto keys = Keys::fromPassphrase(passphrase);

  /* Set the PublicKey from the PrivateKey */
  this->publicKey = PublicKey(keys.publicKey);

  /* Get the Hash */
  const auto unsignedMessage = reinterpret_cast<const unsigned char *>(
      message.c_str());
  const auto hash = Ark::Crypto::Hash::sha256(unsignedMessage,
                                              this->message.size());

  /* Sign it */
  std::vector<uint8_t> buffer(Curve::Ecdsa::MAX_SIG_LEN);
  if (Ark::Crypto::Curve::Ecdsa::sign(hash.data(),
                                      keys.privateKey.data(),
                                      buffer)) {
    buffer.resize(buffer[1] + 2);
    this->signature = std::move(buffer);
  };

  return this->verify();
};

/**/

bool Ark::Crypto::Utils::Message::verify() const {
  // cast message to unsigned char*
  const auto unsignedMessage = reinterpret_cast<const unsigned char *>(
      this->message.c_str());
  const auto hash = Ark::Crypto::Hash::sha256(unsignedMessage,
                                              this->message.size());
  const auto pk = this->publicKey.toBytes();
  return Ark::Crypto::Curve::Ecdsa::verify(hash.data(),
                                           pk.data(),
                                           this->signature);
};

/**/

std::map<std::string, std::string> Ark::Crypto::Utils::Message::toArray() const {
  return {
    { "publickey", this->publicKey.toString() },
    { "signature", BytesToHex(this->signature.begin(), this->signature.end()) },
    { "message", this->message }
  };
}

/**/

std::string Ark::Crypto::Utils::Message::toJson() const {
  std::map<std::string, std::string> messageArray = this->toArray();

  const size_t docLength
      = (33 + 1)  // publickey length
      + (Curve::Ecdsa::MAX_SIG_LEN + 1)  // signature length
      + this->message.length();
  const size_t docCapacity = JSON_OBJECT_SIZE(3) + docLength + 120;

  DynamicJsonDocument doc(docCapacity);

  doc["publickey"] = messageArray["publickey"];
  doc["signature"] = messageArray["signature"];
  doc["message"] = messageArray["message"];

  std::string jsonStr;
  jsonStr.reserve(docCapacity);
  serializeJson(doc, &jsonStr[0], docCapacity);

  return jsonStr;
}
