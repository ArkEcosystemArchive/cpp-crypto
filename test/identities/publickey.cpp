#include "gtest/gtest.h"

#include "identities/publickey.hpp"
using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;

#include "fixtures/identity.hpp"
using namespace fixtures::identity;

TEST(identities, publickey_construct_bytes) {
  PublicKey publicKey(tPublicKeyBytes);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };}

/**/

TEST(identities, publickey_to_bytes) {
  auto publicKey = PublicKey::fromHex(tPublicKeyHex);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, publickey_to_string) {
  PublicKey publicKey(tPublicKeyBytes);
  const auto publicKeyString = publicKey.toString();
  ASSERT_STREQ(publicKeyString.c_str(), tPublicKeyHex);
}

/**/

TEST(identities, publickey_from_passphrase) {
  auto publicKey = PublicKey::fromPassphrase(tPassphrase);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, publickey_from_hex) {
  auto publicKey = PublicKey::fromHex(tPublicKeyHex);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, publickey_from_hex_invalid_chars) {
  auto publicKey = PublicKey::fromHex(invalid::tPublicKeyHex);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_NE(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, publickey_from_hex_invalid_length) {
  auto publicKey = PublicKey::fromHex(&tPublicKeyHex[1]);
  const auto publicKeyBytes = publicKey.toBytes();
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_NE(publicKeyBytes.at(i), tPublicKeyBytes.at(i));
  };
}
