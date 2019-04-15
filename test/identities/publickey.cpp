
#include "gtest/gtest.h"

#include "identities/publickey.h"
using namespace Ark::Crypto::Identities;

namespace { // NOLINT

// ARK Core test fixtures:
// https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
const auto passphrase = "this is a top secret passphrase";
const uint8_t testPublicKeyBytes[33] = {
    3,
    65,  81, 163, 236,  70, 181, 103,  10,
    104,  43,  10,  99,  57,  79, 134, 53,
    135, 209, 188, 151,  72,  59,  27, 108,
    112, 235,  88, 231, 240, 174, 209, 146
};

}  // namespace

TEST(identities, publickey_from_bytes) {
  PublicKey publicKey(testPublicKeyBytes);
  ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", publicKey.toString().c_str());
}

TEST(identities, publickey_from_hex) {
  PublicKey publicKey = PublicKey::fromHex("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", publicKey.toString().c_str());
}

TEST(identities, publickey_from_passphrase) {
  PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
  ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", publicKey.toString().c_str());
}

TEST(identities, publickey_from_string) {
  PublicKey publicKey("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", publicKey.toString().c_str());
}

TEST(identities, publickey_get_bytes) {
  PublicKey publicKey("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  const auto publicKeyBytes = publicKey.toBytes();
  for (unsigned int i = 0; i < COMPRESSED_PUBLICKEY_SIZE; i++) {
    ASSERT_EQ(publicKeyBytes[i], testPublicKeyBytes[i]);
  };
}

TEST(identities, publickey_validate) {
  PublicKey publicKey("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  ASSERT_TRUE(PublicKey::validate(publicKey));
}

TEST(identities, publickey_validate_bytes) {
  ASSERT_TRUE(PublicKey::validate(testPublicKeyBytes));
}

TEST(identities, publickey_validate_string) {
  ASSERT_TRUE(PublicKey::validate("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192"));
}
