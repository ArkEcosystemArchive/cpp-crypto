
#include "gtest/gtest.h"

#include "common/fee_policy.hpp"
using namespace Ark::Crypto;

namespace {
const FeePolicy CustomFeePolicy = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
}  //namespace

/**/

TEST(common, fee_policy_custom) {
  const FeePolicy feePolicy(CustomFeePolicy);
  for (auto i = 0U; i < CustomFeePolicy.size(); ++i) {
    ASSERT_EQ(feePolicy[i], CustomFeePolicy[i]);
  };
}
