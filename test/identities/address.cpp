
#include "gtest/gtest.h"

#include <arkCrypto.h>

#include "fixtures/identity.hpp"
using namespace fixtures::identity;

TEST(identities, address_construct_bytes) {
  Address address(tAddressBytes, tAddressVersion);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_construct_string) {
  Address address(tAddressString);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_construct_string_invalid_chars) {
  Address address(invalid::tAddressString);
  ASSERT_FALSE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_construct_string_invalid_length) {
  Address address(&tAddressString[1]);
  ASSERT_FALSE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_get_version) {
  Address address(tAddressString);
  auto version = address.version();
  ASSERT_EQ(version, tAddressVersion);
}

/**/

TEST(identities, address_to_bytes) {
  Address address(tAddressString);
  auto addressBytes = address.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(addressBytes.at(i), tAddressBytes.at(i));
  };
  auto version = address.version();
  ASSERT_EQ(version, tAddressVersion);
}

/**/

TEST(identities, address_to_string) {
  Address address(tAddressBytes, tAddressVersion);
  auto addressString = address.toString();
  ASSERT_STREQ(addressString.c_str(), tAddressString);
}

/**/

TEST(identities, address_from_passphrase) {
  auto address = Address::fromPassphrase(tPassphrase, tAddressVersion);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_from_publickey) {
  auto publicKey = Keys::fromPassphrase(tPassphrase).publicKey.data();
  Address address = Address::fromPublicKey(publicKey, tAddressVersion);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_from_privatekey) {
  auto privateKey = Keys::fromPassphrase(tPassphrase).privateKey.data();
  auto address = Address::fromPrivateKey(privateKey, tAddressVersion);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_validate) {
  Address address(tAddressString);
  ASSERT_TRUE(Address::validate(address, tAddressVersion));
}

/**/

TEST(identities, address_validate_invalid) {
  Address address(invalid::tAddressString);
  ASSERT_FALSE(Address::validate(address, tAddressVersion));
}
