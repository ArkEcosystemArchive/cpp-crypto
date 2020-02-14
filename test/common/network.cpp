/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "common/network.hpp"

#include "networks/devnet.hpp"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
const Network CustomNetwork {
    "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
    1, 0x53, 0xaa,
    "2019-04-12T13:00:00.000Z"
};

////////////////////////////////////////////////////////////////////////////////
const Network InvalidNetwork {
    "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867",
    1,
    0xaa,
    0x00,
    "2017-03-21T13:00:00.000Z"
};

////////////////////////////////////////////////////////////////////////////////
TEST(common_network, copy_constructor) {
  Network network(CustomNetwork);
  ASSERT_TRUE(network == CustomNetwork);
}

////////////////////////////////////////////////////////////////////////////////
TEST(common_network, members) {
    Network network(Devnet);
    ASSERT_STREQ(Devnet.nethash.c_str(),        network.nethash.c_str());
    ASSERT_EQ(Devnet.slip44,                    network.slip44);
    ASSERT_EQ(Devnet.wif,                       network.wif);
    ASSERT_EQ(Devnet.version,                   network.version);
    ASSERT_STREQ(Devnet.epoch.c_str(),          network.epoch.c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(common_network, comparison_equivalent) {
  Network network(CustomNetwork);
  ASSERT_TRUE(network == CustomNetwork);
}

////////////////////////////////////////////////////////////////////////////////
TEST(common_network, comparison_not_equivalent) {
    Network network(CustomNetwork);
    ASSERT_TRUE(network != Devnet);

    Network invalid(InvalidNetwork);
    ASSERT_TRUE(invalid != Devnet);
}
