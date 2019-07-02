/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "defaults/static_fees.hpp"

#include <cstdint>

#include "common/fee_policy.hpp"

namespace Ark {
namespace Crypto {
namespace defaults {

// Default ARK Static Fees
const FeePolicy Fees::StaticFeePolicy() {
  return {
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
}

}  // namespace defaults
}  // namespace Crypto
}  // namespace Ark
