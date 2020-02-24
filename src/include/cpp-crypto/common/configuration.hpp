/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_COMMON_CONFIGURATION_HPP
#define ARK_COMMON_CONFIGURATION_HPP

#include "managers/network_manager.hpp"
#include "managers/fee_manager.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Network Configuration Class
class Configuration : public managers::NetworkManager,
                      public managers::FeeManager {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Default initialization: ARK Devnet w/StaticFees
    Configuration() = default;
    Configuration(const Network &network);
    Configuration(const FeePolicy &policy);
    Configuration(const Network &network, const FeePolicy &policy);

    ////////////////////////////////////////////////////////////////////////////
    bool operator==(const Configuration &other) const;
    bool operator!=(const Configuration &other) const;
};

}  // namespace Crypto
}  // namespace Ark

#endif
