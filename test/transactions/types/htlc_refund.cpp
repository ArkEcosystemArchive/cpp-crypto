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

#include "fixtures/identity.hpp"
#include "fixtures/common.hpp"
#include "fixtures/htlc_refund.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_refund, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_10_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_10_TYPE,             data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_10_FEE,              data.fee);

    ASSERT_TRUE(array_cmp(TYPE_10_LOCK_TX_ID,
                          data.asset.htlcRefund.id.data(),
                          HASH_32_LEN));

    ASSERT_TRUE(array_cmp(TYPE_10_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_10_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_refund, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_10_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.fee            = TYPE_10_FEE;

    std::move(TYPE_10_LOCK_TX_ID,
              TYPE_10_LOCK_TX_ID + HASH_32_LEN,
              data.asset.htlcRefund.id.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_10_SIGNATURE,
                          TYPE_10_SIGNATURE + sizeof(TYPE_10_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_10_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_10_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_refund, getMap) {
    HtlcRefund refund;

    std::move(TYPE_10_LOCK_TX_ID,
              TYPE_10_LOCK_TX_ID + HASH_32_LEN,
              refund.id.begin());

    const auto refundMap = HtlcRefund::getMap(refund);

    ASSERT_STREQ(TYPE_10_LOCK_ID_STRING,
                 refundMap.find("lockTransactionId")->second.c_str());
}