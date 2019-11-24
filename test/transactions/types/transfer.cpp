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
#include "fixtures/transfer.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transfer, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_0_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_0_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_0_FEE,               data.fee);
    ASSERT_EQ(TYPE_0_NVF_LENGTH,        data.vendorField.size());

    ASSERT_EQ(TYPE_0_AMOUNT,            data.asset.transfer.amount);
    ASSERT_EQ(TYPE_0_EXPIRATION,        data.asset.transfer.expiration);

    ASSERT_TRUE(array_cmp(TYPE_0_RECIPIENT,
                          data.asset.transfer.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(TYPE_0_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_0_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transfer, deserialize_vendorfield_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_0_VF_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_0_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_0_FEE,               data.fee);
    ASSERT_EQ(TYPE_0_VF_LENGTH,         data.vendorField.size());

    ASSERT_TRUE(array_cmp(TYPE_0_VF,
                          data.vendorField.data(),
                          sizeof(TYPE_0_VF)));

    ASSERT_EQ(TYPE_0_AMOUNT,            data.asset.transfer.amount);
    ASSERT_EQ(TYPE_0_EXPIRATION,        data.asset.transfer.expiration);

    ASSERT_TRUE(array_cmp(TYPE_0_RECIPIENT,
                          data.asset.transfer.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(TYPE_0_VF_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_0_VF_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transfer, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_0_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee            = TYPE_0_FEE;

    data.asset.transfer.amount      = TYPE_0_AMOUNT;
    data.asset.transfer.expiration  = TYPE_0_EXPIRATION;

    std::move(TYPE_0_RECIPIENT,
              TYPE_0_RECIPIENT + ADDRESS_HASH_LEN,
              data.asset.transfer.recipientId.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_0_SIGNATURE,
                          TYPE_0_SIGNATURE + sizeof(TYPE_0_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_0_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_0_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transfer, serialize_vendorfield_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_0_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee            = TYPE_0_FEE;

    data.vendorField.insert(data.vendorField.begin(),
                            TYPE_0_VF,
                            TYPE_0_VF + sizeof(TYPE_0_VF));

    data.asset.transfer.amount       = TYPE_0_AMOUNT;
    data.asset.transfer.expiration   = TYPE_0_EXPIRATION;

    std::move(TYPE_0_RECIPIENT,
              TYPE_0_RECIPIENT + ADDRESS_HASH_LEN,
              data.asset.transfer.recipientId.begin());

    data.signature.insert(data.signature.begin(),
                         TYPE_0_VF_SIGNATURE,
                         TYPE_0_VF_SIGNATURE + sizeof(TYPE_0_VF_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_0_VF_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_0_VF_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transfer, getMap) {
    Transfer transfer;

    transfer.amount         = TYPE_0_AMOUNT;
    transfer.expiration     = TYPE_0_EXPIRATION;

    std::move(TYPE_0_RECIPIENT,
              TYPE_0_RECIPIENT + ADDRESS_HASH_LEN,
              transfer.recipientId.begin());

    const auto transferMap = Transfer::getMap(transfer);

    ASSERT_STREQ(TYPE_0_AMOUNT_STRING,
                 transferMap.find("amount")->second.c_str());

    ASSERT_STREQ(TYPE_0_EXPIRATION_STRING,
                 transferMap.find("expiration")->second.c_str());

    ASSERT_STREQ(TYPE_0_RECIPIENT_ID_STRING,
                 transferMap.find("recipientId")->second.c_str());
}

////////////////////////////////////////////////////////////////////////////////
