/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "common/network.hpp"

#include <string>

namespace Ark {
namespace Crypto {

bool Network::operator==(const Network& other) const {
  bool numbersMatch = (this->slip44 == other.slip44) &&
                      (this->wif == other.wif) &&
                      (this->version == other.version);
  bool stringsMatch = (this->nethash == other.nethash) &&
                      (this->epoch == other.epoch);
  return numbersMatch && stringsMatch;
}

/**/

bool Network::operator!=(const Network& other) const {
  bool numbersMatch = (this->slip44 != other.slip44) ||
                      (this->wif != other.wif) ||
                      (this->version != other.version);
  bool stringsMatch = (this->nethash != other.nethash) ||
                      (this->epoch != other.epoch);
  return numbersMatch || stringsMatch;
}

}  // namespace Crypto
}  // namespace Ark
