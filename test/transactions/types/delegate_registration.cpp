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
#include "fixtures/delegate_registration.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_delegate_registration, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_2_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_2_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_2_FEE,               data.fee);

    ASSERT_EQ(TYPE_2_USERNAME_LENGTH, data.asset.delegateRegistration.length);

    ASSERT_TRUE(array_cmp(TYPE_2_USERNAME,
                          data.asset.delegateRegistration.username.data(),
                          data.asset.delegateRegistration.length));

    ASSERT_TRUE(array_cmp(TYPE_2_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_2_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_delegate_registration, serialize_ecdsa) {
    TransactionData data;

    data.network        = COMMON_MAINNET;
    data.typeGroup      = COMMON_TYPEGROUP;
    data.type           = TYPE_2_TYPE;
    data.nonce          = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee            = TYPE_2_FEE;

    data.asset.delegateRegistration.length = TYPE_2_USERNAME_LENGTH;

    std::move(TYPE_2_USERNAME,
              TYPE_2_USERNAME + TYPE_2_USERNAME_LENGTH,
              data.asset.delegateRegistration.username.begin());

    data.signature.insert(data.signature.begin(),
                          TYPE_2_SIGNATURE,
                          TYPE_2_SIGNATURE + sizeof(TYPE_2_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_2_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_2_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_delegate_registration, getMap) {
    DelegateRegistration delegateRegistration;

    delegateRegistration.length = TYPE_2_USERNAME_LENGTH;

    std::move(TYPE_2_USERNAME,
              TYPE_2_USERNAME + TYPE_2_USERNAME_LENGTH,
              delegateRegistration.username.begin());

    const auto delegateRegistrationMap =
        DelegateRegistration::getMap(delegateRegistration);

    ASSERT_STREQ(TYPE_2_USERNAME_LEN_STRING,
                 delegateRegistrationMap.find("usernameLen")->second.c_str());

    ASSERT_STREQ(TYPE_2_USERNAME_STRING,
                 delegateRegistrationMap.find("username")->second.c_str());
}

////////////////////////////////////////////////////////////////////////////////
