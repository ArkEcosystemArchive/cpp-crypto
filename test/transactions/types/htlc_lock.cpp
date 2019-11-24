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
#include "fixtures/htlc_lock.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_htlc_lock, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_8_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_8_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_8_FEE,               data.fee);

    ASSERT_EQ(TYPE_8_AMOUNT,            data.asset.htlcLock.amount);

    ASSERT_TRUE(array_cmp(TYPE_8_SECRET_HASH,
                          data.asset.htlcLock.secretHash.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_EQ(TYPE_8_EXPIRATION_TYPE, data.asset.htlcLock.expirationType);

    ASSERT_EQ(TYPE_8_EXPIRATION_VALUE, data.asset.htlcLock.expiration);

    ASSERT_TRUE(array_cmp(TYPE_8_RECIPIENT,
                          data.asset.htlcLock.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(TYPE_8_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_8_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_htlc_lock, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_8_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee            = TYPE_8_FEE;

    data.asset.htlcLock.amount = TYPE_8_AMOUNT;

    std::move(TYPE_8_SECRET_HASH, TYPE_8_SECRET_HASH + HASH_32_LEN, data.asset.htlcLock.secretHash.begin());


    data.asset.htlcLock.expirationType   = TYPE_8_EXPIRATION_TYPE;
    data.asset.htlcLock.expiration       = TYPE_8_EXPIRATION_VALUE;

    std::move(TYPE_8_RECIPIENT,
              TYPE_8_RECIPIENT + ADDRESS_HASH_LEN,
              data.asset.htlcLock.recipientId.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_8_SIGNATURE,
                          TYPE_8_SIGNATURE + sizeof(TYPE_8_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_8_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_8_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_htlc_lock, getMap) {
    HtlcLock lock;

    lock.amount             = TYPE_8_AMOUNT;

    std::move(TYPE_8_SECRET_HASH,
              TYPE_8_SECRET_HASH + HASH_32_LEN,
              lock.secretHash.begin());

    lock.expirationType     = TYPE_8_EXPIRATION_TYPE;
    lock.expiration         = TYPE_8_EXPIRATION_VALUE;

    std::move(TYPE_8_RECIPIENT,
              TYPE_8_RECIPIENT + ADDRESS_HASH_LEN,
              lock.recipientId.begin());

    const auto lockMap = HtlcLock::getMap(lock);

    ASSERT_STREQ(TYPE_8_AMOUNT_STRING,
                 lockMap.find("amount")->second.c_str());

    ASSERT_STREQ(TYPE_8_SECRET_STRING,
                 lockMap.find("secretHash")->second.c_str());

    ASSERT_STREQ(TYPE_8_EXPIRATION_TYPE_STRING,
                 lockMap.find("expirationType")->second.c_str());

    ASSERT_STREQ(TYPE_8_EXPIRATION_VALUE_STRING,
                 lockMap.find("expiration")->second.c_str());

    ASSERT_STREQ(TYPE_8_RECIPIENT_STRING,
                 lockMap.find("recipientId")->second.c_str());
}

////////////////////////////////////////////////////////////////////////////////
