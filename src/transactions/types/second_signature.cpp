/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/second_signature.hpp"

#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <utility>

#include "interfaces/constants.h"

#include "utils/hex.hpp"
#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Second Signature Registration (Type 1) - 33 Bytes
//
// @param SecondSignature *registration
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Second PublicKey - 33 Bytes:
// - std::move(buffer, buffer + 33, registration->publicKey);
//
// ---
auto SecondSignature::Deserialize(SecondSignature *registration,
                                  const uint8_t *buffer) -> size_t {
    std::move(buffer,
              buffer + PUBLICKEY_COMPRESSED_LEN,
              registration->publicKey.begin());  

    return PUBLICKEY_COMPRESSED_LEN;                             // 33 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Second Signature Registration (Type 1) - 33 Bytes
//
// @param const SecondSignature &registration
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Second PublicKey - 33 Bytes:
// - std::move(registration.publicKey.begin(), registration.publicKey.end(), buffer);
//
// ---
auto SecondSignature::Serialize(const SecondSignature &registration,
                                uint8_t *buffer) -> size_t {
    std::move(registration.publicKey.begin(),
              registration.publicKey.end(),
              buffer);

    return PUBLICKEY_COMPRESSED_LEN;                             // 33 Bytes
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
const auto KEY_SIGNATURE_LABEL      = "signature";
const auto KEY_SIGNATURE_SIZE       = strlen(KEY_SIGNATURE_LABEL);

const auto KEY_PUBLICKEY_LABEL      = "publicKey";
const auto KEY_PUBLICKEY_SIZE       = strlen(KEY_PUBLICKEY_LABEL);

////////////////////////////////////////////////////////////////////////////////
// Add SecondSignature Asset data to a Transaction Map.
void SecondSignature::addToMap(const SecondSignature &registration,
                               std::map<std::string, std::string> &map) {
    // Second Signature PublicKey
    map.emplace(KEY_PUBLICKEY_LABEL, BytesToHex(registration.publicKey));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a SecondSignature-type Transaction.
auto SecondSignature::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1) + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1) + KEY_SIGNATURE_SIZE +
           JSON_OBJECT_SIZE(1) +
                KEY_PUBLICKEY_SIZE + PUBLICKEY_COMPRESSED_STR_LEN;
}

////////////////////////////////////////////////////////////////////////////////
// Add SecondSignature data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain SecondSignature data.
//
// ---
void SecondSignature::addToJson(DynamicJsonDocument &jsonDoc,
                                const std::map<std::string, std::string> &map) {
    const auto asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    const auto secondSig = asset.createNestedObject(KEY_SIGNATURE_LABEL);

    // PublicKey
    secondSig[KEY_PUBLICKEY_LABEL] = map.at(KEY_PUBLICKEY_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
