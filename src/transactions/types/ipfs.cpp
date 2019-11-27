/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/ipfs.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "interfaces/constants.h"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Ipfs Transaction (Type 5) - 0 <=> 255 Bytes
//
// @param Ipfs *ipfs
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Dag - UTF-8 encoded -0 <=> 255 Bytes
// - ipfs->dag.insert(ipfs->dag.begin(), buffer, buffer + ipfs->dag.size());
//
// ---
auto Ipfs::Deserialize(Ipfs *ipfs, const uint8_t *buffer) -> size_t {
    const size_t ipfsLen = buffer[1] + 2U;

    if (buffer[1] == 0U || ipfsLen > IPFS_LIMIT) {
        ipfs->dag.resize(0);
        return 0UL;
    }

    ipfs->dag.insert(ipfs->dag.begin(), buffer, buffer + ipfsLen);

    return ipfsLen;                                         // 0 <=> 255 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Ipfs Transaction (Type 5) - 0 <=> 255 Bytes
//
// @param const Ipfs &ipfs
// @param uint8_t *buffer: The buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Dag - UTF-8 encoded - 0 <=> 255 Bytes
// - std::move(ipfs.dag.begin(), ipfs.dag.end(), buffer);
//
// ---
auto Ipfs::Serialize(const Ipfs &ipfs, uint8_t *buffer) -> size_t {
    if (ipfs.dag.empty() || ipfs.dag.size() > IPFS_LIMIT) {
        return 0UL;
    }

    std::move(ipfs.dag.begin(), ipfs.dag.end(), buffer);    // 0 <=> 255 Bytes

    return ipfs.dag.size();
}

////////////////////////////////////////////////////////////////////////////////
// Return a Map of the Ipfs Hash, Base58-encoded.
auto Ipfs::getMap(const Ipfs &ipfs) -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    map.emplace("ipfsLen", UintToString(ipfs.dag.size()));

    map.emplace("ipfs", Base58::checkEncode(ipfs.dag.data(), ipfs.dag.size()));

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
