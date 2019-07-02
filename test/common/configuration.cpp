
#include "gtest/gtest.h"

#include <cstdint>

#include <arkCrypto.h>

namespace {
static const Network kDefaultNetwork = Networks::Devnet();
static const Network kCustomNetwork = {  // random parameters
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};
/**/
static const FeePolicy kDefaultFeePolicy = defaults::Fees::StaticFeePolicy();
static const FeePolicy kCustomFeePolicy = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
static const uint64_t kTestAmount = 1000000000ULL;
/**/
static const Configuration kDefaultConfiguration = Configuration();
static const Configuration kCustomFeeConfiguration(kCustomFeePolicy);
static const Configuration kCustomNetworkConfiguration(kCustomNetwork);
static const Configuration kCustomConfiguration(kCustomNetwork,
                                                kCustomFeePolicy);
}  //namespace

/**/

//*
TEST(common, configuration_constructor_default) {
  Configuration config;
  bool isMatching = kDefaultConfiguration == config;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_constructor_network) {
  Configuration config(kCustomNetwork);
  bool isMatching = kCustomNetworkConfiguration == config;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_constructor_fee) {
  Configuration config(kCustomFeePolicy);
  bool isMatching = kCustomFeeConfiguration == config;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_constructor_with_network_and_fee) {
  Configuration config(kCustomNetwork, kCustomFeePolicy);
  bool isMatching = kCustomConfiguration == config;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_network_get) {
  Configuration config;
  auto network = config.getNetwork();
  bool isMatching = kDefaultNetwork == network;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_network_set) {
  Configuration config;
  config.setNetwork(kCustomNetwork);
  auto network = config.getNetwork();
  bool isMatching = kCustomNetwork == network;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_fee_get) {
  Configuration config;
  auto transferType = defaults::TransactionTypes::Transfer;
  auto defaultTransferFee = kDefaultFeePolicy[transferType];
  auto transferFee = config.getFee(transferType);
  ASSERT_EQ(defaultTransferFee, transferFee);
}

/**/

TEST(common, configuration_fee_set) {
  Configuration config;
  auto transferType = defaults::TransactionTypes::Transfer;
  config.setFee(transferType, kTestAmount);
  uint64_t newFee = config.getFee(transferType);
  ASSERT_EQ(kTestAmount, newFee);
}

/**/


TEST(common, configuration_fees_get_policy) {
  Configuration config;
  bool isMatching = kDefaultFeePolicy == config.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_fees_policy_set) {
  Configuration config;
  config.setPolicy(kCustomFeePolicy);
  bool isMatching = kCustomFeePolicy == config.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_comparison_equals) {
  Configuration config;
  bool isMatching = kDefaultConfiguration == config;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(common, configuration_comparison_not_equal) {
  Configuration config(kCustomNetwork);
  bool notMatching = kCustomConfiguration != config;
  ASSERT_TRUE(notMatching);
}
