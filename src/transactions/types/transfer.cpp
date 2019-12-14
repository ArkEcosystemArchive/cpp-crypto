/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/transfer.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/json.h"
#include "utils/packing.h"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Transfer (Type 0) - 33 bytes
//
// @param Transfer *transfer
// @param uint8_t *buffer: The serialized buffer beginning at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Amount - 8 Bytes:
// - transfer.amount = unpack8LE(buffer, 0);
//
// Expiration - 4 Bytes:
// - transfer.expiration = unpack4LE(buffer, sizeof(uint64_t));
//
// Recipient - 21 Bytes:
// - std::copy_n(&buffer[12], 21, transfer->recipientId.begin());
//
// ---
auto Transfer::Deserialize(Transfer *transfer, const uint8_t *buffer)
        -> size_t {
    transfer->amount        = unpack8LE(buffer, 0U);                // 8 Bytes
    transfer->expiration    = unpack4LE(buffer, sizeof(uint64_t));  // 4 Bytes

    std::copy_n(&buffer[sizeof(uint64_t) + sizeof(uint32_t)],       // 21 Bytes
                ADDRESS_HASH_LEN,
                transfer->recipientId.begin());

    return TRANSACTION_TYPE_TRANSFER_SIZE;                          // 33 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Transfer (Type 0) - 33 bytes
//
// @param const Transfer &transfer
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Amount - 8 Bytes:
// - pack8LE(buffer, &transfer.amount);
//
// Expiration - 4 Bytes:
// - pack4LE(&buffer[sizeof(uint64_t)], &transfer.expiration);
//
// Recipient - 21 Bytes:
// - std::copy(transfer.recipientId.begin(), transfer.recipientId.end(), &buffer[12]);
//
// ---
auto Transfer::Serialize(const Transfer &transfer, uint8_t *buffer) -> size_t {
    pack8LE(buffer, &transfer.amount);                              // 8 Bytes

    pack4LE(&buffer[sizeof(uint64_t)], &transfer.expiration);       // 4 Bytes

    std::copy(transfer.recipientId.begin(),                         // 21 Bytes
              transfer.recipientId.end(),
              &buffer[sizeof(uint64_t) + sizeof(uint32_t)]);

    return TRANSACTION_TYPE_TRANSFER_SIZE;                          // 33 Bytes
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constantsconst auto KEY_AMOUNT_LABEL         = "amount";
constexpr auto KEY_AMOUNT_LABEL         = "amount";
const auto KEY_AMOUNT_SIZE              = strlen(KEY_AMOUNT_LABEL);

constexpr auto KEY_EXPIRATION_LABEL     = "expiration";
const auto KEY_EXPIRATION_SIZE          = strlen(KEY_EXPIRATION_LABEL);

constexpr auto KEY_RECIPIENT_ID_LABEL   = "recipientId";
const auto KEY_RECIPIENT_ID_SIZE        = strlen(KEY_RECIPIENT_ID_LABEL);

////////////////////////////////////////////////////////////////////////////////
// Add Transfer Asset data to a Transaction Map.
void Transfer::addToMap(const Transfer &transfer,
                        std::map<std::string, std::string> &map) {
    // Amount
    map.emplace(KEY_AMOUNT_LABEL, UintToString(transfer.amount));

    // Expiration
    map.emplace(KEY_EXPIRATION_LABEL, UintToString(transfer.expiration));

    // RecipientId
    map.emplace(KEY_RECIPIENT_ID_LABEL, Base58::parseAddressHash(transfer.recipientId));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Transfer-type Transaction.
auto Transfer::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1) + KEY_AMOUNT_SIZE + UINT64_MAX_CHARS +
           JSON_OBJECT_SIZE(1) + KEY_EXPIRATION_SIZE + UINT32_MAX_CHARS +
           JSON_OBJECT_SIZE(1) + KEY_RECIPIENT_ID_SIZE + ADDRESS_STR_LEN;
}

////////////////////////////////////////////////////////////////////////////////
// Add Transfer data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Transfer data.
//
// ---
void Transfer::addToJson(DynamicJsonDocument &jsonDoc,
                         const std::map<std::string, std::string> &map) {
    // Amount
    jsonDoc[KEY_AMOUNT_LABEL] = map.at(KEY_AMOUNT_LABEL);

    // Expiration
    jsonDoc[KEY_EXPIRATION_LABEL] = strtol(map.at(KEY_EXPIRATION_LABEL).c_str(),
                                       nullptr,
                                       BASE_10);

    // RecipientId
    jsonDoc[KEY_RECIPIENT_ID_LABEL] = map.at(KEY_RECIPIENT_ID_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
