/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "fixtures/common.hpp"
#include "fixtures/second_signature_v1.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_v1, deserialize_second_signature_registration) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, v1::TYPE_1_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V1,        data.version);
    ASSERT_EQ(COMMON_DEVNET,            data.network);
    ASSERT_EQ(v1::TYPE_1_TYPE,          data.type);
    ASSERT_EQ(v1::TYPE_1_TIMESTAMP,     data.timestamp);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(v1::TYPE_1_FEE,           data.fee);

    ASSERT_TRUE(array_cmp(v1::TYPE_1_SECOND_PUBLICKEY,
               data.asset.secondSignature.publicKey.data(),
               PUBLICKEY_COMPRESSED_LEN));

    ASSERT_TRUE(array_cmp(v1::TYPE_1_SIGNATURE,
                          data.signature.data(),
                          data.signature.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_v1, serialize_second_signature_registration) {
    TransactionData data;

    data.version        = COMMON_VERSION_V1;
    data.type           = v1::TYPE_1_TYPE;
    data.fee            = v1::TYPE_1_FEE;
    data.timestamp      = v1::TYPE_1_TIMESTAMP;

    memmove(&data.senderPublicKey, COMMON_PUBLICKEY, PUBLICKEY_COMPRESSED_LEN);

    memmove(&data.asset.secondSignature.publicKey,
            v1::TYPE_1_SECOND_PUBLICKEY,
            PUBLICKEY_COMPRESSED_LEN);

    data.signature.insert(data.signature.begin(),
                          v1::TYPE_1_SIGNATURE,
                          v1::TYPE_1_SIGNATURE + sizeof(v1::TYPE_1_SIGNATURE));

    ASSERT_TRUE(array_cmp(v1::TYPE_1_BYTES.data(),
                          Serializer::serialize(data).data(),
                          v1::TYPE_1_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
