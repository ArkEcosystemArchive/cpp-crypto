
#include "gtest/gtest.h"

#include "networks/testnet.hpp"

namespace {  // NOLINT
using namespace Ark::Crypto;
constexpr const char* kNethash    = "d9acd04bde4234a81addb8482333b4ac906bed7be5a9970ce8ada428bd083192";
constexpr const uint8_t kSlip44   = 1;
constexpr const uint8_t kWif      = 0xba;
constexpr const uint8_t kVersion  = 0x17;
constexpr const char* kEpoch      = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, testnet) {
  ASSERT_STREQ(Testnet.nethash.c_str(),  kNethash);
  ASSERT_EQ(Testnet.slip44,              kSlip44);
  ASSERT_EQ(Testnet.wif,                 kWif);
  ASSERT_EQ(Testnet.version,             kVersion);
  ASSERT_STREQ(Testnet.epoch.c_str(),    kEpoch);
}
