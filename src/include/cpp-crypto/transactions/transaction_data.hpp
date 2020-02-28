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

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

#include "networks/devnet.hpp"

#include "transactions/types/assets.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Transaction Data Model
struct TransactionData {  // LCOV_EXCL_START
    uint8_t                 header      { TRANSACTION_DEFAULT_HEADER };
    uint8_t                 version     { TRANSACTION_VERSION_TYPE_2 };
    uint8_t                 network     { Devnet.version };

    uint32_t                typeGroup   { TRANSACTION_DEFAULT_TYPEGROUP };  // v2
    uint16_t                type        { 0U };     // v1: 1 Byte | v2: 2 Bytes 

    uint64_t                nonce       { 0ULL };   // v2 only
    uint32_t                timestamp   { 0UL };    // v1 only

    PublicKeyBytes          senderPublicKey { };

    uint64_t                fee         { 0ULL };

    std::vector<uint8_t>    vendorField;

    Asset                   asset;

    Hash32                  id { };

    std::vector<uint8_t>    signature;
    std::vector<uint8_t>    secondSignature;

    TransactionData() {
        signature.resize(SIGNATURE_ECDSA_MAX);
        secondSignature.resize(SIGNATURE_ECDSA_MAX);
    };
};  // LCOV_EXCL_STOP


}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
