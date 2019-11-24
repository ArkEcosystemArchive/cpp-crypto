/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_HTLC_CLAIM_HPP
#define ARK_TRANSACTIONS_BUILDERS_HTLC_CLAIM_HPP

#include <cstdint>
#include <utility>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class HtlcClaim;

////////////////////////////////////////////////////////////////////////////////
class HtlcClaim : public Common<HtlcClaim> {
  public:

    ////////////////////////////////////////////////////////////////////////////
    // Lock Transaction Id
    HtlcClaim &lockTransactionId(const uint8_t *lockTransactionId) {
        std::move(lockTransactionId,
                  lockTransactionId + HASH_32_LEN,
                  this->transaction.data.asset.htlcClaim.id.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Unlock Secret
    HtlcClaim &unlockSecret(const uint8_t *unlockSecret) {
        std::move(unlockSecret, 
                  unlockSecret + HASH_32_LEN,
                  this->transaction.data.asset.htlcClaim.secret.begin());

        return *this;
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
