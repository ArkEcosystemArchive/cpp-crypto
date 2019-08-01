/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef MANAGERS_NETWORK_MANAGER_HPP
#define MANAGERS_NETWORK_MANAGER_HPP

#include "common/network.hpp"
#include "networks/devnet.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

class NetworkManager {
 public:
  Network getNetwork() const;
  void setNetwork(const Network& network);

 protected:
  Network network_ = Devnet;
};

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
