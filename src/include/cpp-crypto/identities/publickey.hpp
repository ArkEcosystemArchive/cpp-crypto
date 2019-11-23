/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_IDENTITIES_PUBLICKEY_HPP
#define ARK_IDENTITIES_PUBLICKEY_HPP

#include <string>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

////////////////////////////////////////////////////////////////////////////////

class PublicKey {
  public:
    explicit PublicKey(const PublicKeyBytes &publicKeyBytes);

    PublicKeyBytes toBytes() const noexcept;
    std::string toString() const;

    static PublicKey fromPassphrase(const char *passphrase);
    static PublicKey fromHex(const char *publicKeyHex);

  private:
    PublicKeyBytes publicKeyBytes_;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark

#endif
