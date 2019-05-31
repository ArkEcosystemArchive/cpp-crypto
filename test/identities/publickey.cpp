
#include "gtest/gtest.h"

#include "identities/publickey.h"
using namespace Ark::Crypto::Identities;

namespace { // NOLINT
  // ARK Core test fixtures:
  // https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
  const auto Passphrase = "this is a top secret passphrase";
  const uint8_t TestPublicKeyBytes[33] = {
      3,
      65,  81, 163, 236,  70, 181, 103,  10,
      104,  43,  10,  99,  57,  79, 134, 53,
      135, 209, 188, 151,  72,  59,  27, 108,
      112, 235,  88, 231, 240, 174, 209, 146
  };
  const auto PublicKeyString = "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
}  // namespace

/**/

TEST(identities, publickey_from_bytes) {
  PublicKey publicKey(TestPublicKeyBytes);
  ASSERT_STREQ(PublicKeyString, publicKey.toString().c_str());
}

/**/

TEST(identities, publickey_from_hex) {
  PublicKey publicKey = PublicKey::fromHex(PublicKeyString);
  ASSERT_STREQ(PublicKeyString, publicKey.toString().c_str());
}

/**/

TEST(identities, publickey_from_passphrase) {
  PublicKey publicKey = PublicKey::fromPassphrase(Passphrase);
  ASSERT_STREQ(PublicKeyString, publicKey.toString().c_str());
}

/**/

TEST(identities, publickey_from_string) {
  PublicKey publicKey(PublicKeyString);
  ASSERT_STREQ(PublicKeyString, publicKey.toString().c_str());
}

/**/

TEST(identities, publickey_get_bytes) {
  PublicKey publicKey(PublicKeyString);
  const auto publicKeyBytes = publicKey.toBytes();
  for (unsigned int i = 0; i < COMPRESSED_PUBLICKEY_SIZE; i++) {
    ASSERT_EQ(publicKeyBytes[i], TestPublicKeyBytes[i]);
  };
}

/**/

TEST(identities, publickey_validate) {
  PublicKey publicKey(PublicKeyString);
  ASSERT_TRUE(PublicKey::validate(publicKey));
  ASSERT_TRUE(publicKey.isValid());
}

/**/

TEST(identities, publickey_validate_bytes) {
  ASSERT_TRUE(PublicKey::validate(TestPublicKeyBytes));
}

/**/

TEST(identities, publickey_validate_string) {
  ASSERT_TRUE(PublicKey::validate(PublicKeyString));
}
