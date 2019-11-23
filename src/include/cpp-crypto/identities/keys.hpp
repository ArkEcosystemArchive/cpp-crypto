/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_IDENTITIES_KEYS_HPP
#define ARK_IDENTITIES_KEYS_HPP

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

////////////////////////////////////////////////////////////////////////////////

struct Keys {
    static KeyPair fromPassphrase(const char *passphrase);
    static KeyPair fromPrivateKey(const uint8_t *privateKeyBytes);
    static KeyPair fromWif(const char *wif);

////////////////////////////////////////////////////////////////////////////////

    struct PrivateKey {
        static PrivateKeyBytes fromPassphrase(const char *passphrase);
        static PrivateKeyBytes fromWif(const char *wif, uint8_t *outVersion);
    };

////////////////////////////////////////////////////////////////////////////////

    struct PublicKey {
        static PublicKeyBytes fromPrivateKey(const uint8_t *privateKeyBytes);
    };

////////////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark

#endif
