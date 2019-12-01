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
#include "utils/json.h"
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
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
const auto OBJECT_HTLC_LOCK_LABEL       = "lock";
const auto OBJECT_HTLC_LOCK_SIZE        = strlen(OBJECT_HTLC_LOCK_LABEL) - 1U;

const auto OBJECT_HTLC_LOCK_TYPE_LABEL      = "type";
const auto OBJECT_HTLC_LOCK_VALUE_LABEL     = "value";

const auto KEY_AMOUNT_LABEL             = "amount";
const auto KEY_AMOUNT_SIZE              = strlen(KEY_AMOUNT_LABEL);

const auto KEY_SECRET_HASH_LABEL        = "secretHash";
const auto KEY_SECRET_HASH_SIZE         = strlen(KEY_SECRET_HASH_LABEL);

const auto KEY_EXPIRATION_TYPE_LABEL    = "expirationType";
const auto KEY_EXPIRATION_TYPE_SIZE     = strlen(KEY_EXPIRATION_TYPE_LABEL);

const auto KEY_EXPIRATION_LABEL         = "expiration";
const auto KEY_EXPIRATION_SIZE          = strlen(KEY_EXPIRATION_LABEL);

const auto KEY_RECIPIENT_ID_LABEL       = "recipientId";
const auto KEY_RECIPIENT_ID_SIZE        = strlen(KEY_RECIPIENT_ID_LABEL);

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Lock Asset data to a Transaction Map.
void HtlcLock::addToMap(const HtlcLock &lock,
                        std::map<std::string, std::string> &map) {
    // Amount
    map.emplace(KEY_AMOUNT_LABEL, UintToString(lock.amount));

    // Secret Hash
    map.emplace(KEY_SECRET_HASH_LABEL, BytesToHex(lock.secretHash));

    // Expiration Type
    map.emplace(KEY_EXPIRATION_TYPE_LABEL, UintToString(lock.expirationType));

    // Expiration
    map.emplace(KEY_EXPIRATION_LABEL, UintToString(lock.expiration));

    // RecipientId
    map.emplace(KEY_RECIPIENT_ID_LABEL, Base58::parseAddressHash(lock.recipientId));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Htlc Lock-type Transaction.
auto HtlcLock::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1)  + KEY_AMOUNT_SIZE + UINT64_MAX_CHARS +
           JSON_OBJECT_SIZE(1)  + KEY_RECIPIENT_ID_SIZE + ADDRESS_STR_LEN +
           JSON_OBJECT_SIZE(1)  + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1)  + OBJECT_HTLC_LOCK_SIZE +
           JSON_OBJECT_SIZE(1)  + KEY_SECRET_HASH_SIZE + HASH_32_MAX_CHARS +
           JSON_OBJECT_SIZE(1)  + KEY_EXPIRATION_SIZE +
           JSON_OBJECT_SIZE(1)  + KEY_EXPIRATION_TYPE_SIZE + UINT8_MAX_CHARS +
           JSON_OBJECT_SIZE(1)  + KEY_EXPIRATION_SIZE + UINT32_MAX_CHARS;
}

////////////////////////////////////////////////////////////////////////////////
// Add Htlc Lock data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Htlc Lock data.
//
// ---
void HtlcLock::addToJson(DynamicJsonDocument &jsonDoc,
                         const std::map<std::string, std::string> &map) {
    // Amount
    jsonDoc[KEY_AMOUNT_LABEL] = map.at(KEY_AMOUNT_LABEL);

    // RecipientId
    jsonDoc[KEY_RECIPIENT_ID_LABEL] = map.at(KEY_RECIPIENT_ID_LABEL);

    const auto asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    const auto lock = asset.createNestedObject(OBJECT_HTLC_LOCK_LABEL);

    // Secret Hash
    lock[KEY_SECRET_HASH_LABEL] = map.at(KEY_SECRET_HASH_LABEL);

    const auto expiration = lock.createNestedObject(KEY_EXPIRATION_LABEL);

    // Expiration Type
    expiration[OBJECT_HTLC_LOCK_TYPE_LABEL] =
            strtol(map.at(KEY_EXPIRATION_TYPE_LABEL).c_str(),
                   nullptr,
                   BASE_10);

    // Expiration Value
    expiration[OBJECT_HTLC_LOCK_VALUE_LABEL] =
        strtol(map.at(KEY_EXPIRATION_LABEL).c_str(),
               nullptr,
               BASE_10);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
