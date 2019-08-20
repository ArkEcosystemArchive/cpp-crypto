
#include "gtest/gtest.h"

#include <cstdint>

#include <arkCrypto.h>

namespace {
const FeePolicy CustomFeePolicy = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
}  //namespace

/**/

TEST(common, configuration_constructor_default) {
  Configuration config;
  Configuration custom(Devnet, StaticFeePolicy);
  ASSERT_TRUE(config == custom);
}

/**/

TEST(common, configuration_constructor_network) {
  Configuration config(Testnet);
  ASSERT_TRUE(config.getNetwork() == Testnet);
  ASSERT_TRUE(config.getPolicy() == StaticFeePolicy);
}

/**/

TEST(common, configuration_constructor_fee_policy) {
  Configuration config(CustomFeePolicy);
  ASSERT_TRUE(config.getNetwork() == Devnet);
  ASSERT_TRUE(config.getPolicy() == CustomFeePolicy);
}

/**/

TEST(common, configuration_constructor_network_and_fee_policy) {
  Configuration config(Testnet, CustomFeePolicy);
  ASSERT_TRUE(config.getNetwork() == Testnet);
  ASSERT_TRUE(config.getPolicy() == CustomFeePolicy);
}

/**/

TEST(common, configuration_comparison_equals) {
  Configuration config;
  Configuration custom(Devnet, StaticFeePolicy);
  ASSERT_TRUE(config == custom);
}

/**/

TEST(common, configuration_comparison_not_equal) {
  Configuration config;
  Configuration custom(Testnet);
  ASSERT_TRUE(config != custom);
}
