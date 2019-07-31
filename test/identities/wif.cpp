
#include "gtest/gtest.h"

#include <arkCrypto.h>

#include "fixtures/identity.hpp"
using namespace fixtures::identity;

TEST(identities, wif_construct_bytes) {
  Wif wif(tPrivateKeyBytes, tWifVersion);
  const auto wifBytes = wif.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(wifBytes.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(wif.version(), tWifVersion);
}


TEST(identities, wif_construct_string) {
  Wif wif(tWifString);
  const auto wifBytes = wif.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(wifBytes.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(wif.version(), tWifVersion);
}

/**/

TEST(identities, wif_construct_string_invlaid) {
  Wif wif(invalid::tWifString);
  const auto wifBytes = wif.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(wifBytes.at(i), 0);
  };
  ASSERT_EQ(wif.version(), 0);
}

/**/

TEST(identities, wif_get_version) {
  Wif wif(tWifString);
  ASSERT_EQ(wif.version(), tWifVersion);
}

/**/

TEST(identities, wif_to_bytes) {
  Wif wif(tWifString);
  const auto wifBytes = wif.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(wifBytes.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(wif.version(), tWifVersion);
}

/**/

TEST(identities, wif_to_string) {
  Wif wif(tPrivateKeyBytes, tWifVersion);
  const auto wifString = wif.toString();
  ASSERT_STREQ(wifString.c_str(), tWifString);
  ASSERT_EQ(wif.version(), tWifVersion);
}

/**/

TEST(identities, wif_from_passphrase) {
  Wif wif = Wif::fromPassphrase(tPassphrase, tWifVersion);
  const auto wifBytes = wif.toBytes();
  for (auto i = 0; i < HASH_20_BYTE_LEN; i++) {
    ASSERT_EQ(wifBytes.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(wif.version(), tWifVersion);
}
