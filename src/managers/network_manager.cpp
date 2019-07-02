/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "managers/network_manager.hpp"

#include "common/network.hpp"

namespace Ark {
namespace Crypto {
namespace managers {

Network NetworkManager::getNetwork() const {
  return this->network_;
}

/**/

void NetworkManager::setNetwork(const Network& network) {
  this->network_ = network;
}

/**/

bool NetworkManager::operator==(const NetworkManager& rhs) const {
  return this->getNetwork() == rhs.getNetwork();
}

/**/

bool NetworkManager::operator!=(const NetworkManager& rhs) const {
  return this->getNetwork() != rhs.getNetwork();
}

}  // namespace managers
}  // namespace Crypto
}  // namespace Ark
