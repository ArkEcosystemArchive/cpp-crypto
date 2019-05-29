
#include "arkCrypto.h"
#include "gtest/gtest.h"

TEST(configuration, fee_get) {
  Ark::Crypto::Configuration::Fee fee;
  ASSERT_EQ(10000000ULL, fee.get(0));
  ASSERT_EQ(500000000ULL, fee.get(1));
  ASSERT_EQ(2500000000ULL, fee.get(2));
  ASSERT_EQ(100000000ULL, fee.get(3));
  ASSERT_EQ(500000000ULL, fee.get(4));
  ASSERT_EQ(0ULL, fee.get(5));
  ASSERT_EQ(0ULL, fee.get(6));
  ASSERT_EQ(0ULL, fee.get(7));
  ASSERT_EQ(0ULL, fee.get(8));
}

/**/

TEST(configuration, fee_set) {
  Ark::Crypto::Configuration::Fee fee;
  fee.set(0ULL, 20000000ULL);
  fee.set(1ULL, 1000000000ULL);
  fee.set(2ULL, 4000000000ULL);
  fee.set(3ULL, 200000000ULL);
  fee.set(4ULL, 1000000000ULL);
  fee.set(5ULL, 1ULL);
  fee.set(6ULL, 1ULL);
  fee.set(7ULL, 1ULL);
  fee.set(8ULL, 1ULL);

  ASSERT_EQ(20000000ULL, fee.get(0));
  ASSERT_EQ(1000000000ULL, fee.get(1));
  ASSERT_EQ(4000000000ULL, fee.get(2));
  ASSERT_EQ(200000000ULL, fee.get(3));
  ASSERT_EQ(1000000000ULL, fee.get(4));
  ASSERT_EQ(1ULL, fee.get(5));
  ASSERT_EQ(1ULL, fee.get(6));
  ASSERT_EQ(1ULL, fee.get(7));
  ASSERT_EQ(1ULL, fee.get(8));
}
