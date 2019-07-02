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
#include "defaults/fee_policies.hpp"

namespace Ark {
namespace Crypto {
namespace managers {
/**/
class FeeManager {
 private:
  FeePolicy feePolicy_ = defaults::Fees::StaticFeePolicy();

 public:
  // Default initialization: using ARK StaticFees
  FeeManager() = default; 
  virtual ~FeeManager() = default;

  // FeePolicy initialization: Custom FeePolicy
  FeeManager(const FeePolicy& policy) : feePolicy_(policy) {} 

  uint64_t getFee(uint8_t type) const;
  void setFee(uint8_t type, uint64_t amount);

  FeePolicy getPolicy() const;
  void setPolicy(const FeePolicy& policy);

  bool operator==(const FeeManager& rhs) const;
  bool operator!=(const FeeManager& rhs) const;
};
/**/
}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
