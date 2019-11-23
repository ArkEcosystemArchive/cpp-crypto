/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "utils/base58.hpp"

#include "fixtures/identity.hpp"

#include "transactions/types/fixtures/ipfs.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace fixtures::identity;

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, check_encode) {
    const auto ipfsHash = Base58::checkEncode(TYPE_5_DAG, sizeof(TYPE_5_DAG));
    ASSERT_STREQ(TYPE_5_IPFS_STRING, ipfsHash.c_str());
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, check_encode_invalid) {
    const auto base58Threshold = 164;
    const auto invalidHash = Base58::checkEncode(nullptr, base58Threshold + 1);
    ASSERT_TRUE(invalidHash.empty());
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, get_hash_pair) {
    auto hashPair = Base58::getHashPair(tAddressString);

    ASSERT_TRUE(array_cmp(tAddressBytes.data(),
                          hashPair.pubkeyHash.data(),
                          HASH_20_LEN));

    ASSERT_EQ(tAddressVersion, hashPair.version);
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, parse_address_hash) {
    // 1e0995750207ecaf0ccf251c1265b92ad84f553662
    const AddressHash addressHash = {  30,  9, 149, 117,  2,   7, 236,
                                      175, 12, 207,  37,  28, 18, 101,
                                      185, 42, 216,  79,  85, 54,  98 };

    // D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib
    auto address = Base58::parseAddressHash(addressHash);
    ASSERT_STREQ(tAddressString, address.c_str());
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, parse_hash) {
    auto address = Base58::parsePubkeyHash(tAddressBytes.data(), tAddressVersion);
    ASSERT_STREQ(tAddressString, address.c_str());
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, get_wif) {
    auto wif = Base58::getWif(tPrivateKeyBytes.data(), tWifVersion);
    ASSERT_STREQ(tWifString, wif.c_str());
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, parse_wif) {
    uint8_t outVersion;
    auto privateKey = Base58::parseWif(tWifString, &outVersion);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_EQ(tWifVersion, outVersion);
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, parse_wif_invalid) {
    uint8_t outVersion;
    auto privateKey = Base58::parseWif(invalid::tWifString, &outVersion);

    for (auto &e : privateKey) {
        ASSERT_EQ(0U, e);
    }

    ASSERT_NE(tWifVersion, outVersion);
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, validate) {
    ASSERT_TRUE(Base58::validate(tWifString, WIF_STRING_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, validate_zero_size) {
    ASSERT_FALSE(Base58::validate(tWifString, 0));
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, validate_invalid_size) {
    ASSERT_FALSE(Base58::validate(tWifString, WIF_STRING_LEN - 1));
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_base58, validate_invalid_char) {
    ASSERT_FALSE(Base58::validate(invalid::tWifString, WIF_STRING_LEN));
}

////////////////////////////////////////////////////////////////////////////////
