/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef COMMON_CONFIGURATION_HPP
#define COMMON_CONFIGURATION_HPP

#include "common/network.hpp"
#include "managers/network_manager.hpp"
#include "common/fee_policy.hpp"
#include "managers/fee_manager.hpp"

namespace Ark {
namespace Crypto {
/**/
class Configuration : public managers::NetworkManager,
                      public managers::FeeManager {
 public:
  // Default initialization: using ARK Devnet & StaticFees
  Configuration() = default;
  ~Configuration() = default;

  // Network initialization: Custom Network & StaticFees
  explicit Configuration(const Network& network) : NetworkManager(network) {}

  // FeePolicy initialization: ARK Devnet & Custom Fees
  explicit Configuration(const FeePolicy& policy) : FeeManager(policy) {}

  // Network & Fee initialization: Custom Network & Custom Fees
  Configuration(const Network& network, const FeePolicy& policy)
      : NetworkManager(network), FeeManager(policy) {}

  bool operator==(const Configuration& rhs) const;
  bool operator!=(const Configuration& rhs) const;
};
/**/
}  // namespace Crypto
}  // namespace Ark

#endif
