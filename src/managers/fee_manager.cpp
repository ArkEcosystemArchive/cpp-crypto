/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "managers/fee_manager.hpp"

#include "common/fee_policy.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

uint64_t FeeManager::getFee(uint8_t type) const {
  return type <= this->feePolicy_.size()
          ? this->feePolicy_.at(type)
          : AMOUNT_ZERO;
}

/**/

void FeeManager::setFee(uint8_t type, uint64_t amount) {
  if (type > this->feePolicy_.size()) {
    this->feePolicy_.resize(type + 1);
  };
  this->feePolicy_.at(type) = amount;
}

/**/

FeePolicy FeeManager::getPolicy() const {
  return this->feePolicy_;
}

/**/

void FeeManager::setPolicy(const FeePolicy& policy) {
  this->feePolicy_ = policy;
}

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark
