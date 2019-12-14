/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "common/fee_policy.hpp"


using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
const FeePolicy CustomFeePolicy = {
    900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
    400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};

////////////////////////////////////////////////////////////////////////////////
TEST(common_fee_policy, custom) {
    const FeePolicy feePolicy(CustomFeePolicy);

    uint8_t i = 0U;
    for (auto &fee : feePolicy) {
        ASSERT_EQ(feePolicy.at(i), fee);
        ++i;
    }
}
