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
#include "fixtures/multi_payment.hpp"

#include "test_helpers.h"

#include "utils/platform.h"

#ifndef USE_IOT

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_multi_payment, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_6_BYTES));

    ASSERT_EQ(COMMON_HEADER,        data.header);
    ASSERT_EQ(COMMON_VERSION_V2,    data.version);
    ASSERT_EQ(COMMON_DEVNET,        data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,     data.typeGroup);
    ASSERT_EQ(TYPE_6_TYPE,          data.type);
    ASSERT_EQ(COMMON_NONCE,         data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_6_FEE,           data.fee);

    ASSERT_EQ(TYPE_6_AMOUNT,        data.asset.multiPayment.amounts.at(0));

    ASSERT_EQ(TYPE_6_FIRST_ADDRESS[0],
               data.asset.multiPayment.addresses.at(0).at(0));

    ASSERT_TRUE(array_cmp(&TYPE_6_FIRST_ADDRESS[1],
                          &data.asset.multiPayment.addresses.at(0).at(1),
                          HASH_20_LEN));

    ASSERT_EQ(TYPE_6_AMOUNT, data.asset.multiPayment.amounts.back());

    ASSERT_EQ(TYPE_6_LAST_ADDRESS[0],
               data.asset.multiPayment.addresses.back().at(0));

    ASSERT_TRUE(array_cmp(&TYPE_6_LAST_ADDRESS[1],
                          &data.asset.multiPayment.addresses.back().at(1),
                          HASH_20_LEN));

    ASSERT_TRUE(array_cmp(TYPE_6_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_6_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_multi_payment, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_DEVNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_6_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee            = TYPE_6_FEE;

    data.asset.multiPayment.n_payments = TYPE_6_N_PAYMENTS;

    data.asset.multiPayment.amounts.resize(TYPE_6_N_PAYMENTS);
    data.asset.multiPayment.addresses.resize(TYPE_6_N_PAYMENTS);

    uint32_t offset = TYPE_6_ASSET_OFFSET + sizeof(uint16_t);

    for (uint8_t i = 0U; i < TYPE_6_N_PAYMENTS; ++i) {
        data.asset.multiPayment.amounts.at(i) = TYPE_6_AMOUNT;

        offset += sizeof(uint64_t);

        data.asset.multiPayment.addresses.at(i).at(0) = TYPE_6_BYTES[offset];

        std::move(&TYPE_6_BYTES[offset + 1U],
                  &TYPE_6_BYTES[offset + 1U] + HASH_20_LEN,
                  &data.asset.multiPayment.addresses.at(i).at(1));

        offset += ADDRESS_HASH_LEN;
    }

    data.signature.insert(data.signature.begin(),
                          TYPE_6_SIGNATURE,
                          TYPE_6_SIGNATURE + sizeof(TYPE_6_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_6_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_6_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
// MultiPayment Map setup can be quite a bit of overhead.
// Let's save some trade a little space for Deserialization overhead.
TEST(transactions_multi_payment, getMap) {
    TransactionData data;
    Deserializer::deserialize(&data, TYPE_6_BYTES);

    const auto multiPaymentMap = MultiPayment::getMap(data.asset.multiPayment);

    ASSERT_STREQ(TYPE_6_N_PAYMENTS_STRING,
                 multiPaymentMap.find("n_payments")->second.c_str());

    ASSERT_STREQ(TYPE_6_AMOUNTS_STRING,
                 multiPaymentMap.find("amounts")->second.c_str());

    ASSERT_STREQ(TYPE_6_ADDRESSES_STRING,
                 multiPaymentMap.find("addresses")->second.c_str());
}

#endif // #ifndef USE_IOT
