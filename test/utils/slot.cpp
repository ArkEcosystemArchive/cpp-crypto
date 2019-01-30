#include "gtest/gtest.h"
#include "gtest/gtest.h"

#include "helpers/crypto_helpers.h"
#include "utils/slot.h"

TEST(utilities, slots_epoch) {
  const auto devnet = Ark::Crypto::Networks::Devnet;
  const auto arkEpoch = 1490101200ull;
  ASSERT_EQ(arkEpoch, Ark::Crypto::Utils::Slot::epoch(devnet));
}

TEST(utilities, slots_time) {
  const auto devnet = Ark::Crypto::Networks::Devnet;

  // 28 Jan 2019(in seconds) - Ark Epoch (seconds)
  const auto testTime = (1548725761ull - 1490101200ull); 
  const auto slotTime = Ark::Crypto::Utils::Slot::time(devnet);

  // test that slot-time is more recent than 'testTime',
  ASSERT_GT(slotTime , testTime);
  // also check that the 'slotTime' is not too large (e.g. from an overflow).
  ASSERT_LT(slotTime, (testTime) + 315360000); // 315360000s = 10yrs
}
