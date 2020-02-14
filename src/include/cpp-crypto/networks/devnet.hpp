/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_NETWORKS_DEVNET_HPP
#define ARK_NETWORKS_DEVNET_HPP

#include "common/network.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Devnet
// Default ARK Development Network
const Network Devnet {
    "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867",  // nethash
    1,                                                                   // slip44
    0xaa,                                                                // wif
    0x1e,                                                                // version
    "2017-03-21T13:00:00.000Z"                                           // epoch
};

}  // namespace Crypto
}  // namespace Ark

#endif
