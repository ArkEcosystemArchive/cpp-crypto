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
#include <vector>

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/common.hpp"
#include "fixtures/delegate_registration_v1.hpp"

#include "test_helpers.h"

#include "utils/hex.hpp"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_delegate_registration_v1, deserialize) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, v1::TYPE_2_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V1,        data.version);
    ASSERT_EQ(COMMON_DEVNET,            data.network);

    ASSERT_EQ(v1::TYPE_2_TYPE,          data.type);
    ASSERT_EQ(v1::TYPE_2_TIMESTAMP,     data.timestamp);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(v1::TYPE_2_FEE,           data.fee);

    ASSERT_TRUE(array_cmp(v1::TYPE_2_USERNAME,
                          data.asset.delegateRegistration.username.data(),
                          data.asset.delegateRegistration.length));
               
    ASSERT_TRUE(array_cmp(v1::TYPE_2_SIGNATURE,
                          data.signature.data(),
                          data.signature.size()));

    ASSERT_TRUE(array_cmp(v1::TYPE_2_SECOND_SIG,
                          data.secondSignature.data(),
                          data.secondSignature.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_delegate_registration_v1, serialize) {
    TransactionData data;

    data.version         = COMMON_VERSION_V1;
    data.type            = v1::TYPE_2_TYPE;
    data.fee             = v1::TYPE_2_FEE;
    data.timestamp       = v1::TYPE_2_TIMESTAMP;

    std::copy(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
              data.senderPublicKey.begin());

    data.asset.delegateRegistration.length = v1::TYPE_2_USERNAME_LENGTH;

    std::copy_n(v1::TYPE_2_USERNAME,
                v1::TYPE_2_USERNAME_LENGTH,
                data.asset.delegateRegistration.username.begin());

    data.signature.resize(sizeof(v1::TYPE_2_SIGNATURE));
    std::copy_n(v1::TYPE_2_SIGNATURE,
                data.signature.size(),
                data.signature.begin());

    data.secondSignature.resize(sizeof(v1::TYPE_2_SECOND_SIG));
    std::copy_n(v1::TYPE_2_SECOND_SIG,
                data.secondSignature.size(),
                data.secondSignature.begin());

    const auto serialized = Serializer::serialize(data);

    ASSERT_TRUE(array_cmp(v1::TYPE_2_BYTES.data(),
                          serialized.data(),
                          serialized.size()));
}
