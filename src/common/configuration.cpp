/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "common/configuration.hpp"

namespace Ark {
namespace Crypto {

bool Configuration::operator==(const Configuration& rhs) const {
  return this->getNetwork() == rhs.getNetwork()
         && this->getPolicy() == rhs.getPolicy();
}

/**/

bool Configuration::operator!=(const Configuration& rhs) const {
  return this->getNetwork() != rhs.getNetwork()
         || this->getPolicy() != rhs.getPolicy();}

}  // namespace Crypto
}  // namespace Ark
