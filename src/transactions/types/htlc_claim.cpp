/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/htlc_claim.hpp"

#include <cstdint>
#include <cstring>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "utils/hex.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

// Deserialize Htlc Claim (Type 8) - 64 Bytes
//
// @param HtlcClaim *claim
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Lock Transaction Id - 32 Bytes:
// - memmove(&claim.id, &buffer[0], 32);
//
// Unlock Secret - UTF-8 encoded - 32 Bytes
// - memmove(&claim.secret, &buffer[HASH_32_LEN], 32);
//
// ---
auto HtlcClaim::Deserialize(HtlcClaim *claim, const uint8_t *buffer) -> uint32_t {
    memmove(&claim->id, buffer, HASH_32_LEN);                       // 32 Bytes

    memmove(&claim->secret, &buffer[HASH_32_LEN], HASH_32_LEN);     // 32 Bytes

    return HASH_64_LEN;                                             // 64 Bytes
}

////////////////////////////////////////////////////////////////////////////////

// Serialize Htlc Claim (Type 8) - 64 Bytes
//
// @param const HtlcClaim &claim
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Lock Transaction Id - 32 Bytes:
// - memmove(buffer, &claim.id, 32);
//
// Unlock Secret - UTF-8 encoded - 32 Bytes
// - memmove(&buffer[32], &claim.secret, 32);
//
// ---
auto HtlcClaim::Serialize(const HtlcClaim &claim, uint8_t *buffer) -> uint32_t {
    memmove(buffer, claim.id.data(), HASH_32_LEN);                  // 32 Bytes

    memmove(&buffer[HASH_32_LEN],                                   // 32 Bytes
            claim.secret.data(),
            claim.secret.size());

    return HASH_64_LEN;                                             // 64 Bytes
}

////////////////////////////////////////////////////////////////////////////////

// Return a Map of the Htlc Claim asset.
auto HtlcClaim::getMap(const HtlcClaim &claim)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Id
    map.emplace("lockTransactionId", BytesToHex(claim.id));

    // Secret
    std::string secret(claim.secret.size(), '\0');
    secret.insert(secret.begin(), claim.secret.begin(), claim.secret.end());    
    map.emplace("unlockSecret", secret);

    return map;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
