/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/address.hpp"
#include "identities/keys.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace fixtures::identity;

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_bytes) {
    Address address(tAddressBytes, tAddressVersion);
    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_string) {
    Address address(tAddressString);
    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address,construct_string_invalid_chars) {
    Address address(invalid::tAddressString);
    ASSERT_FALSE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_string_invalid_length) {
    Address address(&tAddressString[1]);
    ASSERT_FALSE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, get_version) {
    Address address(tAddressString);
    ASSERT_EQ(tAddressVersion, address.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, to_bytes) {
    Address address(tAddressString);

    ASSERT_TRUE(array_cmp(tAddressBytes.data(),
                          address.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(tAddressVersion, address.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, to_string) {
    Address address(tAddressBytes, tAddressVersion);
    ASSERT_STREQ(tAddressString, address.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_passphrase) {
    auto address = Address::fromPassphrase(tPassphrase, tAddressVersion);
    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_publickey) {
    auto publicKey = Keys::fromPassphrase(tPassphrase).publicKey.data();
    Address address = Address::fromPublicKey(publicKey, tAddressVersion);

    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_privatekey) {
    auto privateKey = Keys::fromPassphrase(tPassphrase).privateKey.data();
    auto address = Address::fromPrivateKey(privateKey, tAddressVersion);

    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, validate) {
    Address address(tAddressString);
    ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, validate_invalid) {
    Address address(invalid::tAddressString);
    ASSERT_FALSE(Address::validate(address, tAddressVersion));
}
