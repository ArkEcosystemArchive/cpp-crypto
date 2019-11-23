/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "networks/mainnet.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////

TEST(networks, mainnet) {  // NOLINT
  const char* NETHASH       = "6e84d08bd299ed97c212c886c98a57e36545c8f5d645ca7eeae63a8bd62d8988";
  const uint8_t SLIP44      = 111U;
  const uint8_t WIF         = 0xaa;
  const uint8_t VERSION     = 0x17;
  const char* EPOCH         = "2017-03-21T13:00:00.000Z";

  ASSERT_STREQ(NETHASH,     Mainnet.nethash.c_str());
  ASSERT_EQ(SLIP44,         Mainnet.slip44);
  ASSERT_EQ(WIF,            Mainnet.wif);
  ASSERT_EQ(VERSION,        Mainnet.version);
  ASSERT_STREQ(EPOCH,       Mainnet.epoch.c_str());
}

////////////////////////////////////////////////////////////////////////////////
