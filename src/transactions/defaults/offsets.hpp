/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_DEFAULTS_OFFSETS_HPP
#define ARK_TRANSACTIONS_DEFAULTS_OFFSETS_HPP

#include <cstdint>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// v2 Transaction Offsets
constexpr uint8_t HEADER_OFFSET                 = 0U;
constexpr uint8_t VERSION_OFFSET                = 1U;
constexpr uint8_t NETWORK_OFFSET                = 2U;
constexpr uint8_t TYPEGROUP_OFFSET              = 3U;
constexpr uint8_t TYPE_OFFSET                   = 7U;
constexpr uint8_t NONCE_OFFSET                  = 9U;
constexpr uint8_t SENDER_PUBLICKEY_OFFSET       = 17U;
constexpr uint8_t FEE_OFFSET                    = 50U;
constexpr uint8_t VF_LEN_OFFSET                 = 58U;
constexpr uint8_t VF_OFFSET                     = 59U;

////////////////////////////////////////////////////////////////////////////////
// v1 Transaction Offsets
namespace v1 {
constexpr uint8_t HEADER_OFFSET                 = 0U;
constexpr uint8_t VERSION_OFFSET                = 1U;
constexpr uint8_t NETWORK_OFFSET                = 2U;
constexpr uint8_t TYPE_OFFSET                   = 3U;
constexpr uint8_t TIMESTAMP_OFFSET              = 4U;
constexpr uint8_t SENDER_PUBLICKEY_OFFSET       = 8U;
constexpr uint8_t FEE_OFFSET                    = 41U;
constexpr uint8_t VF_LEN_OFFSET                 = 49U;
constexpr uint8_t VF_OFFSET                     = 50U;
}  // namespace v1

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
