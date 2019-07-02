
#include "gtest/gtest.h"
#include <arkCrypto.h>

namespace {  // NOLINT
  static const std::string Nethash  = "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867";
  static const uint8_t Slip44       = 1;
  static const uint8_t Wif          = 0xaa;
  static const uint8_t Version      = 0x1E;
  static const std::string Epoch    = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, devnet) {
  ASSERT_STREQ(Nethash.c_str(), Networks::Devnet().nethash().c_str());
  ASSERT_EQ(Slip44,             Networks::Devnet().slip44());
  ASSERT_EQ(Wif,                Networks::Devnet().wif());
  ASSERT_EQ(Version,            Networks::Devnet().version());
  ASSERT_STREQ(Epoch.c_str(),   Networks::Devnet().epoch().c_str());
}
