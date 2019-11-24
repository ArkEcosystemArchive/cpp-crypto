/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_NETWORKS_MAINNET_HPP
#define ARK_NETWORKS_MAINNET_HPP

#include "common/network.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Mainnet
// ARK Public Network
const Network Mainnet {
    "6e84d08bd299ed97c212c886c98a57e36545c8f5d645ca7eeae63a8bd62d8988",  // nethash
    111,                                                                 // slip44
    0xaa,                                                                // wif
    0x17,                                                                // version
    "2017-03-21T13:00:00.000Z"                                           // epoch
};

}  // namespace Crypto
}  // namespace Ark

#endif
