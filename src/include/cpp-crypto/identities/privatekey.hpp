/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef IDENTITIES_PRIVATEKEY_HPP
#define IDENTITIES_PRIVATEKEY_HPP

#include <string>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

class PrivateKey {
 public:
  explicit PrivateKey(const PrivateKeyBytes& privateKeyBytes);

  PrivateKeyBytes toBytes() const noexcept;
  std::string toString() const;

  static PrivateKey fromPassphrase(const char* passphrase);
  static PrivateKey fromHex(const char* privateKeyHex);

 private:
  PrivateKeyBytes privateKeyBytes_;
};

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark

#endif
