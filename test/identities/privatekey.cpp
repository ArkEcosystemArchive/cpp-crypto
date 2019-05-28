
#include "gtest/gtest.h"

#include "identities/privatekey.h"
using namespace Ark::Crypto::Identities;

namespace { // NOLINT
  // ARK Core test fixtures:
  // https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
  const auto Passphrase = "this is a top secret passphrase";
  const uint8_t TestPrivateKeyBytes[32] = {
    216, 131, 156,  36,  50, 191, 208, 166,
    126, 241,  10, 128,  75, 169, 145, 234,
    187, 161, 159,  21,  74,  61, 112, 121,
    23, 104,  29,  69, 130,  42,  87,  18
  };
  const uint8_t WIFByte = 0xaa;
  const auto PrivateKeyString = "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712";
}  // namespace

TEST(identities, privatekey_construct_bytes) {
  PrivateKey privateKey(TestPrivateKeyBytes);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_construct_string) {
  PrivateKey privateKey(PrivateKeyString);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_from_hex) {
  PrivateKey privateKey = PrivateKey::fromHex(PrivateKeyString);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_from_passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(Passphrase);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_from_string) {
  PrivateKey privateKey(PrivateKeyString);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_from_wif_string) {
  const char* wifStr = "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA";
  PrivateKey privateKey = PrivateKey::fromWIFString(wifStr, WIFByte);
  ASSERT_STREQ(PrivateKeyString, privateKey.toString().c_str());
}

TEST(identities, privatekey_get_bytes) {
  PrivateKey privateKey(PrivateKeyString);
  const auto privateKeyBytes = privateKey.toBytes();
  for (unsigned int i = 0; i < PRIVATEKEY_SIZE; i++) {
    ASSERT_EQ(privateKeyBytes[i], TestPrivateKeyBytes[i]);
  };
}

TEST(identities, privatekey_validate) {
  PrivateKey privateKey(PrivateKeyString);
  ASSERT_TRUE(PrivateKey::validate(privateKey));
}

TEST(identities, privatekey_validate_bytes) {
  ASSERT_TRUE(PrivateKey::validate(TestPrivateKeyBytes));
}

TEST(identities, privatekey_validate_string) {
  ASSERT_TRUE(PrivateKey::validate(PrivateKeyString));
}
