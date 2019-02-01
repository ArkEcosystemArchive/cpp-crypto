/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "utils/message.h"
#include "helpers/json.h"

/**
 * @brief Create a message object for checking its validity.
 *
 * @param std::string msg
 * @param PublicKey pubKey
 * @param std::vector<uint8_t> sig
 **/
Ark::Crypto::Utils::Message::Message(
    std::string msg,
    PublicKey pubKey,
    std::vector<uint8_t> sig)
    : message(msg),
      publicKey(pubKey),
      signature(sig){};
/**/

/**
 * @brief Sign a message using the given passphrase.
 *
 * @param string message
 * @param string passphrase
 *
 * @return bool
 **/
bool Ark::Crypto::Utils::Message::sign(std::string newMessage, const char *const passphrase) {
  this->message = newMessage;

  /* Get the PrivateKey */
  PrivateKey privateKey = Ark::Crypto::Identities::PrivateKey::fromPassphrase(passphrase);

  /* Set the PublicKey from the derived PrivateKey */
  this->publicKey = Ark::Crypto::Identities::PublicKey::fromPrivateKey(privateKey);

  /* Get the Hash */
  const auto unsignedMessage = reinterpret_cast<const unsigned char *>(message.c_str());
  const auto hash = Sha256::getHash(unsignedMessage, this->message.length());

  /* Sign it */
  cryptoSign(hash, privateKey, this->signature);

  return this->verify();
};
/**/

/**
 * @brief Verify the message contents.
 *
 * @return bool
 **/
bool Ark::Crypto::Utils::Message::verify() {
  // cast message to unsigned char*
  const auto unsignedMessage = reinterpret_cast<const unsigned char *>(this->message.c_str());
  const auto hash = Sha256::getHash(unsignedMessage, this->message.length());

  return cryptoVerify(this->publicKey, hash, this->signature);
};
/**/

/**
 * @brief Convert the message to its array representation using an array of pairs
 *
 * @return std::map<std::string, std::string>
 **/
std::map<std::string, std::string> Ark::Crypto::Utils::Message::toArray() {
  return {
    {"publickey", this->publicKey.toString()},
    {"signature", BytesToHex(this->signature.begin(), this->signature.end())},
    {"message", this->message}
  };
}
/**/

/**
 * @brief Convert the message to its JSON representation.
 *
 * @return std::string
 **/
std::string Ark::Crypto::Utils::Message::toJson() {
  std::map<std::string, std::string> messageArray = this->toArray();

  const size_t capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.createObject();

  root["publickey"] = messageArray["publickey"];
  root["signature"] = messageArray["signature"];
  root["message"] = messageArray["message"];

  char jsonChar[root.measureLength() + 1];
  root.printTo((char*)jsonChar, sizeof(jsonChar));

  return jsonChar;
}
/**/
