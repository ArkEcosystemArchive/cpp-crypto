/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_HTLC_REFUND_HPP
#define ARK_TRANSACTIONS_TYPES_HTLC_REFUND_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Type 10 - Htlc Refund
struct HtlcRefund {
    ////////////////////////////////////////////////////////////////////////////
    std::array<uint8_t, HASH_32_LEN> id;

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(HtlcRefund *refund, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const HtlcRefund &refund, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static std::map<std::string, std::string> getMap(const HtlcRefund &refund);

    ////////////////////////////////////////////////////////////////////////////
    HtlcRefund() : id() {}
};


}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
