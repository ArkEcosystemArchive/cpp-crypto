/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef IDENTITIES_WIF_HPP
#define IDENTITIES_WIF_HPP

#include <string>

#include "identities/privatekey.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

class Wif {
 public:
  Wif(const PrivateKeyBytes privateKeyBytes, uint8_t version);
  explicit Wif(const char* wif);

  uint8_t version() const;
  PrivateKeyBytes toBytes() const;
  std::string toString() const;

  static Wif fromPassphrase(const char* passphrase, uint8_t version);

 private:
  PrivateKeyBytes privateKeyBytes_;
  uint8_t version_;
};

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark

#endif
