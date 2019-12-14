/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "crypto/message.hpp"

#include <algorithm>
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

////////////////////////////////////////////////////////////////////////////////
constexpr auto MESSAGE_KEY      = "message";
constexpr auto PUBLICKEY_KEY    = "publickey";
constexpr auto SIGNATURE_KEY    = "signature";

constexpr size_t MAGIC_JSON_SIZE       = 120;
constexpr size_t MAGIC_JSON_OBJ_SIZE   = 3;

////////////////////////////////////////////////////////////////////////////////
// Create an empty Message object for building and signing.
Message::Message() : publicKey() {
        signature.resize(SIGNATURE_ECDSA_MAX);
}

////////////////////////////////////////////////////////////////////////////////
// Create a Signed Message object for verification.
Message::Message(std::string message,
                 const uint8_t *publicKeyBytes,
                 const uint8_t *signature) : message(std::move(message)) {
    std::copy_n(publicKeyBytes,
                PUBLICKEY_COMPRESSED_LEN,
                this->publicKey.begin());

    this->signature.resize(signature[1] == 0U ? 0U : 2U + signature[1]);
    std::copy_n(signature,
                this->signature.size(),
                this->signature.begin());
}

////////////////////////////////////////////////////////////////////////////////
auto Message::sign(const std::string &message, const std::string &passphrase)
        -> bool {
    this->message = message;

    const auto keys = identities::Keys::fromPassphrase(passphrase.c_str());
    this->publicKey = keys.publicKey;

    const auto hash = Hash::sha256((uint8_t *)message.data(),
                                   this->message.size());

    return Curve::Ecdsa::sign(hash.data(),
                              keys.privateKey.data(),
                              &this->signature);
}

////////////////////////////////////////////////////////////////////////////////
// Verify a Signed Message object.
auto Message::verify() const -> bool {
    const auto hash = Hash::sha256((uint8_t *)this->message.data(),
                                   this->message.size());

    return Curve::Ecdsa::verify(hash.data(),
                                this->publicKey.data(),
                                this->signature);
}

////////////////////////////////////////////////////////////////////////////////
// Create a string map of the Signed Message objects.
auto Message::toMap() const -> std::map<std::string, std::string> {
    return {
        { MESSAGE_KEY, this->message },
        { PUBLICKEY_KEY, BytesToHex(this->publicKey) },
        { SIGNATURE_KEY, BytesToHex(this->signature) }
    };
}

////////////////////////////////////////////////////////////////////////////////
// Create a Json'ified string of the Signed Message.
auto Message::toJson() const -> std::string {
    auto messageArray = this->toMap();

    const size_t docLength = this->message.length() +
                             (PUBLICKEY_COMPRESSED_LEN + 1U) +  // + `/0` 
                             (this->signature.size() + 1U);     // + `/0` 
                            
    const size_t docCapacity = JSON_OBJECT_SIZE(MAGIC_JSON_OBJ_SIZE) +
                                                docLength +
                                                MAGIC_JSON_SIZE;
    DynamicJsonDocument doc(docCapacity);

    doc[MESSAGE_KEY]        = messageArray[MESSAGE_KEY];
    doc[PUBLICKEY_KEY]      = messageArray[PUBLICKEY_KEY];
    doc[SIGNATURE_KEY]      = messageArray[SIGNATURE_KEY];

    std::string jsonStr;
    jsonStr.reserve(docCapacity);
    serializeJson(doc, jsonStr);

    return jsonStr;
}

}  // namespace Crypto
}  // namespace Ark
