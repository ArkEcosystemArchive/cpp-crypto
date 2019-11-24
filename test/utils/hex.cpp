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
using namespace fixtures::message;

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, bytes_to_hex) {
    const auto result = BytesToHex(tMessageSignatureBytes.begin(),
                                   tMessageSignatureBytes.end());
    ASSERT_STREQ(tSignatureString, result.c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes) {
    const auto result = HexToBytes(tSignatureString);
    ASSERT_TRUE(array_cmp(tMessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_spaces) {
    const auto result = HexToBytes(tSignatureStringSpaces);
    ASSERT_TRUE(array_cmp(tMessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_array) {
    const auto result = HexToBytesArray<>(tSignatureString);
    ASSERT_TRUE(array_cmp(tMessageSignatureBytes.data(),
                          result.data(),
                          result.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_hex, hex_to_bytes_array_spaces) {
    const auto result = HexToBytesArray<>(tSignatureStringSpaces);
    ASSERT_TRUE(array_cmp(tMessageSignatureBytes.data(),
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
