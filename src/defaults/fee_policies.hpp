/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef DEFAULTS_TRANSACTIONS_FEE_POLICIES_HPP
#define DEFAULTS_TRANSACTIONS_FEE_POLICIES_HPP

#include <cstdint>

#include "common/fee_policy.hpp"

namespace Ark {
namespace Crypto {
namespace defaults {
/**/
class Fees {
 public:
  static const FeePolicy StaticFeePolicy();
};
/**/
}  // namespace defaults
}  // namespace Crypto
}  // namespace Ark

#endif
