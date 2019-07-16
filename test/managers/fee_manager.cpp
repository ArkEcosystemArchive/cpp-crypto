
#include "gtest/gtest.h"

#include <arkCrypto.h>

using namespace managers;

namespace {
static const FeePolicy kDefaultFeePolicy = defaults::Fees::StaticFeePolicy();
static const FeePolicy kCustomFeePolicy = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
static const FeeManager kDefaultFeeManager = FeeManager();
static const FeeManager kCustomFeeManager = FeeManager(kCustomFeePolicy);
static const uint8_t kInPolicyBounds = 5;
static const uint8_t kOutOfPolicyBounds = 11;
static const uint64_t kAmountZero = 0ULL;
static const uint64_t kCustomFee = 1000000000ULL;
}  //namespace

/**/

TEST(managers, fee_manager_constructor_default) {
  FeeManager feeManager;
  bool isMatching = kDefaultFeeManager == feeManager.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, fee_manager_constructor_fee_policy) {
  FeeManager feeManager(kCustomFeePolicy);
  bool isMatching = kCustomFeeManager == feeManager.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, fee_manager_fee_get_in_bounds) {
  FeeManager feeManager;
  ASSERT_EQ(kDefaultFeePolicy[kInPolicyBounds],
            feeManager.getFee(kInPolicyBounds));
}

/**/

TEST(managers, fee_manager_fee_get_out_of_bounds) {
  FeeManager feeManager;
  ASSERT_EQ(kAmountZero, feeManager.getFee(kOutOfPolicyBounds));
}

/**/

TEST(managers, fee_manager_fee_set_in_bounds) {
  FeeManager feeManager;
  feeManager.setFee(kInPolicyBounds, kCustomFee);
  ASSERT_EQ(kCustomFee, feeManager.getFee(kInPolicyBounds));
}

/**/

TEST(managers, fee_manager_fee_set_out_of_bounds) {
  FeeManager feeManager;
  feeManager.setFee(kOutOfPolicyBounds, kCustomFee);
  ASSERT_EQ(kCustomFee, feeManager.getFee(kOutOfPolicyBounds));
}

/**/

TEST(managers, fee_manager_policy_get) {
  FeeManager feeManager;
  bool isMatching = kDefaultFeePolicy == feeManager.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, fee_manager_policy_set) {
  FeeManager feeManager;
  feeManager.setPolicy(kCustomFeePolicy);
  bool isMatching = kCustomFeePolicy == feeManager.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, fee_manager_comparison_equals) {
  FeeManager feeManager;
  bool isMatching = kDefaultFeePolicy == feeManager.getPolicy();
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, fee_manager_comparison_not_equal) {
  FeeManager feeManager(kCustomFeePolicy);
  bool notMatching = kDefaultFeePolicy != feeManager.getPolicy();
  ASSERT_TRUE(notMatching);
}
