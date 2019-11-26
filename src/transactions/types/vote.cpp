/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/vote.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "interfaces/constants.h"

#include "utils/hex.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Vote Transaction (Type 3) - 35 Bytes
//
// @param Vote *vote
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Vote - 1 + 33 Bytes:
// - std::move(&buffer[1], &buffer[35] + VOTES_LEN, vote->votes.begin());
//
// ---
auto Vote::Deserialize(Vote *vote, const uint8_t *buffer) -> size_t {
    vote->count = buffer[0];                                        // 1 Byte

    std::move(&buffer[sizeof(uint8_t)],                             // 34 Bytes
              &buffer[sizeof(uint8_t)] + VOTES_LEN,
              vote->votes.begin());

    return sizeof(uint8_t) + VOTE_LEN;                              // 35 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Vote Transaction (Type 3) - 35 Bytes
//
// @param const Vote &vote
// @param uint8_t *buffer: The buffer beginning at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Count - 1 Byte:  1-Vote supported
// - buffer[0] = 1;
//
// Vote - 2 + 33 Bytes:
// - std::move(vote.votes.begin(), vote.votes.end(), &buffer[1])
//
// ---
auto Vote::Serialize(const Vote &vote, uint8_t *buffer) -> size_t {
    buffer[0] = vote.count;                                         // 1 Byte

    std::move(vote.votes.begin(),                                   // 34 Bytes
              vote.votes.end(),
              &buffer[sizeof(uint8_t)]);

    return sizeof(uint8_t) + vote.count * VOTE_LEN;                 // 35 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Return a Map of the Vote asset.
auto Vote::getMap(const Vote &vote) -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Vote
    std::string votes;
    votes.reserve(VOTES_LEN);

    // 1 Vote currently supported.
    votes.push_back(vote.votes[0] == 0x01 ? '+' : '-');
    votes.append(BytesToHex(vote.votes.begin() + sizeof(uint8_t),
                            vote.votes.end()));

    map.emplace("votes", votes);

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
