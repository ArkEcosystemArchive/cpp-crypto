
#include "gtest/gtest.h"
#include "arkCrypto.h"

TEST(utilities, slots_time) {
  const auto devnet = Ark::Crypto::Networks::Devnet;
  
#ifdef USE_IOT
  // IoT does not support 64 bit in unit tests yet
  //ASSERT_EQ(10ull, ARK::Utilities::slots::time(1490101210000, devnet));
  ASSERT_TRUE(Ark::Crypto::Utils::Slot::time(1490101210000, devnet) == 10ull);
#else
  ASSERT_EQ(10ull, Ark::Crypto::Utils::Slot::time(1490101210000, devnet));
#endif
}

TEST(utilities, slots_begin_epoch_time) {
  const auto devnet = Ark::Crypto::Networks::Devnet;

#ifdef USE_IOT
  // IoT does not support 64 bit in unit tests yet
  //ASSERT_EQ(1490101200ull, ARK::Utilities::slots::begin_epoch_time(devnet));
  ASSERT_TRUE(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(Ark::Crypto::Utils::Slot::begin_epoch_time(devnet))).count() == 1490101200ull);
#else
  ASSERT_EQ(1490101200ull, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(Ark::Crypto::Utils::Slot::begin_epoch_time(devnet))).count());
#endif
}

TEST(utilities, slots_get_real_time) {
  const auto devnet = Ark::Crypto::Networks::Devnet;

#ifdef USE_IOT
  // IoT does not support 64 bit in unit tests yet
  //ASSERT_EQ(1490101210000ull, ARK::Utilities::slots::get_real_time(10));
  ASSERT_TRUE(Ark::Crypto::Utils::Slot::real_time(10, devnet) == 1490101210000ull);
#else
  ASSERT_EQ(1490101210000ull, Ark::Crypto::Utils::Slot::real_time(10, devnet));
#endif
}

