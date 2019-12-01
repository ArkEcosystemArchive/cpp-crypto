/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_VOTE_HPP
#define ARK_TRANSACTIONS_TYPES_VOTE_HPP

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
const uint8_t VOTE_LIMIT    = 1U;
const uint8_t VOTE_LEN      = 1U + PUBLICKEY_COMPRESSED_LEN;
const uint8_t VOTES_LEN     = VOTE_LIMIT * VOTE_LEN;

////////////////////////////////////////////////////////////////////////////////
// Type 3 - Vote
struct Vote {
    ////////////////////////////////////////////////////////////////////////////
    uint8_t                             count;
    std::array<uint8_t, VOTES_LEN>      votes;      // (VOTE_LIMIT * (1 + 33))

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(Vote *vote, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const Vote &vote, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const Vote &vote,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    Vote() : count(0U), votes() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
