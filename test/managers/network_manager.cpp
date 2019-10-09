
#include "gtest/gtest.h"

#include "managers/network_manager.hpp"
#include "common/network.hpp"

using namespace Ark::Crypto;
using namespace managers;

namespace {
const Network CustomNetwork {
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};
}  //namespace

/**/

TEST(managers, network_manager_network_get) {
  NetworkManager manager;
  ASSERT_TRUE(manager.getNetwork() == Devnet);
}

/**/

TEST(managers, network_manager_network_set) {
  NetworkManager manager;
  manager.setNetwork(CustomNetwork);
  ASSERT_TRUE(manager.getNetwork() == CustomNetwork);
}
