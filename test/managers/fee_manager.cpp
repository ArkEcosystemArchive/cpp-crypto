/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "managers/fee_manager.hpp"

#include "transactions/defaults/fees.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::managers;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

static const FeePolicy CustomFeePolicy {
    900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
    400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};

////////////////////////////////////////////////////////////////////////////////

static constexpr const uint8_t InBounds         = 5U;
static constexpr const uint8_t OutOfBounds      = 11;
static constexpr const uint64_t CustomFee       = 1000ULL;

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, get) {
    FeeManager feeManager;
    uint8_t i = 0;
    for (auto &fee : StaticFeePolicy) {
        ASSERT_EQ(fee, feeManager.getFee(i));
        ++i;
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, get_out_of_bounds) {
    FeeManager feeManager;
    ASSERT_EQ(0ULL, feeManager.getFee(OutOfBounds));
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, set) {
    FeeManager feeManager;
    feeManager.setFee(InBounds, CustomFee);
    ASSERT_EQ(CustomFee, feeManager.getFee(InBounds));
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, set_out_of_bounds) {
    FeeManager feeManager;
    feeManager.setFee(OutOfBounds, CustomFee);
    ASSERT_EQ(CustomFee, feeManager.getFee(OutOfBounds));
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, policy_get) {
    FeeManager feeManager;
    ASSERT_TRUE(StaticFeePolicy == feeManager.getPolicy());
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_fee_manager, policy_set) {
    FeeManager feeManager;
    feeManager.setPolicy(CustomFeePolicy);
    ASSERT_TRUE(CustomFeePolicy == feeManager.getPolicy());
}

////////////////////////////////////////////////////////////////////////////////
