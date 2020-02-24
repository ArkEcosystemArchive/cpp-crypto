/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/ipfs.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>

#include "interfaces/constants.h"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/json.h"
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

    if (buffer[1] == 0U || ipfsLen <= IPFS_MIN || ipfsLen > IPFS_MAX) {
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
// - std::copy(ipfs.dag.begin(), ipfs.dag.end(), buffer);
//
// ---
auto Ipfs::Serialize(const Ipfs &ipfs, uint8_t *buffer) -> size_t {
    if (ipfs.dag.empty() ||
        ipfs.dag.size() <= IPFS_MIN ||
        ipfs.dag.size() > IPFS_MAX) {
        return 0UL;
    }

    std::copy(ipfs.dag.begin(), ipfs.dag.end(), buffer);    // 0 <=> 255 Bytes

    return ipfs.dag.size();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
constexpr auto KEY_IPFS_LABEL   = "ipfs";
constexpr size_t KEY_IPFS_SIZE  = 4;

////////////////////////////////////////////////////////////////////////////////
// Add Ipfs Asset data to a Transaction Map.
void Ipfs::addToMap(const Ipfs &ipfs,
                    std::map<std::string, std::string> &map) {
    map.emplace(KEY_IPFS_LABEL,
                Base58::checkEncode(ipfs.dag.data(),
                ipfs.dag.size()));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Ipfs-type Transaction.
auto Ipfs::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1)  + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1)  + KEY_IPFS_SIZE +
           IPFS_MAX;
}

////////////////////////////////////////////////////////////////////////////////
// Add Ipfs data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Ipfs data.
//
// ---
void Ipfs::addToJson(DynamicJsonDocument &jsonDoc,
                     const std::map<std::string, std::string> &map) {
    JsonObject asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);

    // Ipfs Dag
    asset[KEY_IPFS_LABEL] = map.at(KEY_IPFS_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
