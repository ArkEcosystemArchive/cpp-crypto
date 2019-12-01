/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_HTLC_CLAIM_HPP
#define ARK_TRANSACTIONS_TYPES_HTLC_CLAIM_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Type 9 - Htlc Claim
struct HtlcClaim {
    ////////////////////////////////////////////////////////////////////////////
    std::array<uint8_t, HASH_32_LEN>    id;
    std::array<uint8_t, HASH_32_LEN>    secret;

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(HtlcClaim *claim, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const HtlcClaim &claim, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const HtlcClaim &claim,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    HtlcClaim() : id(), secret() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
