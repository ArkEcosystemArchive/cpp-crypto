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
#include <cstring>
#include <map>
#include <string>

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
constexpr size_t TRANSACTION_TYPE_TRANSFER_SIZE = 33UL;

////////////////////////////////////////////////////////////////////////////////
// Type 0 - Transfer
struct Transfer {  // LCOV_EXCL_LINE
    ////////////////////////////////////////////////////////////////////////////
    uint64_t        amount      { 0ULL };
    uint32_t        expiration  { 0UL };
    AddressHash     recipientId { };

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(Transfer *transfer, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const Transfer &transfer, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const Transfer &transfer,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
