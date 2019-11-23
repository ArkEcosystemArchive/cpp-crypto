/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "managers/network_manager.hpp"

#include "common/network.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace managers;

////////////////////////////////////////////////////////////////////////////////

static const Network CustomNetwork {
    "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
    1, 0x53, 0xaa,
    "2019-04-12T13:00:00.000Z"
};

////////////////////////////////////////////////////////////////////////////////

TEST(managers_network_manager, get) {
    NetworkManager manager;
    ASSERT_TRUE(Devnet  == manager.getNetwork());
}

////////////////////////////////////////////////////////////////////////////////

TEST(managers_network_manager, set) {
    NetworkManager manager;
    manager.setNetwork(CustomNetwork);

    ASSERT_TRUE(CustomNetwork == manager.getNetwork());
}

////////////////////////////////////////////////////////////////////////////////
