
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/
#include "crypto/curve.hpp"

#include "interfaces/identities.hpp"

#include "uECC.h"

namespace Ark {
namespace Crypto {

PublicKeyBytes Curve::PublicKey::compute(const uint8_t* privateKeyBytes) {
  const struct uECC_Curve_t* curve = uECC_secp256k1();

  PublicKeyPoint uncompressed {};
  if (uECC_compute_public_key(privateKeyBytes,
                              uncompressed.data(),
                              curve) == 0) { return {}; };

  PublicKeyBytes compressed {};
  uECC_compress(uncompressed.data(), compressed.data(), curve);

  return compressed;
}

/**/

bool Curve::PublicKey::validate(const uint8_t* publicKeyBytes) {
  const struct uECC_Curve_t* curve = uECC_secp256k1();

  PublicKeyPoint uncompressed {};
  uECC_decompress(publicKeyBytes, uncompressed.data(), curve);

  return (uECC_valid_public_key(uncompressed.data(), curve) != 0);
}


}  // namespace Crypto
}  // namespace Ark
