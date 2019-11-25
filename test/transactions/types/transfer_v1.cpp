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

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "fixtures/common.hpp"
#include "fixtures/transfer_v1.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_transfer_v1, deserialize) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, v1::TYPE_0_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V1,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(v1::TYPE_0_TYPE,          data.type);
    ASSERT_EQ(v1::TYPE_0_TIMESTAMP,     data.timestamp);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(v1::TYPE_0_FEE,           data.fee);

    ASSERT_EQ(v1::TYPE_0_AMOUNT,        data.asset.transfer.amount);
    ASSERT_EQ(v1::TYPE_0_EXPIRATION,    data.asset.transfer.expiration);

    ASSERT_TRUE(array_cmp(v1::TYPE_0_RECIPIENT,
                          data.asset.transfer.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(v1::TYPE_0_SIGNATURE,
                          data.signature.data(),
                          data.signature.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_transfer_v1, deserialize_vendorfield) {
    TransactionData data;

    Deserializer::deserialize(&data, v1::TYPE_0_BYTES_VF);

    ASSERT_EQ(COMMON_HEADER,                data.header);
    ASSERT_EQ(COMMON_VERSION_V1,            data.version);
    ASSERT_EQ(COMMON_MAINNET,               data.network);
    ASSERT_EQ(v1::TYPE_0_TYPE,              data.type);
    ASSERT_EQ(v1::TYPE_0_VF_TIMESTAMP,      data.timestamp);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(v1::TYPE_0_FEE,               data.fee);

    ASSERT_TRUE(array_cmp(v1::TYPE_0_VF,
                          data.vendorField.data(),
                          sizeof(v1::TYPE_0_VF)));

    ASSERT_EQ(v1::TYPE_0_AMOUNT,            data.asset.transfer.amount);
    ASSERT_EQ(v1::TYPE_0_EXPIRATION,        data.asset.transfer.expiration);

    ASSERT_TRUE(array_cmp(v1::TYPE_0_RECIPIENT,
                          data.asset.transfer.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(v1::TYPE_0_VF_SIGNATURE,
                          data.signature.data(),
                          data.signature.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_transfer_v1, serialize) {
    TransactionData data;

    data.version        = COMMON_VERSION_V1;
    data.network        = COMMON_MAINNET;
    data.type           = v1::TYPE_0_TYPE;
    data.fee            = v1::TYPE_0_FEE;
    data.timestamp      = v1::TYPE_0_TIMESTAMP;

    data.asset.transfer.amount = v1::TYPE_0_AMOUNT;

    std::move(v1::TYPE_0_RECIPIENT,
              v1::TYPE_0_RECIPIENT + ADDRESS_HASH_LEN,
              data.asset.transfer.recipientId.begin());

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.signature.insert(data.signature.begin(),
                          v1::TYPE_0_SIGNATURE,
                          v1::TYPE_0_SIGNATURE + sizeof(v1::TYPE_0_SIGNATURE));

    ASSERT_TRUE(array_cmp(v1::TYPE_0_BYTES.data(),
                          Serializer::serialize(data).data(),
                          v1::TYPE_0_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_transfer_v1, serialize_vendorfield) {
    TransactionData data;

    data.version        = COMMON_VERSION_V1;
    data.network        = COMMON_MAINNET;
    data.type           = v1::TYPE_0_TYPE;
    data.fee            = v1::TYPE_0_FEE;
    data.timestamp      = v1::TYPE_0_VF_TIMESTAMP;

    data.asset.transfer.amount = v1::TYPE_0_AMOUNT;

    std::move(v1::TYPE_0_RECIPIENT,
              v1::TYPE_0_RECIPIENT + ADDRESS_HASH_LEN,
              data.asset.transfer.recipientId.begin());

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.vendorField.insert(data.vendorField.begin(),
                           v1::TYPE_0_VF,
                           v1::TYPE_0_VF + sizeof(v1::TYPE_0_VF));

    data.signature.insert(
            data.signature.begin(),
            v1::TYPE_0_VF_SIGNATURE,
            v1::TYPE_0_VF_SIGNATURE + sizeof(v1::TYPE_0_VF_SIGNATURE));

    ASSERT_TRUE(array_cmp(v1::TYPE_0_BYTES_VF.data(),
                          Serializer::serialize(data).data(),
                          v1::TYPE_0_BYTES.size()));
}
