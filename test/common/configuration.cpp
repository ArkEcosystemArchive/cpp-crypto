/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include <cstdint>

#include "common/configuration.hpp"

#include "transactions/defaults/fees.hpp"

#include "networks/devnet.hpp"
#include "networks/testnet.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

static const FeePolicy CustomFeePolicy = {
    900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
    400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, constructor_default) {
    Configuration config;
    Configuration custom(Devnet, StaticFeePolicy);
    ASSERT_TRUE(config == custom);
}

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, constructor_network) {
    Configuration config(Testnet);
    ASSERT_TRUE(config.getNetwork() == Testnet);
    ASSERT_TRUE(config.getPolicy() == StaticFeePolicy);
}

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, constructor_fee_policy) {
    Configuration config(CustomFeePolicy);
    ASSERT_TRUE(config.getNetwork() == Devnet);
    ASSERT_TRUE(config.getPolicy() == CustomFeePolicy);
}

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, constructor_network_and_fee_policy) {
    Configuration config(Testnet, CustomFeePolicy);
    ASSERT_TRUE(config.getNetwork() == Testnet);
    ASSERT_TRUE(config.getPolicy() == CustomFeePolicy);
}

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, comparison_equivalent) {
    Configuration config;
    Configuration custom(Devnet, StaticFeePolicy);
    ASSERT_TRUE(config == custom);
}

////////////////////////////////////////////////////////////////////////////////

TEST(common_configuration, comparison_not_equivalent) {
    Configuration config;
    Configuration custom(Testnet);
    ASSERT_TRUE(config != custom);
}

////////////////////////////////////////////////////////////////////////////////
