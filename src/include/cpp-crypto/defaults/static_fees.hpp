/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef DEFAULTS_TRANSACTIONS_STATIC_FEES_HPP
#define DEFAULTS_TRANSACTIONS_STATIC_FEES_HPP

#include "common/fee_policy.hpp"

namespace Ark {
namespace Crypto {

const FeePolicy StaticFeePolicy {
    10000000ULL,    // Transfer
    500000000ULL,   // SecondSignatureRegistration
    2500000000ULL,  // DelegateRegistration
    100000000ULL,   // Vote
    500000000ULL,   // MultiSignatureRegistration
    0ULL,           // Ipfs
    0ULL,           // TimelockTransfer
    0ULL,           // MultiPayment
    2500000000ULL   // DelegateResignation
};

}  // namespace Crypto
}  // namespace Ark

#endif
