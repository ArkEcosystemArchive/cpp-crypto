/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "utils/hex.hpp"

#include "fixtures/message.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, bytes_to_hex) {
    const auto result = BytesToHex(fixtures::MessageSignatureBytes.begin(),
                                   fixtures::MessageSignatureBytes.end());
    ASSERT_STREQ(fixtures::MessageSignatureString, result.c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes) {
    const auto result = HexToBytes(fixtures::MessageSignatureString);
    ASSERT_TRUE(array_cmp(fixtures::MessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_spaces) {
    const auto result = HexToBytes(fixtures::MessageSignatureStringSpaces);
    ASSERT_TRUE(array_cmp(fixtures::MessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_array) {
    const auto result = HexToBytesArray<>(fixtures::MessageSignatureString);
    ASSERT_TRUE(array_cmp(fixtures::MessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_array_spaces) {
    const auto result = HexToBytesArray<>(fixtures::MessageSignatureStringSpaces);
    ASSERT_TRUE(array_cmp(fixtures::MessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_array_null_input) {
    const auto result = HexToBytesArray<>(nullptr);
    for (auto &e : result) {
        ASSERT_EQ(0U, e);
    }
}
