/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/publickey.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, construct_bytes) {
    PublicKey publicKey(fixtures::PublicKeyBytes);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          publicKey.toBytes().data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, to_bytes) {
    auto publicKey = PublicKey::fromHex(fixtures::PublicKeyHex);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          publicKey.toBytes().data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, to_string) {
    PublicKey publicKey(fixtures::PublicKeyBytes);
    ASSERT_STREQ(fixtures::PublicKeyHex, publicKey.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_passphrase) {
    auto publicKey = PublicKey::fromPassphrase(fixtures::Passphrase);
    const auto publicKeyBytes = publicKey.toBytes();

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          publicKeyBytes.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex) {
    auto publicKey = PublicKey::fromHex(fixtures::PublicKeyHex);
    const auto publicKeyBytes = publicKey.toBytes();

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          publicKeyBytes.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex_invalid_chars) {
    const auto publicKey = PublicKey::fromHex(fixtures::invalid::PublicKeyHex);

    for (auto &e : publicKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex_invalid_length) {
    const auto publicKey = PublicKey::fromHex(&fixtures::PublicKeyHex[1]);

    for (auto &e : publicKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}
