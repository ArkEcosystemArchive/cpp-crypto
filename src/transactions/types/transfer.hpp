/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_TRANSFER_HPP
#define ARK_TRANSACTIONS_TYPES_TRANSFER_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

const size_t TRANSACTION_TYPE_TRANSFER_SIZE = 33UL;

////////////////////////////////////////////////////////////////////////////////
// Type 0 - Transfer
struct Transfer {
    ////////////////////////////////////////////////////////////////////////////
    uint64_t                                amount;
    uint32_t                                expiration;
    std::array<uint8_t, ADDRESS_HASH_LEN>   recipientId;

    ////////////////////////////////////////////////////////////////////////////
    static uint32_t Deserialize(Transfer *transfer, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static uint32_t Serialize(const Transfer &transfer, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static std::map<std::string, std::string> getMap(const Transfer &transfer);

    ////////////////////////////////////////////////////////////////////////////
    Transfer() : amount(0ULL), expiration(0UL), recipientId() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
