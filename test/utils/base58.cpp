
#include "gtest/gtest.h"

#include "utils/base58.hpp"

#include "fixtures/identity.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;

TEST(utils, base58_get_hash_pair) {
  auto hashPair = Base58::getHashPair(tAddressString);
  for (auto i = 0U; i < HASH_20_BYTE_LEN; ++i) {
    ASSERT_EQ(hashPair.pubkeyHash.at(i), tAddressBytes.at(i));
  };
  ASSERT_EQ(hashPair.version, tAddressVersion);
}

/**/

TEST(utils, base58_parse_hash) {
  auto address = Base58::parseHash(tAddressBytes.data(), tAddressVersion);
  ASSERT_STREQ(address.c_str(), tAddressString);
}

/**/

TEST(utils, base58_get_wif) {
  auto wif = Base58::getWif(tPrivateKeyBytes.data(), tWifVersion);
  ASSERT_STREQ(wif.c_str(), tWifString);
}

/**/

TEST(utils, base58_parse_wif) {
  uint8_t outVersion;
  auto privateKey = Base58::parseWif(tWifString, &outVersion);
  for (auto i = 0U; i < HASH_20_BYTE_LEN; ++i) {
    ASSERT_EQ(privateKey[i], tPrivateKeyBytes.at(i));
  };
  ASSERT_EQ(outVersion, tWifVersion);
}

/**/

TEST(utils, base58_parse_wif_invalid) {
  uint8_t outVersion;
  auto privateKey = Base58::parseWif(invalid::tWifString, &outVersion);
  for (auto i = 0U; i < HASH_20_BYTE_LEN; ++i) {
    ASSERT_NE(privateKey.at(i), tPrivateKeyBytes.at(i));
  };
  ASSERT_NE(outVersion, tWifVersion);
}

/**/

TEST(utils, base58_validate) {
  ASSERT_TRUE(Base58::validate(tWifString, WIF_STRING_LEN));
}

/**/

TEST(utils, base58_validate_zero_size) {
  ASSERT_FALSE(Base58::validate(tWifString, 0));
}

/**/

TEST(utils, base58_validate_invalid_size) {
  ASSERT_FALSE(Base58::validate(tWifString, WIF_STRING_LEN - 1));
}

/**/

TEST(utils, base58_validate_invalid_char) {
  ASSERT_FALSE(Base58::validate(invalid::tWifString, WIF_STRING_LEN));
}

