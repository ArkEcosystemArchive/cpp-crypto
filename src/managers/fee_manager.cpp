/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "managers/fee_manager.hpp"

#include <cstdint>

namespace Ark {
namespace Crypto {
namespace managers {

namespace {
  static const uint64_t AMOUNT_ZERO = 0ULL;
}  // namespace

/**/

uint64_t FeeManager::getFee(uint8_t type) const {
  std::size_t slot = type + 1;
  return slot <= feePolicy_.size()
      ? this->feePolicy_[type]
      : AMOUNT_ZERO;
}

/**/

void FeeManager::setFee(uint8_t type, uint64_t amount) {
  std::size_t slot = type + 1;
  if (slot > this->feePolicy_.size()) {
    this->feePolicy_.resize(slot);
  };
  this->feePolicy_[type] = amount;
}

/**/

FeePolicy FeeManager::getPolicy() const {
  return this->feePolicy_;
}

/**/

void FeeManager::setPolicy(const FeePolicy& policy) {
  this->feePolicy_ = policy;
}

/**/

bool FeeManager::operator==(const FeeManager& rhs) const {
  return this->getPolicy() == rhs.getPolicy();
}

/**/

bool FeeManager::operator!=(const FeeManager& rhs) const {
  return this->getPolicy() != rhs.getPolicy();
}

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark
