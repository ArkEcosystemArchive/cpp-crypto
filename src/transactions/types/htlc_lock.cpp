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
// - memmove(&lock.secretHash, &buffer[8], 32);
//
// Expiration Type- 1 Byte
// - lock.expirationType = buffer[40];
//
// Expiration Value - 4 Bytes
// - lock.expirationValue = unpack4LE(buffer, 41);
//
// Recipient - 21 Bytes
// - memmove(&lock.recipientId, &buffer[45], 21);
//
// ---
auto HtlcLock::Deserialize(HtlcLock *lock, const uint8_t *buffer) -> uint32_t {
    lock->amount             = unpack8LE(buffer, 0U);               // 8 Bytes

    memmove(&lock->secretHash,                                      // 32 Bytes
            &buffer[sizeof(uint64_t)],
            HASH_32_LEN);

    lock->expirationType = buffer[sizeof(uint64_t) + HASH_32_LEN];  // 1 Byte

    lock->expiration = unpack4LE(buffer, sizeof(uint64_t) +         // 4 Bytes
                                         HASH_32_LEN +
                                         sizeof(uint8_t));

    memmove(&lock->recipientId,                                     // 21 Bytes
            &buffer[sizeof(uint64_t) +
                    HASH_32_LEN +
                    sizeof(uint8_t) +
                    sizeof(uint32_t)],
            ADDRESS_HASH_LEN);

    return HTLC_LOCK_SIZE;                                          // 66 Bytes
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
// - memmove(buffer, &lock.amount, sizeof(uint64_t));
//
// Secret Hash - 32 Bytes
// - memmove(&buffer[8], &lock.secretHash, 32);
//
// Expiration Type- 1 Byte
// - buffer[40] = lock.expirationType;
//
// Expiration Value - 4 Bytes
// - memmove(&buffer[41], &lock.expirationValue, 4);
//
// Recipient - 21 Bytes
// - memmove(&buffer[45], &lock.recipientId, 21)
//
// ---
auto HtlcLock::Serialize(const HtlcLock &lock, uint8_t *buffer) -> uint32_t {
    memmove(buffer, &lock.amount, sizeof(uint64_t));                // 8 Bytes

    memmove(&buffer[sizeof(uint64_t)],                              // 32 Bytes
            &lock.secretHash,
            HASH_32_LEN);

    buffer[sizeof(uint64_t) + HASH_32_LEN] = lock.expirationType;   // 1 Byte

    memmove(&buffer[sizeof(uint64_t) +                              // 4 Bytes
                    HASH_32_LEN + sizeof(uint8_t)],
            &lock.expiration,
            sizeof(uint32_t));

    memmove(&buffer[sizeof(uint64_t) +                              // 21 Bytes
                    HASH_32_LEN +
                    sizeof(uint8_t) +
                    sizeof(uint32_t)],
            &lock.recipientId,
            ADDRESS_HASH_LEN);  

    return HTLC_LOCK_SIZE;                                          // 66 Bytes
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

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
