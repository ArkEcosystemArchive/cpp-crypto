/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/htlc_lock.hpp"

#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <utility>

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

#include "transactions/defaults/offsets.hpp"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"
#include "utils/unpack.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Htlc Lock Transaction (Type 8) - 66 Bytes
//
// @param HtlcLock *lock
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Amount - 8 Bytes:
// - lock.amount = unpack8LE(buffer, 0);
//
// Secret Hash - 32 Bytes
// - std::move(&buffer[8], &buffer[40], lock->secretHash.begin());
//
// Expiration Type- 1 Byte
// - lock.expirationType = buffer[40];
//
// Expiration Value - 4 Bytes
// - lock.expirationValue = unpack4LE(buffer, 41);
//
// Recipient - 21 Bytes
// - std::move(&buffer[45], &buffer[66], lock->recipientId.begin());
//
// ---
auto HtlcLock::Deserialize(HtlcLock *lock, const uint8_t *buffer) -> size_t {
    size_t offset = 0UL;

    lock->amount = unpack8LE(buffer, offset);                       // 8 Bytes

    offset += sizeof(uint64_t);

    std::move(&buffer[offset],                                      // 32 Bytes
              &buffer[offset + HASH_32_LEN],
              lock->secretHash.begin());

    offset += HASH_32_LEN;

    lock->expirationType = buffer[offset];                          // 1 Byte

    offset += sizeof(uint8_t);

    lock->expiration = unpack4LE(buffer, offset);                   // 4 Bytes

    offset += sizeof(uint32_t);

    std::move(&buffer[offset],                                      // 21 Bytes
              &buffer[offset + ADDRESS_HASH_LEN],
              lock->recipientId.begin());

    offset += ADDRESS_HASH_LEN;

    return offset;                                                  // 66 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Htlc Lock Transaction (Type 8) - 70 Bytes
//
// @param const HtlcLock &lock
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Amount - 8 Bytes:
// - memmove(buffer, &lock.amount, 8);
//
// Secret Hash - 32 Bytes
// - std::move(lock.secretHash.begin(), lock.secretHash.end(), &buffer[8]);;
//
// Expiration Type- 1 Byte
// - buffer[40] = lock.expirationType;
//
// Expiration Value - 4 Bytes
// - memmove(&buffer[offset], &lock.expiration, 8);
//
// Recipient - 21 Bytes
// - std::move(lock.recipientId.begin(), lock.recipientId.end(), &buffer[45]);
//
// ---
auto HtlcLock::Serialize(const HtlcLock &lock, uint8_t *buffer) -> size_t {
    size_t offset = 0;

    memmove(buffer, &lock.amount, sizeof(uint64_t));                // 8 Bytes

    offset += sizeof(uint64_t);

    std::move(lock.secretHash.begin(),                              // 32 Bytes
              lock.secretHash.end(),
              &buffer[offset]);

    offset += HASH_32_LEN;

    buffer[offset] = lock.expirationType;                           // 1 Byte

    offset += sizeof(uint8_t);

    memmove(&buffer[offset], &lock.expiration, sizeof(uint32_t));   // 4 Bytes

    offset += sizeof(uint32_t);

    std::move(lock.recipientId.begin(),                             // 21 Bytes
              lock.recipientId.end(),
              &buffer[offset]);

    offset += ADDRESS_HASH_LEN;

    return offset;
}

////////////////////////////////////////////////////////////////////////////////
// Return a Map of the Htlc Lock asset.
auto HtlcLock::getMap(const HtlcLock &lock)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Amount
    map.emplace("amount", UintToString(lock.amount));

    // Secret Hash
    map.emplace("secretHash", BytesToHex(lock.secretHash));

    // Expiration Type
    map.emplace("expirationType", UintToString(lock.expirationType));

    // Expiration
    map.emplace("expiration", UintToString(lock.expiration));

    // RecipientId
    map.emplace("recipientId", Base58::parseAddressHash(lock.recipientId));

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
