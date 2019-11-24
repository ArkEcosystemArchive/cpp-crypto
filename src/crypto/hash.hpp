
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_CRYPTO_HASH_HPP
#define ARK_CRYPTO_HASH_HPP

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Hash Operations
struct Hash {
    ////////////////////////////////////////////////////////////////////////////
    static PubkeyHash ripemd160(const uint8_t *publicKeyBytes);

    ////////////////////////////////////////////////////////////////////////////
    static Hash32 sha256(const uint8_t *inputBytes, const size_t size);

////////////////////////////////////////////////////////////////////////////////

};

}  // namespace Crypto
}  // namespace Ark

#endif
