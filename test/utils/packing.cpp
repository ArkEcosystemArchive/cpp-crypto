/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "utils/packing.h"

#include <array>
#include <cstdint>

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////
constexpr uint16_t U16  = 1U;
constexpr uint32_t U32  = 1UL;
constexpr uint64_t U64  = 1ULL;

constexpr std::array<uint8_t, sizeof(uint16_t)> Packed2LE   = { 1U, 0U };
constexpr std::array<uint8_t, sizeof(uint32_t)> Packed4LE   = { 1U, 0U, 0U, 0U };
constexpr std::array<uint8_t, sizeof(uint64_t)> Packed8LE   = { 1U, 0U, 0U, 0U,
                                                                0U, 0U, 0U, 0U };

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, pack_2_le) {
    std::array<uint8_t, sizeof(uint16_t)> packed2LE {};

    pack2LE(packed2LE.data(), &U16);

    ASSERT_TRUE(array_cmp(Packed2LE.data(), packed2LE.data(), sizeof(uint16_t)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, pack_4_le) {
    std::array<uint8_t, sizeof(uint32_t)> packed4LE {};

    pack4LE(packed4LE.data(), &U32);

    ASSERT_TRUE(array_cmp(Packed4LE.data(), packed4LE.data(), sizeof(uint32_t)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, pack_8_le) {
    std::array<uint8_t, sizeof(uint64_t)> packed8LE {};

    pack8LE(packed8LE.data(), &U64);

    ASSERT_TRUE(array_cmp(Packed4LE.data(), packed8LE.data(), sizeof(uint32_t)));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, unpack_2_le) {
    const auto unpacked2 = unpack2LE(Packed2LE, 0);
    ASSERT_EQ(U16, unpacked2);
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, unpack_4_le) {
    const auto unpacked4 = unpack4LE(Packed4LE, 0);
    ASSERT_EQ(U32, unpacked4);
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_packing, unpack_8_le) {
    const auto unpacked8 = unpack8LE(Packed8LE, 0);
    ASSERT_EQ(U64, unpacked8);
}
