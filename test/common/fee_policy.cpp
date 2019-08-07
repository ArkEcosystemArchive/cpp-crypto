
#include "gtest/gtest.h"

#include <arkCrypto.h>

namespace {
static const FeePolicy kCustomFeePolicy = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};
}  //namespace

/**/

TEST(common, fee_policy_custom) {
  const FeePolicy feePolicy(kCustomFeePolicy);
  for (auto i = 0U; i < kCustomFeePolicy.size(); ++i) {
    ASSERT_EQ(kCustomFeePolicy[i], feePolicy[i]);
  };
}
