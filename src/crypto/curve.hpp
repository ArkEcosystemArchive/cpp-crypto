
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_CRYPTO_CURVE_HPP
#define ARK_CRYPTO_CURVE_HPP

#include <vector>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {

struct Curve {

////////////////////////////////////////////////////////////////////////////////

    // Generate Signatures based in ECDSA Cryptography.
    struct Ecdsa {
        static bool sign(const uint8_t *hash32,
                         const uint8_t *privateKeyBytes,
                         std::vector<uint8_t> *outSignature);

        static bool verify(const uint8_t *hash32,
                           const uint8_t *publicKeyBytes,
                           const std::vector<uint8_t> &signature);
  };

////////////////////////////////////////////////////////////////////////////////

    // Primitive PublicKey operations.
    struct PublicKey {
        static PublicKeyBytes compute(const uint8_t *privateKeyBytes);

        static PublicKeyBytes compress(const uint8_t *uncompressed);
        static PublicKeyPoint decompress(const uint8_t *compressed);

        static bool validate(const uint8_t *publicKeyBytes);  
    };

////////////////////////////////////////////////////////////////////////////////

};

}  // namespace Crypto
}  // namespace Ark

#endif
