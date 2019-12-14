/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include <utility>

#include "transactions/serializer.hpp"
#include "transactions/transaction_data.hpp"

#include "transactions/defaults/offsets.hpp"

#include "fixtures/identity.hpp"
#include "types/fixtures/transfer.hpp"
#include "types/fixtures/common.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
// Break serialization with an invalid version.
// All other cases are tested via transaction types.
TEST(transactions_serializer, serialize_invalid_version) {
    TransactionData data;

    // break serialization.
    // the API only accepts v1 or v2.
    data.version        = 0U;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_0_TYPE;
    data.nonce          = COMMON_NONCE;

    std::copy(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.fee            = TYPE_0_FEE;

    data.asset.transfer.amount      = TYPE_0_AMOUNT;
    data.asset.transfer.expiration  = TYPE_0_EXPIRATION;

    std::copy_n(TYPE_0_RECIPIENT,
                ADDRESS_HASH_LEN,
                data.asset.transfer.recipientId.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_0_SIGNATURE,
                          TYPE_0_SIGNATURE + sizeof(TYPE_0_SIGNATURE));

    const auto serialized = Serializer::serialize(data);

    ASSERT_TRUE(serialized.empty());
}

////////////////////////////////////////////////////////////////////////////////
// Serialize with an unknown type.
// For compatiblity with future Tx types, this should not fail.
// All other cases are tested via transaction types.
TEST(transactions_serializer, serialize_unknown_type_no_fail) {
    TransactionData data;

    const auto unknownType = 100U;
    data.type = unknownType;
    // auto unknownTypeBytes = TYPE_0_BYTES;
    // unknownTypeBytes.at(TYPE_OFFSET) = unknowntype;

    const auto serialized = Serializer::serialize(data);

    ASSERT_FALSE(serialized.empty());
}
