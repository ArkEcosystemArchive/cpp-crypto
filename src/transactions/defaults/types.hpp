/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_DEFAULTS_TYPES_HPP
#define ARK_TRANSACTIONS_DEFAULTS_TYPES_HPP

#include <cstdint>

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

enum TransactionTypes : uint8_t {
    TRANSFER_TYPE                   = 0U,
    SECOND_SIGNATURE_TYPE           = 1U,
    DELEGATE_REGISTRATION_TYPE      = 2U,
    VOTE_TYPE                       = 3U,
    MULTI_SIGNATURE_TYPE            = 4U,
    IPFS_TYPE                       = 5U,
    MULTI_PAYMENT_TYPE              = 6U,
    DELEGATE_RESIGNATION_TYPE       = 7U,
    HTLC_LOCK_TYPE                  = 8U,
    HTLC_CLAIM_TYPE                 = 9U,
    HTLC_REFUND_TYPE                = 10U
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
