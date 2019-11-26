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
#include <map>
#include <string>
#include <utility>

#include "interfaces/constants.h"

#include "utils/hex.hpp"

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
// Return a Map of the Second Signature's PublicKey.
auto SecondSignature::getMap(const SecondSignature &registration)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Second Signature PublicKey
    map.emplace("publicKey", BytesToHex(registration.publicKey));

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
