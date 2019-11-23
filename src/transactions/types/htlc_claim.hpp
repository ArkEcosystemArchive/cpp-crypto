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

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

struct HtlcClaim {
    std::array<uint8_t, HASH_32_LEN>    id;
    std::array<uint8_t, HASH_32_LEN>    secret;

    static uint32_t Deserialize(HtlcClaim *claim, const uint8_t *buffer);

    static uint32_t Serialize(const HtlcClaim &claim, uint8_t *buffer);

    static std::map<std::string, std::string> getMap(const HtlcClaim &claim);

    HtlcClaim() : id(), secret() {}
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
