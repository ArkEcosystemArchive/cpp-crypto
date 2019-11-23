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
#include "fixtures/vote.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_vote, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_3_BYTES));
    
    ASSERT_EQ(COMMON_HEADER,        data.header);
    ASSERT_EQ(COMMON_VERSION_V2,    data.version);
    ASSERT_EQ(COMMON_MAINNET,       data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,     data.typeGroup);
    ASSERT_EQ(TYPE_3_TYPE,          data.type);
    ASSERT_EQ(COMMON_NONCE,         data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_3_FEE,           data.fee);

    ASSERT_EQ(TYPE_3_VOTE_COUNT,    data.asset.vote.count);

    ASSERT_TRUE(array_cmp(TYPE_3_VOTE,
                          data.asset.vote.votes.data(),
                          sizeof(TYPE_3_VOTE)));

    ASSERT_TRUE(array_cmp(TYPE_3_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_3_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_vote, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_3_TYPE;
    data.nonce          = COMMON_NONCE;

    memmove(&data.senderPublicKey,
            COMMON_PUBLICKEY,
            PUBLICKEY_COMPRESSED_LEN);

    data.fee            = TYPE_3_FEE;

    data.asset.vote.count = 1U;
    memmove(&data.asset.vote.votes, TYPE_3_VOTE, sizeof(TYPE_3_VOTE));

    data.signature.insert(data.signature.begin(),
                          TYPE_3_SIGNATURE,
                          TYPE_3_SIGNATURE + sizeof(TYPE_3_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_3_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_3_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_vote, getMap) {
    Vote vote;

    vote.count = TYPE_3_VOTE_COUNT;
    memmove(&vote.votes, TYPE_3_VOTE, VOTE_LEN);

    const auto voteMap = Vote::getMap(vote);

    ASSERT_STREQ(TYPE_3_VOTES_STRING,
                 voteMap.find("votes")->second.c_str());
}

////////////////////////////////////////////////////////////////////////////////
