/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_COMMON_NETWORK_HPP
#define ARK_COMMON_NETWORK_HPP

#include <string>

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Network Data Model
struct Network {
    ////////////////////////////////////////////////////////////////////////////
    std::string     nethash;
    uint8_t         slip44;
    uint8_t         wif;
    uint8_t         version;
    std::string     epoch;

    ////////////////////////////////////////////////////////////////////////////
    bool operator==(const Network &other) const;
    bool operator!=(const Network &other) const;
};

}  // namespace Crypto
}  // namespace Ark

#endif
