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
#include "fixtures/ipfs.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_ipfs, deserialize_ecdsa) {
    TransactionData data;

    ASSERT_TRUE(Deserializer::deserialize(&data, TYPE_5_BYTES));

    ASSERT_EQ(COMMON_HEADER,            data.header);
    ASSERT_EQ(COMMON_VERSION_V2,        data.version);
    ASSERT_EQ(COMMON_MAINNET,           data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,         data.typeGroup);
    ASSERT_EQ(TYPE_5_TYPE,              data.type);
    ASSERT_EQ(COMMON_NONCE,             data.nonce);

    ASSERT_TRUE(array_cmp(COMMON_PUBLICKEY,
                          data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_5_FEE,               data.fee);

    ASSERT_TRUE(array_cmp(TYPE_5_DAG,
                          data.asset.ipfs.dag.data(),
                          sizeof(TYPE_5_DAG)));

    ASSERT_TRUE(array_cmp(TYPE_5_SIGNATURE,
                          data.signature.data(),
                          sizeof(TYPE_5_SIGNATURE)));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_ipfs, serialize_ecdsa) {
    TransactionData data;

    data.network            = COMMON_MAINNET;
    data.typeGroup          = COMMON_TYPEGROUP;
    data.type               = TYPE_5_TYPE;
    data.nonce              = COMMON_NONCE;

    std::move(COMMON_PUBLICKEY,
              COMMON_PUBLICKEY + PUBLICKEY_COMPRESSED_LEN,
              data.senderPublicKey.begin());

    data.fee                = TYPE_5_FEE;

    data.asset.ipfs.dag.insert(data.asset.ipfs.dag.begin(),
                               TYPE_5_DAG,
                               TYPE_5_DAG + sizeof(TYPE_5_DAG));

    data.signature.insert(data.signature.begin(),
                          TYPE_5_SIGNATURE,
                          TYPE_5_SIGNATURE + sizeof(TYPE_5_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_5_BYTES.data(),
                          Serializer::serialize(data).data(),
                          TYPE_5_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_ipfs, getMap) {
    Ipfs ipfs;

    ipfs.dag.insert(ipfs.dag.begin(),
                    TYPE_5_DAG,
                    TYPE_5_DAG + sizeof(TYPE_5_DAG));

    const auto ipfsMap = Ipfs::getMap(ipfs);

    ASSERT_STREQ(TYPE_5_IPFS_LEN_STRING,
                 ipfsMap.find("ipfsLen")->second.c_str());

    ASSERT_STREQ(TYPE_5_IPFS_STRING,
                 ipfsMap.find("ipfs")->second.c_str());
}

////////////////////////////////////////////////////////////////////////////////
