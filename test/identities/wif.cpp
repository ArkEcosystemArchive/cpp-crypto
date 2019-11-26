/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/wif.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, construct_bytes) {
    Wif wif(fixtures::PrivateKeyBytes, fixtures::WifVersion);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(fixtures::WifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, construct_string) {
    Wif wif(fixtures::WifString);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(fixtures::WifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, construct_string_invlaid) {
    Wif wif(fixtures::invalid::WifString);

    for (auto &e : wif.toBytes()) {
        ASSERT_EQ(0U, e);
    }

    ASSERT_EQ(0U, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, get_version) {
    Wif wif(fixtures::WifString);
    ASSERT_EQ(fixtures::WifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, to_bytes) {
    Wif wif(fixtures::WifString);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(fixtures::WifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, to_string) {
    Wif wif(fixtures::PrivateKeyBytes, fixtures::WifVersion);

    ASSERT_STREQ(fixtures::WifString, wif.toString().c_str());
    ASSERT_EQ(fixtures::WifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_wif, from_passphrase) {
    Wif wif = Wif::fromPassphrase(fixtures::Passphrase, fixtures::WifVersion);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(fixtures::WifVersion, wif.version());
}
