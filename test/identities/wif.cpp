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

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace fixtures::identity;

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, construct_bytes) {
    Wif wif(tPrivateKeyBytes, tWifVersion);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, construct_string) {
    Wif wif(tWifString);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, construct_string_invlaid) {
    Wif wif(invalid::tWifString);

    for (auto &e : wif.toBytes()) {
        ASSERT_EQ(0U, e);
    }

    ASSERT_EQ(0U, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, get_version) {
    Wif wif(tWifString);
    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, to_bytes) {
    Wif wif(tWifString);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, to_string) {
    Wif wif(tPrivateKeyBytes, tWifVersion);

    ASSERT_STREQ(tWifString, wif.toString().c_str());
    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_wif, from_passphrase) {
    Wif wif = Wif::fromPassphrase(tPassphrase, tWifVersion);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          wif.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(tWifVersion, wif.version());
}

////////////////////////////////////////////////////////////////////////////////
