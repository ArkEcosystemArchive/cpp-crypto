/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "networks/testnet.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////

TEST(networks, testnet) {  // NOLINT
    const char* NETHASH     = "d9acd04bde4234a81addb8482333b4ac906bed7be5a9970ce8ada428bd083192";
    const uint8_t SLIP44    = 1U;
    const uint8_t WIF       = 0xba;
    const uint8_t VERSION   = 0x17;
    const char* EPOCH       = "2017-03-21T13:00:00.000Z";

    ASSERT_STREQ(NETHASH,   Testnet.nethash.c_str());
    ASSERT_EQ(SLIP44,       Testnet.slip44);
    ASSERT_EQ(WIF,          Testnet.wif);
    ASSERT_EQ(VERSION,      Testnet.version);
    ASSERT_STREQ(EPOCH,     Testnet.epoch.c_str());
}

////////////////////////////////////////////////////////////////////////////////
