/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "utils/str.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
constexpr auto PassphraseLength = 31U;

////////////////////////////////////////////////////////////////////////////////
TEST(utils_str, strlen_safe) {
    const auto passphrase = fixtures::Passphrase;
    for (auto i = 0U; i < PassphraseLength; ++i) {
        ASSERT_EQ(strlenSafe(&passphrase[i]), PassphraseLength - i);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(utils_str, string_to_bytes) {
    const auto passphraseBytes = StringToBytes(fixtures::Passphrase);
    ASSERT_TRUE(array_cmp(fixtures::PassphraseBytes.data(),
                          passphraseBytes.data(),
                          passphraseBytes.size()));

    ASSERT_EQ(passphraseBytes.size(), PassphraseLength);
}
