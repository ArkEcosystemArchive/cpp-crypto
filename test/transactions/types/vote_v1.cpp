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
#include "fixtures/vote_v1.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_vote_v1, deserialize) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, v1::TYPE_3_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V1,        data.version);
    ASSERT_EQ(COMMON_DEVNET,            data.network);
    ASSERT_EQ(v1::TYPE_3_TYPE,          data.type);
    ASSERT_EQ(v1::TYPE_3_TIMESTAMP,     data.timestamp);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(v1::TYPE_3_FEE,           data.fee);

    ASSERT_EQ(v1::TYPE_3_VOTE_COUNT,    data.asset.vote.count);

    ASSERT_TRUE(array_cmp(v1::TYPE_3_VOTE,
                          data.asset.vote.votes.data(),
                          sizeof(v1::TYPE_3_VOTE)));

    ASSERT_TRUE(array_cmp(v1::TYPE_3_SIGNATURE,
                          data.signature.data(),
                          data.signature.size()));

    ASSERT_TRUE(array_cmp(v1::TYPE_3_SECOND_SIG,
                          data.secondSignature.data(),
                          data.secondSignature.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_vote_v1, serialize) {
    TransactionData data;

    data.version        = COMMON_VERSION_V1;
    data.type           = v1::TYPE_3_TYPE;
    data.fee            = v1::TYPE_3_FEE;
    data.timestamp      = v1::TYPE_3_TIMESTAMP;

    std::copy(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.asset.vote.count = 1U;

    std::copy_n(v1::TYPE_3_VOTE, VOTES_LEN, data.asset.vote.votes.begin());

    data.signature.resize(sizeof(v1::TYPE_3_SIGNATURE));
    std::copy_n(v1::TYPE_3_SIGNATURE,
                data.signature.size(),
                data.signature.begin());

    data.secondSignature.resize(sizeof(v1::TYPE_3_SECOND_SIG));
    std::copy_n(v1::TYPE_3_SECOND_SIG,
                data.secondSignature.size(),
                data.secondSignature.begin());

    ASSERT_TRUE(array_cmp(v1::TYPE_3_BYTES.data(),
                          Serializer::serialize(data).data(),
                          v1::TYPE_3_BYTES.size()));
}
