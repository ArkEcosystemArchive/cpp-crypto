
#include "gtest/gtest.h"
#include <arkCrypto.h>

namespace {  // NOLINT
  static const std::string Nethash  = "6e84d08bd299ed97c212c886c98a57e36545c8f5d645ca7eeae63a8bd62d8988";
  static const uint8_t Slip44       = 111;
  static const uint8_t tWif          = 0xaa;
  static const uint8_t Version      = 0x17;
  static const std::string Epoch    = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, mainnet) {
  ASSERT_STREQ(Nethash.c_str(), Networks::Mainnet().nethash().c_str());
  ASSERT_EQ(Slip44,             Networks::Mainnet().slip44());
  ASSERT_EQ(tWif,                Networks::Mainnet().wif());
  ASSERT_EQ(Version,            Networks::Mainnet().version());
  ASSERT_STREQ(Epoch.c_str(),   Networks::Mainnet().epoch().c_str());
}
