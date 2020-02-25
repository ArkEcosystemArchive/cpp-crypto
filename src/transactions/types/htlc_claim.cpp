/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/htlc_claim.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>

#include "interfaces/constants.h"

#include "utils/hex.hpp"
#include "utils/json.h"

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
// - std::copy_n(buffer, 32, claim->id.begin());
//
// Unlock Secret - UTF-8 encoded - 32 Bytes
// - std::copy_n(&buffer[32], 32, claim->secret.begin());
//
// ---
auto HtlcClaim::Deserialize(HtlcClaim *claim, const uint8_t *buffer) -> size_t {
    std::copy_n(buffer, HASH_32_LEN, claim->id.begin());            // 32 Bytes

    std::copy_n(&buffer[HASH_32_LEN],                               // 32 Bytes
                HASH_32_LEN,
                claim->secret.begin());

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
// - std::copy(claim.id.begin(), claim.id.end(), buffer);
//
// Unlock Secret - UTF-8 encoded - 32 Bytes
// - std::copy(claim.secret.begin(), claim.secret.end(), &buffer[32]);
//
// ---
auto HtlcClaim::Serialize(const HtlcClaim &claim, uint8_t *buffer) -> size_t {
    std::copy(claim.id.begin(), claim.id.end(), buffer);            // 32 Bytes

    std::copy(claim.secret.begin(),                                 // 32 Bytes
              claim.secret.end(),
              &buffer[HASH_32_LEN]);

    return HASH_64_LEN;                                             // 64 Bytes
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
constexpr auto OBJECT_HTLC_CLAIM_LABEL      = "claim";
constexpr size_t OBJECT_HTLC_CLAIM_SIZE     = 5;

constexpr auto KEY_CLAIM_TX_ID_LABEL        = "lockTransactionId";
constexpr size_t KEY_CLAIM_TX_ID_SIZE       = 17;

constexpr auto KEY_CLAIM_SECRET_LABEL       = "unlockSecret";
constexpr size_t KEY_CLAIM_SECRET_SIZE      = 11;

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Claim Asset data to a Transaction Map.
void HtlcClaim::addToMap(const HtlcClaim &claim,
                         std::map<std::string, std::string> &map) {
    // Id
    map.emplace(KEY_CLAIM_TX_ID_LABEL, BytesToHex(claim.id));

    // Secret
    map.emplace(KEY_CLAIM_SECRET_LABEL, BytesToHex(claim.secret));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Htlc Claim-type Transaction.
auto HtlcClaim::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1)  + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1)  + OBJECT_HTLC_CLAIM_SIZE +
           JSON_OBJECT_SIZE(1)  + KEY_CLAIM_TX_ID_SIZE  + HASH_32_MAX_CHARS +
           JSON_OBJECT_SIZE(1)  + KEY_CLAIM_SECRET_SIZE + HASH_32_MAX_CHARS;
}

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Claim data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Htlc Claim data.
//
// ---
void HtlcClaim::addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map) {
    const auto asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    const auto claim = asset.createNestedObject(OBJECT_HTLC_CLAIM_LABEL);

    // Lock Transaction Id
    claim[KEY_CLAIM_TX_ID_LABEL] = map.at(KEY_CLAIM_TX_ID_LABEL);

    // Unlock Secret
    claim[KEY_CLAIM_SECRET_LABEL] = map.at(KEY_CLAIM_SECRET_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
