
#include "gtest/gtest.h"
#include <arkCrypto.h>

namespace {  // NOLINT
  static const std::string Nethash  = "d9acd04bde4234a81addb8482333b4ac906bed7be5a9970ce8ada428bd083192";
  static const uint8_t Slip44       = 1;
  static const uint8_t Wif          = 0xba;
  static const uint8_t Version      = 0x17;
  static const std::string Epoch    = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, testnet) {
  ASSERT_STREQ(Nethash.c_str(), Networks::Testnet().nethash().c_str());
  ASSERT_EQ(Slip44,             Networks::Testnet().slip44());
  ASSERT_EQ(Wif,                Networks::Testnet().wif());
  ASSERT_EQ(Version,            Networks::Testnet().version());
  ASSERT_STREQ(Epoch.c_str(),   Networks::Testnet().epoch().c_str());
}
