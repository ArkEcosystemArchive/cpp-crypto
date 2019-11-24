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
using namespace fixtures::identity;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, construct_bytes) {
    PublicKey publicKey(tPublicKeyBytes);

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKey.toBytes().data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, to_bytes) {
    auto publicKey = PublicKey::fromHex(tPublicKeyHex);

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKey.toBytes().data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, to_string) {
    PublicKey publicKey(tPublicKeyBytes);
    ASSERT_STREQ(tPublicKeyHex, publicKey.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_passphrase) {
    auto publicKey = PublicKey::fromPassphrase(tPassphrase);
    const auto publicKeyBytes = publicKey.toBytes();

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKeyBytes.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex) {
    auto publicKey = PublicKey::fromHex(tPublicKeyHex);
    const auto publicKeyBytes = publicKey.toBytes();

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKeyBytes.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex_invalid_chars) {
    const auto publicKey = PublicKey::fromHex(invalid::tPublicKeyHex);

    for (auto &e : publicKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_publickey, from_hex_invalid_length) {
    const auto publicKey = PublicKey::fromHex(&tPublicKeyHex[1]);

    for (auto &e : publicKey.toBytes()) {
        ASSERT_EQ(0U, e);
    }
}
