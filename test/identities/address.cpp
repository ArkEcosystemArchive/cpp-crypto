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

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_bytes) {
    Address address(fixtures::AddressBytes, fixtures::AddressVersion);
    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_string) {
    Address address(fixtures::AddressString);
    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address,construct_string_invalid_chars) {
    Address address(fixtures::invalid::AddressString);
    ASSERT_FALSE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, construct_string_invalid_length) {
    Address address(&fixtures::AddressString[1]);
    ASSERT_FALSE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, get_version) {
    Address address(fixtures::AddressString);
    ASSERT_EQ(fixtures::AddressVersion, address.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, to_bytes) {
    Address address(fixtures::AddressString);

    ASSERT_TRUE(array_cmp(fixtures::AddressBytes.data(),
                          address.toBytes().data(),
                          HASH_20_LEN));

    ASSERT_EQ(fixtures::AddressVersion, address.version());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, to_string) {
    Address address(fixtures::AddressBytes, fixtures::AddressVersion);
    ASSERT_STREQ(fixtures::AddressString, address.toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_passphrase) {
    auto address = Address::fromPassphrase(fixtures::Passphrase,
                                           fixtures::AddressVersion);
    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_publickey) {
    auto publicKey = Keys::fromPassphrase(fixtures::Passphrase).publicKey.data();
    const auto address = Address::fromPublicKey(publicKey,
                                                fixtures::AddressVersion);

    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, from_privatekey) {
    auto privateKey = Keys::fromPassphrase(
                fixtures::Passphrase).privateKey.data();
    auto address = Address::fromPrivateKey(privateKey, fixtures::AddressVersion);

    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, validate) {
    Address address(fixtures::AddressString);
    ASSERT_TRUE(Address::validate(address, fixtures::AddressVersion));
}

////////////////////////////////////////////////////////////////////////////////
TEST(identities_address, validate_invalid) {
    Address address(fixtures::invalid::AddressString);
    ASSERT_FALSE(Address::validate(address, fixtures::AddressVersion));
}
