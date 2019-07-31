
#include "gtest/gtest.h"

#include <arkCrypto.h>

#include "fixtures/identity.hpp"
using namespace fixtures::identity;

TEST(identities, privatekey_construct_bytes) {
  PrivateKey privateKey(tPrivateKeyBytes);
  const auto privateKeyString = privateKey.toString();
  ASSERT_STREQ(privateKeyString.c_str(), tPrivateKeyHex);
}

/**/

TEST(identities, privatekey_to_bytes) {
  auto privateKey = PrivateKey::fromHex(tPrivateKeyHex);
  const auto privateKeyBytes = privateKey.toBytes();
  for (auto i = 0; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKeyBytes.at(i), tPrivateKeyBytes.at(i));
  };
}

/**/

TEST(identities, privatekey_to_string) {
  PrivateKey privateKey(tPrivateKeyBytes);
  const auto privateKeyString = privateKey.toString();
  ASSERT_STREQ(privateKeyString.c_str(), tPrivateKeyHex);
}

/**/

TEST(identities, privatekey_from_passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(tPassphrase);
  const auto privateKeyString = privateKey.toString();
  ASSERT_STREQ(privateKeyString.c_str(), tPrivateKeyHex);
}

/**/

TEST(identities, privatekey_from_hex) {
  auto privateKey = PrivateKey::fromHex(tPrivateKeyHex);
  const auto privateKeyBytes = privateKey.toBytes();
  for (auto i = 0; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKeyBytes.at(i), tPrivateKeyBytes.at(i));
  };
}

/**/

TEST(identities, privatekey_from_hex_invalid_chars) {
  auto privateKey = PrivateKey::fromHex(invalid::tPrivateKeyHex);
  const auto privateKeyBytes = privateKey.toBytes();
  for (auto i = 0; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKeyBytes.at(i), 0);
  };
}

/**/

TEST(identities, privatekey_from_hex_invalid_length) {
  auto privateKey = PrivateKey::fromHex(&tPrivateKeyHex[1]);
  const auto privateKeyBytes = privateKey.toBytes();
  for (auto i = 0; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKeyBytes.at(i), 0);
  };
}
