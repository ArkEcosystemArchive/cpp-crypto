
#include "gtest/gtest.h"

#include "managers/fee_manager.hpp"
#include "defaults/static_fees.hpp"

using namespace Ark::Crypto;
using namespace Ark::Crypto::managers;

namespace {
const FeePolicy CustomFeePolicy {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
constexpr const uint8_t InBounds = 5U;
constexpr const uint8_t OutOfBounds = 11;
constexpr const uint64_t CustomFee = 1000ULL;
}  //namespace

/**/

TEST(managers, fee_manager_fee_get) {
  FeeManager feeManager;
  for (auto i = 0u; i < StaticFeePolicy.size(); ++i) {
    ASSERT_EQ(feeManager.getFee(i), StaticFeePolicy.at(i));
  };
}

/**/

TEST(managers, fee_manager_fee_get_oob) {
  FeeManager feeManager;
  ASSERT_EQ(feeManager.getFee(OutOfBounds), AMOUNT_ZERO);
}

/**/

TEST(managers, fee_manager_fee_set) {
  FeeManager feeManager;
  feeManager.setFee(InBounds, CustomFee);
  ASSERT_EQ(feeManager.getFee(InBounds), CustomFee);
}

/**/

TEST(managers, fee_manager_fee_set_oob) {
  FeeManager feeManager;
  feeManager.setFee(OutOfBounds, CustomFee);
  ASSERT_EQ(feeManager.getFee(OutOfBounds), CustomFee);
}

/**/

TEST(managers, fee_manager_policy_get) {
  FeeManager feeManager;
  ASSERT_TRUE(feeManager.getPolicy() == StaticFeePolicy);
}

/**/

TEST(managers, fee_manager_policy_set) {
  FeeManager feeManager;
  feeManager.setPolicy(CustomFeePolicy);
  ASSERT_TRUE(feeManager.getPolicy() == CustomFeePolicy);
}
