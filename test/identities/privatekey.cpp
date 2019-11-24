/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/privatekey.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace fixtures::identity;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, construct_bytes) {
    PrivateKey privateKey(tPrivateKeyBytes);    
    ASSERT_STREQ(tPrivateKeyHex, privateKey.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, to_bytes) {
    auto privateKey = PrivateKey::fromHex(tPrivateKeyHex);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          privateKey.toBytes().data(),
                          PRIVATEKEY_BYTE_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, to_string) {
    PrivateKey privateKey(tPrivateKeyBytes);
    ASSERT_STREQ(tPrivateKeyHex, privateKey.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, from_passphrase) {
    PrivateKey privateKey = PrivateKey::fromPassphrase(tPassphrase);
    ASSERT_STREQ(tPrivateKeyHex, privateKey.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, from_hex) {
    auto privateKey = PrivateKey::fromHex(tPrivateKeyHex);
    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          privateKey.toBytes().data(),
                          PRIVATEKEY_BYTE_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, from_hex_invalid_chars) {
    auto privateKey = PrivateKey::fromHex(invalid::tPrivateKeyHex);

    for (auto &e : privateKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_privatekey, from_hex_invalid_length) {
    auto privateKey = PrivateKey::fromHex(&tPrivateKeyHex[1]);

    for (auto &e : privateKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}
