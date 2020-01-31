/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "crypto/slot.hpp"

#include "networks/devnet.hpp"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_slots, epoch) {
    const auto arkEpoch = 1490101200ULL;
    ASSERT_EQ(arkEpoch, Slot::epoch(Devnet));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_slots, time) {
    // 28 Jan 2019(in seconds) - Ark Epoch (seconds)
    const auto testTime = (1548725761ULL - 1490101200ULL); 
    const auto slotTime = Slot::time(Devnet);

    // test that slot-time is more recent than 'testTime',
    ASSERT_GT(slotTime , testTime);

    // also check that the 'slotTime' is not too large (e.g. from an overflow).
    ASSERT_LT(slotTime, (testTime) + 315360000ULL); // 315360000s = 10yrs
}
