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
#include <vector>

#include "interfaces/identities.hpp"

#include "transactions/types/assets.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// v2 Transcation Offsets
static const uint8_t HEADER_OFFSET              = 0U;
static const uint8_t VERSION_OFFSET             = 1U;
static const uint8_t NETWORK_OFFSET             = 2U;
static const uint8_t TYPEGROUP_OFFSET           = 3U;
static const uint8_t TYPE_OFFSET                = 7U;
static const uint8_t NONCE_OFFSET               = 9U;
static const uint8_t SENDER_PUBLICKEY_OFFSET    = 17U;
static const uint8_t FEE_OFFSET                 = 50U;
static const uint8_t VF_LEN_OFFSET              = 58U;
static const uint8_t VF_OFFSET                  = 59U;

////////////////////////////////////////////////////////////////////////////////
// v1 Transaction Offsets
namespace v1 {
static const uint8_t HEADER_OFFSET              = 0U;
static const uint8_t VERSION_OFFSET             = 1U;
static const uint8_t NETWORK_OFFSET             = 2U;
static const uint8_t TYPE_OFFSET                = 3U;
static const uint8_t TIMESTAMP_OFFSET           = 4U;
static const uint8_t SENDER_PUBLICKEY_OFFSET    = 8U;
static const uint8_t FEE_OFFSET                 = 41U;
static const uint8_t VF_LEN_OFFSET              = 49U;
static const uint8_t VF_OFFSET                  = 50U;
}  // namespace v1

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
