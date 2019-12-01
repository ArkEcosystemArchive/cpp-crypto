/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include <map>
#include <string>
#include <utility>

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/common.hpp"
#include "fixtures/htlc_claim.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_claim, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_9_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_9_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_9_FEE,               data.fee);

    ASSERT_TRUE(array_cmp(TYPE_9_LOCK_TX_ID,
                          data.asset.htlcClaim.id.data(),
                          HASH_32_LEN));

    ASSERT_TRUE(array_cmp(TYPE_9_UNLOCK_SECRET,
                          data.asset.htlcClaim.secret.data(),
                          HASH_32_LEN));

    ASSERT_TRUE(array_cmp(TYPE_9_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_9_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_claim, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_9_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.fee            = TYPE_9_FEE;

    std::move(TYPE_9_LOCK_TX_ID,
              TYPE_9_LOCK_TX_ID + HASH_32_LEN,
              data.asset.htlcClaim.id.begin());


    std::move(TYPE_9_UNLOCK_SECRET,
              TYPE_9_UNLOCK_SECRET + HASH_32_LEN,
              data.asset.htlcClaim.secret.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_9_SIGNATURE,
                          TYPE_9_SIGNATURE + sizeof(TYPE_9_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_9_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_9_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_htlc_claim, add_to_map) {
    HtlcClaim claim;

    std::move(TYPE_9_LOCK_TX_ID,
              TYPE_9_LOCK_TX_ID + HASH_32_LEN,
              claim.id.begin());

    std::move(TYPE_9_UNLOCK_SECRET,
              TYPE_9_UNLOCK_SECRET + HASH_32_LEN,
              claim.secret.begin());

    std::map<std::string, std::string> claimMap;

    HtlcClaim::addToMap(claim, claimMap);

    ASSERT_STREQ(TYPE_9_LOCK_ID_STRING,
                 claimMap.find("lockTransactionId")->second.c_str());

    ASSERT_STREQ(TYPE_9_SECRET_STRING,
                 claimMap.find("unlockSecret")->second.c_str());
}
