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
#include <cstring>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////

class HtlcClaim;

////////////////////////////////////////////////////////////////////////////////

class HtlcClaim : public Common<HtlcClaim> {
  public:

////////////////////////////////////////////////////////////////////////////////

    // Lock Transaction Id
    HtlcClaim &lockTransactionId(const uint8_t *lockTransactionId) {
        memmove(&this->transaction.data.asset.htlcClaim.id,
                lockTransactionId,
                HASH_32_LEN);
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    // Unlock Secret
    HtlcClaim &unlockSecret(const uint8_t *unlockSecret) {
        memmove(&this->transaction.data.asset.htlcClaim.secret,
                unlockSecret,
                HASH_32_LEN);
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
