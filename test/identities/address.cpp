
#include "gtest/gtest.h"

#include "identities/address.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"

#include <cstring>

using namespace Ark::Crypto::Identities;

namespace { // NOLINT
  // ARK Core test fixtures:
  // https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
  const auto Passphrase = "this is a top secret passphrase";
  const uint8_t NetworkVersion = 0x1E;
  const auto AddressString = "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib";
  const uint8_t TestAddressBytes[34] = {
    68, 54, 49, 109, 102, 83, 103, 103,
    122, 98, 118, 81, 103, 84, 85, 101,
    54, 74, 104, 89, 75, 72, 50, 100,
    111, 72, 97, 113, 74, 51, 68, 121, 105, 98
  };
}  // namespace

/**/

TEST(identities, address_from_bytes) {
  Address address(TestAddressBytes);
  ASSERT_STREQ(address.toString().c_str(), AddressString);
}

/**/

TEST(identities, address_to_bytes) {
  Address address(AddressString);
  const auto addressBytes = address.toBytes();
  for (auto i = 0; i < 34; ++i) {
    ASSERT_EQ(addressBytes[i], TestAddressBytes[i]);
  };
}

/**/

TEST(identities, address_from_passphrase) {
  Address address = Address::fromPassphrase(Passphrase, NetworkVersion);
  ASSERT_STREQ(AddressString, address.toString().c_str());
}

/**/

TEST(identities, address_from_privatekey) {
  const auto privateKeyString = "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712";
  PrivateKey privateKey(privateKeyString);
  Address address = Address::fromPrivateKey(privateKey, NetworkVersion);
  ASSERT_STREQ(AddressString, address.toString().c_str());
}

/**/

TEST(identities, address_from_publickey) {
  const auto publicKeyString = "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
  PublicKey publicKey(publicKeyString);
  Address address = Address::fromPublicKey(publicKey, NetworkVersion);
  ASSERT_STREQ(AddressString, address.toString().c_str());
}

/**/

TEST(identities, address_from_string) {
  Address address(AddressString);
  ASSERT_STREQ(AddressString, address.toString().c_str());
}

/**/

TEST(identities, address_validate_address) {
  Address address(AddressString);
  ASSERT_TRUE(Address::validate(address, NetworkVersion));
}

/**/

TEST(identities, address_validate) {
  Address address(AddressString);
  ASSERT_TRUE(Address::validate(address, NetworkVersion));
}

/**/

TEST(identities, address_validate_string) {
  ASSERT_TRUE(Address::validate(AddressString, NetworkVersion));
}

/**/

TEST(identities, address_validate_bytes) {
  ASSERT_TRUE(Address::validate(TestAddressBytes, NetworkVersion));
}

/**/

TEST(identities, address_invalid) {
  const auto invalidAddressStr = "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyi";
  Address address(invalidAddressStr);
  ASSERT_FALSE(Address::validate(address, NetworkVersion));
}
