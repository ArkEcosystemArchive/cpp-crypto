/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_MANAGERS_NETWORK_MANAGER_HPP
#define ARK_MANAGERS_NETWORK_MANAGER_HPP

#include "common/network.hpp"

#include "networks/devnet.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

// Network Manager
// Network Getter/Setter for the common/Configuration-type.
class NetworkManager {
  public:

////////////////////////////////////////////////////////////////////////////////

    auto getNetwork() const -> Network {
        return this->network_;
    }

////////////////////////////////////////////////////////////////////////////////

    void setNetwork(const Network &network) {
        this->network_ = network;
    }

////////////////////////////////////////////////////////////////////////////////

  protected:
    Network network_ = Devnet;

////////////////////////////////////////////////////////////////////////////////

};

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
