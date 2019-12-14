/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_HTLC_LOCK_HPP
#define ARK_TRANSACTIONS_TYPES_HTLC_LOCK_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
constexpr size_t HTLC_LOCK_SIZE = 66U;

////////////////////////////////////////////////////////////////////////////////
// Type 8 - Htlc Lock
struct HtlcLock {
    ////////////////////////////////////////////////////////////////////////////
    uint64_t                                amount              { 0ULL };
    std::array<uint8_t, HASH_32_LEN>        secretHash          { };
    uint8_t                                 expirationType      { 0U };
    uint32_t                                expiration          { 0UL };
    AddressHash                             recipientId         { };

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(HtlcLock *lock, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const HtlcLock &lock, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const HtlcLock &lock,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    HtlcLock() = default;
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
