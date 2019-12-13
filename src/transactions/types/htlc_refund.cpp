/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/htlc_refund.hpp"

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "utils/hex.hpp"
#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Htlc Refund (Type 10) - 32 Bytes
//
// @param HtlcRefund *refund
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Lock Transaction Id - 32 Bytes:
// - std::copy_n(buffer, 32, refund->id.begin());
// ---
auto HtlcRefund::Deserialize(HtlcRefund *refund, const uint8_t *buffer)
        -> size_t {
    refund->id = {};
    std::copy_n(buffer, HASH_32_LEN, refund->id.begin());           // 32 Bytes

    return HASH_32_LEN;
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Htlc Refund (Type 10) - 32 Bytes
//
// @param const HtlcRefund &refund
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Lock Transaction Id - 32 Bytes:
// - std::copy(refund.id.begin(), refund.id.end(), buffer);
//
// ---
auto HtlcRefund::Serialize(const HtlcRefund &refund, uint8_t *buffer)
        -> size_t {
    std::copy(refund.id.begin(), refund.id.end(), buffer);          // 32 Bytes

    return HASH_32_LEN;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
const auto OBJECT_HTLC_REFUND_LABEL = "refund";
const auto OBJECT_HTLC_REFUND_SIZE  = strlen(OBJECT_HTLC_REFUND_LABEL);

const auto KEY_REFUND_TX_ID_LABEL   = "lockTransactionId";
const auto KEY_REFUND_TX_ID_SIZE    = strlen(KEY_REFUND_TX_ID_LABEL);

const auto HTLC_JSON_OBJECT_SIZE = 1U;

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Refund Asset data to a Transaction Map.
void HtlcRefund::addToMap(const HtlcRefund &refund,
                          std::map<std::string, std::string> &map) {
    // Id
    map.emplace(KEY_REFUND_TX_ID_LABEL, BytesToHex(refund.id));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Htlc Refund-type Transaction.
auto HtlcRefund::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1)  + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1)  + OBJECT_HTLC_REFUND_SIZE +
           JSON_OBJECT_SIZE(1)  + KEY_REFUND_TX_ID_SIZE + HASH_32_MAX_CHARS;
}

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Refund data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Htlc Refund data.
//
// ---
void HtlcRefund::addToJson(DynamicJsonDocument &jsonDoc,
                           const std::map<std::string, std::string> &map) {
    const auto asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    const auto refund = asset.createNestedObject(OBJECT_HTLC_REFUND_LABEL);

    // Lock Transaction Id
    refund[KEY_REFUND_TX_ID_LABEL] = map.at(KEY_REFUND_TX_ID_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
