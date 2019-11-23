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
#include <vector>

#include "utils/crypto_helpers.h"

////////////////////////////////////////////////////////////////////////////////

TEST(utils_crypto_helpers, unpack) {
    std::vector<uint8_t> packBuffer;
    const uint8_t packValue = 23U;
    pack(packBuffer, packValue);

    uint8_t unpackValue;
    unpack(&unpackValue, &packBuffer[0]);
    ASSERT_EQ(packValue, unpackValue);
}

////////////////////////////////////////////////////////////////////////////////

TEST(utils_crypto_helpers, join) {
    const auto strBuffer = "123";
    std::vector<std::string> vstr(3);
    vstr.at(0) = strBuffer[0];
    vstr.at(1) = strBuffer[1];
    vstr.at(2) = strBuffer[2];

    std::string joined = join(vstr);
    ASSERT_STREQ(strBuffer, joined.c_str());
}

////////////////////////////////////////////////////////////////////////////////
