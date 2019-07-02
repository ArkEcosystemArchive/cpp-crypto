/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "networks/testnet.hpp"

namespace Ark {
namespace Crypto {
/**/
// Testnet
// ARK Test Network
const Network Networks::Testnet() {  // NOLINT
  return Network(
    "d9acd04bde4234a81addb8482333b4ac906bed7be5a9970ce8ada428bd083192",   // nethash
    1,                                                                    // slip44
    0xba,                                                                 // wif
    0x17,                                                                 // version
    "2017-03-21T13:00:00.000Z"                                            // epoch
  );
}
/**/
}  // namespace Crypto
}  // namespace Ark
