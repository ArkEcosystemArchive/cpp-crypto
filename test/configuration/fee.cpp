
#include "arkCrypto.h"
#include "gtest/gtest.h"

TEST(configuration, fee_get) {
  Ark::Crypto::Configuration::Fee fee;
  ASSERT_TRUE(10000000 == fee.get(0));
  ASSERT_TRUE(500000000 == fee.get(1));
  ASSERT_TRUE(2500000000 == fee.get(2));
  ASSERT_TRUE(100000000 == fee.get(3));
  ASSERT_TRUE(500000000 == fee.get(4));
  ASSERT_TRUE(0 == fee.get(5));
  ASSERT_TRUE(0 == fee.get(6));
  ASSERT_TRUE(0 == fee.get(7));
  ASSERT_TRUE(0 == fee.get(8));
}

TEST(configuration, fee_set) {
  Ark::Crypto::Configuration::Fee fee;
  fee.set(0, 20000000ul);
  fee.set(1, 1000000000ul);
  fee.set(2, 4000000000ul);
  fee.set(3, 200000000ul);
  fee.set(4, 1000000000ul);
  fee.set(5, 1ul);
  fee.set(6, 1ul);
  fee.set(7, 1ul);
  fee.set(8, 1ul);

  ASSERT_TRUE(20000000 == fee.get(0));
  ASSERT_TRUE(1000000000 == fee.get(1));
  ASSERT_TRUE(4000000000 == fee.get(2));
  ASSERT_TRUE(200000000 == fee.get(3));
  ASSERT_TRUE(1000000000 == fee.get(4));
  ASSERT_TRUE(1 == fee.get(5));
  ASSERT_TRUE(1 == fee.get(6));
  ASSERT_TRUE(1 == fee.get(7));
  ASSERT_TRUE(1 == fee.get(8));
}
