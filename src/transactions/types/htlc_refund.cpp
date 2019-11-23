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
#include <cstring>
#include <map>
#include <string>

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
// - memmove(&refund.id, &buffer[0], 32); 
//
// ---
auto HtlcRefund::Deserialize(HtlcRefund *refund, const uint8_t *buffer) -> uint32_t {
    refund->id = { 0U };
    memmove(&refund->id, buffer, HASH_32_LEN);                   // 32 Bytes

    return HASH_32_LEN;                                          // 32 Bytes
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
// - memmove(buffer, &refund.id, 32);
//
// ---
auto HtlcRefund::Serialize(const HtlcRefund &refund, uint8_t *buffer) -> uint32_t {
    memmove(buffer, &refund.id, HASH_32_LEN);                   // 32 Bytes

    return HASH_32_LEN;                                         // 32 Bytes
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
