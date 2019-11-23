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

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace Ark::Crypto::fixtures::identity;

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, from_passphrase) {
    auto keys = Keys::fromPassphrase(tPassphrase);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, from_privatekey) {
    auto keys = Keys::fromPrivateKey(tPrivateKeyBytes.data());

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, from_wif) {
    auto keys = Keys::fromWif(tWifString);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          keys.privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          keys.publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, privatekey_from_passphrase) {
    auto privateKey = Keys::PrivateKey::fromPassphrase(tPassphrase);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, privatekey_from_wif) {
    uint8_t outVersion;
    auto privateKey = Keys::PrivateKey::fromWif(tWifString, &outVersion);

    ASSERT_TRUE(array_cmp(tPrivateKeyBytes.data(),
                          privateKey.data(),
                          PRIVATEKEY_BYTE_LEN));

    ASSERT_EQ(tWifVersion, outVersion);
}

////////////////////////////////////////////////////////////////////////////////
