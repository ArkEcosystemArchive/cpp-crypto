/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/htlc_refund.hpp"

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
// - std::move(buffer, buffer + 32, refund->id.begin());
// ---
auto HtlcRefund::Deserialize(HtlcRefund *refund, const uint8_t *buffer) -> uint32_t {
    refund->id = {};
    std::move(buffer, buffer + HASH_32_LEN, refund->id.begin());    // 32 Bytes

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
// - std::move(refund.id.begin(), refund.id.end(), buffer);
//
// ---
auto HtlcRefund::Serialize(const HtlcRefund &refund, uint8_t *buffer) -> uint32_t {
    std::move(refund.id.begin(), refund.id.end(), buffer);          // 32 Bytes

    return HASH_32_LEN;
}

////////////////////////////////////////////////////////////////////////////////

// Return a Map of the the Htlc Refund Id.
auto HtlcRefund::getMap(const HtlcRefund &refund)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Id
    map.emplace("lockTransactionId", BytesToHex(refund.id));

    return map;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
