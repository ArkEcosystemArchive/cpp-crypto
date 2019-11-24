/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_VOTE_HPP
#define ARK_TRANSACTIONS_BUILDERS_VOTE_HPP

#include <cstdint>
#include <utility>

#include "transactions/builders/common.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////

class Vote;

////////////////////////////////////////////////////////////////////////////////

class Vote : public Common<Vote> {
  public:
    // Votes
    //
    // Should be in the format:
    // - { 1(n_votes), 00/01('-'/'+'), publicKeyBytes }
    Vote &votes(const uint8_t *votes) {
        this->transaction.data.asset.vote.count = 1U;
        std::move(votes,
                  votes + VOTES_LEN,
                  this->transaction.data.asset.vote.votes.begin());

        return *this;
    }
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
