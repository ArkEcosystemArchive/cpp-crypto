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
#include "fixtures/second_signature.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_second_signature, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_1_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_1_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_1_FEE,               data.fee);
    ASSERT_EQ(TYPE_1_VF_LENGTH,         data.vendorField.size());

    ASSERT_TRUE(array_cmp(TYPE_1_SECOND_PUBLICKEY,
               data.asset.secondSignature.publicKey.data(),
               PUBLICKEY_COMPRESSED_LEN));

    ASSERT_TRUE(array_cmp(TYPE_1_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_1_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_second_signature, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_1_TYPE;
    data.nonce          = COMMON_NONCE;

    std::copy(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.fee            = TYPE_1_FEE;

    std::copy_n(TYPE_1_SECOND_PUBLICKEY,
                PUBLICKEY_COMPRESSED_LEN,
                data.asset.secondSignature.publicKey.begin());

    data.signature.resize(sizeof(TYPE_1_SIGNATURE));
    std::copy_n(TYPE_1_SIGNATURE,
                data.signature.size(),
                data.signature.begin());

    ASSERT_TRUE(array_cmp(TYPE_1_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_1_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_second_signature, add_to_map) {
    SecondSignature secondSignature;

    std::copy_n(TYPE_1_SECOND_PUBLICKEY,
                PUBLICKEY_COMPRESSED_LEN,
                secondSignature.publicKey.begin());

    std::map<std::string, std::string> secondSignatureMap;

    SecondSignature::addToMap(secondSignature, secondSignatureMap);

    ASSERT_STREQ(TYPE_1_PUBLICKEY_STRING,
                 secondSignatureMap.find("publicKey")->second.c_str());
}
