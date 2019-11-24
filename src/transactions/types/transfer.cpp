/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/transfer.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"
#include "utils/unpack.h"

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
// - std::move(&buffer[12], &buffer[33], transfer->recipientId.begin());
//
// ---
auto Transfer::Deserialize(Transfer *transfer, const uint8_t *buffer)
        -> uint32_t {
    transfer->amount        = unpack8LE(buffer, 0U);                 // 8 Bytes
    transfer->expiration    = unpack4LE(buffer, sizeof(uint64_t));   // 4 Bytes

    std::move(&buffer[sizeof(uint64_t) + sizeof(uint32_t)],         // 21 Bytes
              &buffer[sizeof(uint64_t) + sizeof(uint32_t)] + ADDRESS_HASH_LEN,
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
// - memmove(&buffer[0], &transfer.amount, sizeof(uint64_t));
//
// Expiration - 4 Bytes:
// - memmove(&buffer[sizeof(uint64_t)], &transfer.expiration, sizeof(uint32_t));
//
// Recipient - 21 Bytes:
// - std::move(transfer.recipientId.begin(), transfer.recipientId.end(), &buffer[12]);
//
// ---
auto Transfer::Serialize(const Transfer &transfer, uint8_t *buffer) -> uint32_t {
    memmove(&buffer[0],                                             // 8 Bytes
            &transfer.amount,
            sizeof(uint64_t));

    memmove(&buffer[sizeof(uint64_t)],                              // 4 Bytes
            &transfer.expiration,
            sizeof(uint32_t));

    std::move(transfer.recipientId.begin(),                         // 21 Bytes
              transfer.recipientId.end(),
              &buffer[sizeof(uint64_t) + sizeof(uint32_t)]);

    return TRANSACTION_TYPE_TRANSFER_SIZE;                          // 33 Bytes
}

////////////////////////////////////////////////////////////////////////////////

// Return a Map of the Transfer asset.
auto Transfer::getMap(const Transfer &transfer)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    // Amount
    map.emplace("amount", UintToString(transfer.amount));

    // Expiration
    map.emplace("expiration", UintToString(transfer.expiration));

    // RecipientId
    map.emplace("recipientId", Base58::parseAddressHash(transfer.recipientId));

    return map;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
