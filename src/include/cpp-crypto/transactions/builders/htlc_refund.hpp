/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_HTLC_REFUND_HPP
#define ARK_TRANSACTIONS_BUILDERS_HTLC_REFUND_HPP

#include <algorithm>
#include <cstdint>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class HtlcRefund;

////////////////////////////////////////////////////////////////////////////////
class HtlcRefund : public Common<HtlcRefund> {
  public:
  ////////////////////////////////////////////////////////////////////////////
    // Lock Transaction Id
    HtlcRefund &lockTransactionId(const uint8_t *lockTransactionId) {
        std::copy_n(lockTransactionId,
                    HASH_32_LEN,
                    this->transaction.data.asset.htlcRefund.id.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    HtlcRefund(const Configuration &config = {}) {
        this->transaction.data.type = HTLC_REFUND_TYPE;
        this->configure(config);
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
