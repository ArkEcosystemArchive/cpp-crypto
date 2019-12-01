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
#include "fixtures/ipfs.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
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

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
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

    std::move(fixtures::PublicKeyBytes.begin(),
              fixtures::PublicKeyBytes.end(),
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
TEST(transactions_ipfs, invalid_len) {
    Ipfs ipfs;

    // Invalid Ipfs on Deserialization.
    Ipfs::Deserialize(
            &ipfs,
            reinterpret_cast<const uint8_t *>("\0"));

    ASSERT_EQ(0UL, ipfs.dag.size());

    // Invalid Ipfs on Serialization.
    std::array<uint8_t, HASH_64_LEN> buffer {};
    Ipfs::Serialize(ipfs, buffer.data());

    ASSERT_EQ(0U, buffer.at(0));
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_ipfs, add_to_map) {
    Ipfs ipfs;

    ipfs.dag.insert(ipfs.dag.begin(),
                    TYPE_5_DAG,
                    TYPE_5_DAG + sizeof(TYPE_5_DAG));

    std::map<std::string, std::string> ipfsMap;

    Ipfs::addToMap(ipfs, ipfsMap);

    ASSERT_STREQ(TYPE_5_IPFS_STRING,
                 ipfsMap.find("ipfs")->second.c_str());
}
