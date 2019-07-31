
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef CRYPTO_CURVE_HPP
#define CRYPTO_CURVE_HPP

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {

struct Curve {

  struct PublicKey {
    static PublicKeyBytes compute(const uint8_t* privateKeyBytes);
    static bool validate(const uint8_t* publicKeyBytes);  
  };

};

}  // namespace Crypto
}  // namespace Ark

#endif
