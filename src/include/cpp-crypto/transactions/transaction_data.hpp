/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TRANSACTION_DATA_HPP
#define ARK_TRANSACTIONS_TRANSACTION_DATA_HPP

#include <cstdint>
#include <vector>

#include "interfaces/identities.hpp"

#include "transactions/types/assets.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Transaction Data Model
typedef struct transaction_data_t {
    uint8_t                 header;
    uint8_t                 version;
    uint8_t                 network;

    uint32_t                typeGroup;  // v2 only
    uint16_t                type;       // v1: 1 Byte | v2: 2 Bytes 

    uint64_t                nonce;      // v2 only
    uint32_t                timestamp;  // v1 only

    PublicKeyBytes          senderPublicKey;

    uint64_t                fee;

    std::vector<uint8_t>    vendorField;

    Asset                   asset;

    std::vector<uint8_t>    signature;
    std::vector<uint8_t>    secondSignature;

    transaction_data_t() : header(0xFF),
                           version(0x02),
                           network(0x1E),
                           typeGroup(1UL),
                           type(0U),
                           nonce(0ULL),
                           timestamp(0UL),
                           senderPublicKey(),
                           fee(0ULL),
                           vendorField() {}
} TransactionData;


}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
