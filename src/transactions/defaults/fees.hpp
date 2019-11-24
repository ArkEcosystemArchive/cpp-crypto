/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_DEFAULTS_FEES_HPP
#define ARK_TRANSACTIONS_DEFAULTS_FEES_HPP

#include "common/fee_policy.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Default Transaction Fees
static const uint64_t TRANSFER_FEE                  = 10000000ULL;
static const uint64_t SECOND_SIGNATURE_FEE          = 500000000ULL;
static const uint64_t DELEGATE_REGISTRATION_FEE     = 2500000000ULL;
static const uint64_t VOTE_FEE                      = 100000000ULL;
static const uint64_t MULTI_SIGNATURE_FEE           = 500000000ULL;
static const uint64_t IPFS_FEE                      = 500000000ULL;
static const uint64_t MULTI_PAYMENT_FEE             = 10000000ULL;
static const uint64_t DELEGATE_RESIGNATION_FEE      = 2500000000ULL;
static const uint64_t HTLC_LOCK_FEE                 = 10000000ULL;
static const uint64_t HTLC_CLAIM_FEE                = 0ULL;
static const uint64_t HTLC_REFUND_FEE               = 0ULL;

////////////////////////////////////////////////////////////////////////////////
// The Default Fee Policy
const FeePolicy StaticFeePolicy {
    TRANSFER_FEE,                   // 10000000ULL
    SECOND_SIGNATURE_FEE,           // 500000000ULL
    DELEGATE_REGISTRATION_FEE,      // 2500000000ULL
    VOTE_FEE,                       // 100000000ULL
    MULTI_SIGNATURE_FEE,            // 500000000ULL
    IPFS_FEE,                       // 500000000ULL
    MULTI_PAYMENT_FEE,              // 10000000ULL
    DELEGATE_RESIGNATION_FEE,       // 2500000000ULL
    HTLC_LOCK_FEE,                  // 10000000ULL
    HTLC_CLAIM_FEE,                 // 0ULL
    HTLC_REFUND_FEE                 // 0ULL
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
