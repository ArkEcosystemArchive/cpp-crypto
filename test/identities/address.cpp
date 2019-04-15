
#include "gtest/gtest.h"

#include "identities/address.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"
using namespace Ark::Crypto::Identities;

namespace { // NOLINT

// ARK Core test fixtures:
// https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
const auto passphrase = "this is a top secret passphrase";
const uint8_t networkVersion = 0x1E;
}  // namespace

TEST(identities, address_from_passphrase) {
  Address address = Address::fromPassphrase(passphrase, networkVersion);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", address.toString().c_str());
}

TEST(identities, address_from_privatekey) {
  PrivateKey privateKey("d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712");
  Address address = Address::fromPrivateKey(privateKey, networkVersion);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", address.toString().c_str());
}

TEST(identities, address_from_publickey) {
  PublicKey publicKey("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  Address address = Address::fromPublicKey(publicKey, networkVersion);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", address.toString().c_str());
}

TEST(identities, address_from_string) {
  Address address("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib");
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", address.toString().c_str());
}

TEST(identities, address_validate) {
  Address address("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib");
  ASSERT_TRUE(Address::validate(address, networkVersion));
}
