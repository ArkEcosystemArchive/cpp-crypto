
#include "gtest/gtest.h"

#include "networks/devnet.hpp"

namespace {  // NOLINT
using namespace Ark::Crypto;
constexpr const char* kNethash    = "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867";
constexpr const uint8_t kSlip44   = 1;
constexpr const uint8_t kWif      = 0xaa;
constexpr const uint8_t kVersion  = 0x1E;
constexpr const char* kEpoch      = "2017-03-21T13:00:00.000Z";
};  // namespace

TEST(networks, devnet) {
  ASSERT_STREQ(Devnet.nethash.c_str(),  kNethash);
  ASSERT_EQ(Devnet.slip44,              kSlip44);
  ASSERT_EQ(Devnet.wif,                 kWif);
  ASSERT_EQ(Devnet.version,             kVersion);
  ASSERT_STREQ(Devnet.epoch.c_str(),    kEpoch);
}
