/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "utils/unpack.h"

#include <array>
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
TEST(utils_unpack, le_2) {
    const uint16_t AMOUNT_16 = 1ULL;
    const std::array<uint8_t, sizeof(uint16_t)>
    AMOUNT_16_ARRAY_LE = { 1U, 0U };

    ASSERT_EQ(AMOUNT_16, unpack2LE(AMOUNT_16_ARRAY_LE, 0));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_unpack, le_4) {
    const uint32_t AMOUNT_32 = 1ULL;
    const std::array<uint8_t, sizeof(uint32_t)>
    AMOUNT_32_ARRAY_LE = { 1U, 0U, 0U, 0U };

    ASSERT_EQ(AMOUNT_32, unpack4LE(AMOUNT_32_ARRAY_LE, 0));

}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_unpack, le_8) {
    const uint64_t AMOUNT_64 = 1ULL;
    const std::array<uint8_t, sizeof(uint64_t)>
    AMOUNT_64_ARRAY_LE = { 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

    ASSERT_EQ(AMOUNT_64, unpack8LE(AMOUNT_64_ARRAY_LE, 0));
}
