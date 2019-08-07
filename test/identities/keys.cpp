
#include "gtest/gtest.h"

#include <arkCrypto.h>

#include "fixtures/identity.hpp"
using namespace fixtures::identity;

TEST(identities, keys_from_passphrase) {
  auto keys = Keys::fromPassphrase(tPassphrase);
  for (auto i = 0U; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(keys.privateKey.at(i), tPrivateKeyBytes.at(i));
  };
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(keys.publicKey.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, keys_from_privatekey) {
  auto keys = Keys::fromPrivateKey(tPrivateKeyBytes.data());
  for (auto i = 0U; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(keys.privateKey.at(i), tPrivateKeyBytes.at(i));
  };
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(keys.publicKey.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, keys_from_wif) {
  auto keys = Keys::fromWif(tWifString);
  for (auto i = 0U; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(keys.privateKey.at(i), tPrivateKeyBytes.at(i));
  };
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(keys.publicKey.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(identities, keys_privatekey_from_passphrase) {
  auto privateKey = Keys::PrivateKey::fromPassphrase(tPassphrase);
  for (auto i = 0U; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKey.at(i), tPrivateKeyBytes.at(i));
  };
}

/**/

TEST(identities, keys_privatekey_from_wif) {
  uint8_t outVersion;
  auto privateKey = Keys::PrivateKey::fromWif(tWifString, &outVersion);
  for (auto i = 0U; i < PRIVATEKEY_BYTE_LEN; i++) {
    ASSERT_EQ(privateKey.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(outVersion, tWifVersion);
}

/**/

TEST(identities, keys_publickey_from_privatekey) {
  auto publicKey = Keys::PublicKey::fromPrivateKey(tPrivateKeyBytes.data());
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKey.at(i), tPublicKeyBytes.at(i));
  };
}
