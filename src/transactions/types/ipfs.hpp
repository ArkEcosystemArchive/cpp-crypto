/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_IPFS_HPP
#define ARK_TRANSACTIONS_TYPES_IPFS_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "interfaces/constants.h"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
const uint8_t IPFS_MIN  = 2U;
const uint8_t IPFS_MAX  = 90U;

////////////////////////////////////////////////////////////////////////////////
// Type 5 - Ipfs
struct Ipfs {
    ////////////////////////////////////////////////////////////////////////////
    std::vector<uint8_t> dag;

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(Ipfs *ipfs, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const Ipfs &ipfs, uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const Ipfs &ipfs,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    Ipfs() : dag() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
