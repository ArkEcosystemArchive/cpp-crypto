/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "crypto/message.hpp"

#include <map>
#include <string>
#include <vector>

#include "interfaces/identities.hpp"
#include "crypto/curve.hpp"
#include "crypto/hash.hpp"
#include "identities/keys.hpp"
#include "utils/hex.hpp"
#include "utils/json.h"

namespace Ark {
namespace Crypto {

namespace {
constexpr const char* MESSAGE_KEY    = "message";
constexpr const char* PUBLICKEY_KEY  = "publickey";
constexpr const char* SIGNATURE_KEY  = "signature";
constexpr size_t MAGIC_JSON_SIZE = 120U;
}  // namespace

// Create an empty Message object for building and signing.
Message::Message() : publicKey({}), signature(Curve::Ecdsa::MAX_SIG_LEN) {}

// Create a Signed Message object for verification.
Message::Message(std::string message,
                 const PublicKeyBytes& publicKeyBytes,
                 std::vector<uint8_t> signature)
                 : message(std::move(message)),
                   publicKey(publicKeyBytes),
                   signature(std::move(signature)) {};

bool Message::sign(const std::string& message, const std::string& passphrase) {
  this->message = message;

  const auto keys = identities::Keys::fromPassphrase(passphrase.c_str());
  this->publicKey = keys.publicKey;

  const auto messageBytes =
      reinterpret_cast<const unsigned char *>(message.c_str());
  const auto hash = Hash::sha256(messageBytes, this->message.size());

  std::vector<uint8_t> buffer(Curve::Ecdsa::MAX_SIG_LEN);
  if (!Curve::Ecdsa::sign(hash.data(), keys.privateKey.data(), buffer)) {
    return false;
  };

  buffer.resize(buffer[1] + 2);
  this->signature = std::move(buffer);

  return true;
}

// Verify a Signed Message object.
bool Message::verify() const {
  const auto messageBytes =
      reinterpret_cast<const unsigned char *>(this->message.c_str());
  const auto hash = Hash::sha256(messageBytes, this->message.size());

  return Curve::Ecdsa::verify(hash.data(),
                              this->publicKey.data(),
                              this->signature);
}

// Create a string map of the Signed Message objects.
std::map<std::string, std::string>
Message::toArray() const {
  return {
    { MESSAGE_KEY, this->message },
    { PUBLICKEY_KEY, BytesToHex(this->publicKey.begin(), this->publicKey.end()) },
    { SIGNATURE_KEY, BytesToHex(this->signature.begin(), this->signature.end()) }
  };
}

// Create a Json'ified string of the Signed Message.
std::string Message::toJson() const {
  std::map<std::string, std::string> messageArray = this->toArray();

  const size_t docLength = this->message.length() +
                           (PUBLICKEY_COMPRESSED_BYTE_LEN + 1) +  // + `/0` 
                           (Curve::Ecdsa::MAX_SIG_LEN + 1);       // + `/0` 
                           
  const size_t docCapacity = JSON_OBJECT_SIZE(3) + docLength + MAGIC_JSON_SIZE;
  DynamicJsonDocument doc(docCapacity);

  doc[MESSAGE_KEY] = messageArray[MESSAGE_KEY];
  doc[PUBLICKEY_KEY] = messageArray[PUBLICKEY_KEY];
  doc[SIGNATURE_KEY] = messageArray[SIGNATURE_KEY];

  std::string jsonStr;
  jsonStr.reserve(docCapacity);
  serializeJson(doc, &jsonStr[0], docCapacity);

  return jsonStr;
}

}  // namespace Crypto
}  // namespace Ark
