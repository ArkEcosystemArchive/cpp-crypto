
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_MANAGERS_FEE_MANAGER_HPP
#define ARK_MANAGERS_FEE_MANAGER_HPP

#include "common/fee_policy.hpp"

#include "transactions/defaults/fees.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

////////////////////////////////////////////////////////////////////////////////
// FeeManager
// Fee Getter/Setter for the common/Configuration-type.
class FeeManager {
  public:
    ////////////////////////////////////////////////////////////////////////////
    auto getFee(const uint16_t type) const -> uint64_t {
        return type < this->feePolicy_.size() ? this->feePolicy_.at(type) : 0ULL;
    }
  
    ////////////////////////////////////////////////////////////////////////////
    void setFee(const uint16_t type, const uint64_t amount) {
        this->feePolicy_.insert(this->feePolicy_.begin() + type, amount);
    }

    ////////////////////////////////////////////////////////////////////////////
    auto getPolicy() const -> FeePolicy {
        return this->feePolicy_;
    }

    ////////////////////////////////////////////////////////////////////////////
    void setPolicy(const FeePolicy &policy){
        this->feePolicy_ = policy;
    }

  protected:
    ////////////////////////////////////////////////////////////////////////////
    FeePolicy feePolicy_ = transactions::StaticFeePolicy;
};

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
