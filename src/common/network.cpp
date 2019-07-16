/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "common/network.hpp"
#include "networks/devnet.hpp"

namespace Ark {
namespace Crypto {

Network::Network() { *this = Networks::Devnet(); }

/**/

std::string Network::nethash() const  { return this->nethash_; }
uint8_t Network::slip44() const       { return this->slip44_; }
uint8_t Network::wif() const          { return this->wif_; }
uint8_t Network::version() const      { return this->version_; }
std::string Network::epoch() const    { return this->epoch_; }

/**/

bool Network::operator==(const Network& rhs) const {
  bool numericsMatch = (this->slip44_ == rhs.slip44_)
                        && (this->wif_ == rhs.wif_)
                        && (this->version_ == rhs.version_);
  bool stringsMatch = (this->nethash_ == rhs.nethash_)
                       && (this->epoch_ == rhs.epoch_);
  return numericsMatch && stringsMatch;
}

/**/

bool Network::operator!=(const Network& rhs) const {
  bool numericsMatch = (this->slip44_ != rhs.slip44_)
                        || (this->wif_ != rhs.wif_)
                        || (this->version_ != rhs.version_);
  bool stringsMatch = (this->nethash_ != rhs.nethash_)
                       || (this->epoch_ != rhs.epoch_);
  return numericsMatch || stringsMatch;
}

}  // namespace Crypto
}  // namespace Ark
