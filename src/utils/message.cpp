/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "utils/message.h"

/**
 * @brief Create a message object for checking its validity.
 *
 * @param std::string msg
 * @param PublicKey pubKey
 * @param std::vector<uint8_t> sig
 **/
Ark::Crypto::Utils::Message::Message(std::string msg, PublicKey pubKey, std::vector<uint8_t> sig)
    : message(msg), publicKey(pubKey), signature(sig){};
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
  const auto unsignedMessage =
      reinterpret_cast<const unsigned char *>(this->message.c_str());  // cast message to unsigned char*
  const auto hash = Sha256::getHash(unsignedMessage, this->message.length());

  return cryptoVerify(this->publicKey, hash, this->signature);
};
/**/

/**
 * @brief Convert the message to its array representation using an array of pairs
 *
 * ' messageArray[0].first: "publickey" '
 * ' messageArray[0].second: uint8_t* (ex: { 2, 159, 223 ... 253, 151, 180 })
    };) '
 *
 * @return std::vector< std::pair<const char *const, std::string> >
 **/
std::vector<std::pair<const char *const, std::string>> Ark::Crypto::Utils::Message::toArray() {
  return {{"publickey", this->publicKey.toString().c_str()},
          {"signature", BytesToHex(&this->signature[0], &this->signature[0] + this->signature.size())},
          {"message", this->message}};
};
/**/

/**
 * @brief Convert the message to its JSON representation.
 *
 * @return std::string
 **/
std::string Ark::Crypto::Utils::Message::toJson() {
  const auto messageArray = this->toArray();

  std::string messageJsonString;
  messageJsonString += "{\"";
  messageJsonString += messageArray[0].first;
  messageJsonString += "\":\"";

  messageJsonString += messageArray[0].second;

  messageJsonString += "\",\"";
  messageJsonString += messageArray[1].first;
  messageJsonString += "\":\"";

  messageJsonString += messageArray[1].second;

  messageJsonString += "\",\"";
  messageJsonString += messageArray[2].first;
  messageJsonString += "\":\"";

  messageJsonString += messageArray[2].second;

  messageJsonString += "\"}";

  return messageJsonString;
}
/**/

/**
 * @brief Convert the message to its String representation.
 *
 * @return std::string
 **/
std::string Ark::Crypto::Utils::Message::toString() {
  return this->toJson();
};
/**/
