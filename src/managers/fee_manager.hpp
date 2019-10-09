/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef MANAGERS_FEE_MANAGER_HPP
#define MANAGERS_FEE_MANAGER_HPP

#include "common/fee_policy.hpp"
#include "defaults/static_fees.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

class FeeManager {
 public:
  uint64_t getFee(uint8_t type) const ;
  void setFee(uint8_t type, uint64_t amount);

  FeePolicy getPolicy() const;
  void setPolicy(const FeePolicy& policy);

 protected:
  FeePolicy feePolicy_ = StaticFeePolicy;
};

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
