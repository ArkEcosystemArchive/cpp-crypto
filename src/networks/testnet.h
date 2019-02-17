/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef TESTNET_H
#define TESTNET_H

#include "networks/abstractnetwork.h"

namespace Ark {
namespace Crypto {
namespace Networks {
/**
 * @brief This is the testnet network class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
const AbstractNetwork Testnet = {
    {
        0x17,  // BASE58_ADDRESS_P2PKH
        0x00,  // BASE58_ADDRESS_P2SH
        0xba   // BASE58_WIF
    },
    {
        70617039,  // BIP32_PREFIX_XPUB
        70615956   // BIP32_PREFIX_XPRV
    },
    "2017-03-21T13:00:00.000Z"  // Epoch
};
/**/
};  // namespace Networks
};  // namespace Crypto
};  // namespace Ark

#endif
