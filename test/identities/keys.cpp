/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "interfaces/identities.hpp"

#include "identities/keys.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_keys, from_passphrase) {
    auto keys = Keys::fromPassphrase(fixtures::Passphrase);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_keys, from_privatekey) {
    auto keys = Keys::fromPrivateKey(fixtures::PrivateKeyBytes.data());

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_keys, from_wif) {
    auto keys = Keys::fromWif(fixtures::WifString);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_keys, privatekey_from_passphrase) {
    auto privateKey = Keys::PrivateKey::fromPassphrase(fixtures::Passphrase);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_keys, privatekey_from_wif) {
    uint8_t outVersion;
    auto privateKey = Keys::PrivateKey::fromWif(fixtures::WifString, &outVersion);

    ASSERT_TRUE(array_cmp(fixtures::PrivateKeyBytes.data(),
                          privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_EQ(fixtures::WifVersion, outVersion);
}
