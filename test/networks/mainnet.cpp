
#include "gtest/gtest.h"

#include "networks/mainnet.hpp"

namespace {  // NOLINT
using namespace Ark::Crypto;
constexpr const char* kNethash    = "6e84d08bd299ed97c212c886c98a57e36545c8f5d645ca7eeae63a8bd62d8988";
constexpr const uint8_t kSlip44   = 111;
constexpr const uint8_t kWif      = 0xaa;
constexpr const uint8_t kVersion  = 0x17;
constexpr const char* kEpoch      = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, mainnet) {
  ASSERT_STREQ(Mainnet.nethash.c_str(),  kNethash);
  ASSERT_EQ(Mainnet.slip44,              kSlip44);
  ASSERT_EQ(Mainnet.wif,                 kWif);
  ASSERT_EQ(Mainnet.version,             kVersion);
  ASSERT_STREQ(Mainnet.epoch.c_str(),    kEpoch);
}
