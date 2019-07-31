
#include "utils/message.h"

#include "helpers/json.h"
#include "identities/keys.hpp"
#include "utils/hex.hpp"

Ark::Crypto::Utils::Message::Message(
    std::string msg,
    PublicKey pubKey,
    std::vector<uint8_t> sig)
    : message(std::move(msg)),
      publicKey(std::move(pubKey)),
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
  const auto hash = Sha256::getHash(unsignedMessage, this->message.length());

  /* Sign it */
  cryptoSign(hash, PrivateKey(keys.privateKey), this->signature);

  return this->verify();
};

/**/

bool Ark::Crypto::Utils::Message::verify() {
  // cast message to unsigned char*
  const auto unsignedMessage = reinterpret_cast<const unsigned char *>(
      this->message.c_str());
  const auto hash = Sha256::getHash(unsignedMessage, this->message.length());

  return cryptoVerify(this->publicKey, hash, this->signature);
};

/**/

std::map<std::string, std::string> Ark::Crypto::Utils::Message::toArray() {
  return {
    { "publickey", this->publicKey.toString() },
    { "signature", BytesToHex(this->signature.begin(), this->signature.end()) },
    { "message", this->message }
  };
}

/**/

std::string Ark::Crypto::Utils::Message::toJson() {
  std::map<std::string, std::string> messageArray = this->toArray();

  const size_t docLength
      = (33 + 1)  // publickey length
      + (72 + 1)  // signature length
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
