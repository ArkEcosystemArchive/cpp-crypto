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
/**/
class NetworkManager {
 private:
  Network network_ = Networks::Devnet();

 public:
  // Default initialization: using ARK Devnet
  NetworkManager() = default;
  virtual ~NetworkManager() = default;

  // Network initialization: Custom Network
  NetworkManager(const Network& network) : network_(network) {}

  Network getNetwork() const;
  void setNetwork(const Network& network);

  bool operator==(const NetworkManager& rhs) const;
  bool operator!=(const NetworkManager& rhs) const;
};
/**/
}  // namespace managers
}  // namespace Crypto
}  // namespace Ark

#endif
