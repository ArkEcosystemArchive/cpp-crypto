/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "networks/devnet.hpp"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(networks, devnet) {
    const char* NETHASH         = "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867";
    const uint8_t SLIP44        = 1U;
    const uint8_t WIF           = 0xaa;
    const uint8_t VERSION       = 0x1E;
    const char* EPOCH           = "2017-03-21T13:00:00.000Z";

    ASSERT_STREQ(NETHASH,       Devnet.nethash.c_str());
    ASSERT_EQ(SLIP44,           Devnet.slip44);
    ASSERT_EQ(WIF,              Devnet.wif);
    ASSERT_EQ(VERSION,          Devnet.version);
    ASSERT_STREQ(EPOCH,         Devnet.epoch.c_str());
}
