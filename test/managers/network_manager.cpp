
#include "gtest/gtest.h"

#include <arkCrypto.h>

using namespace managers;

namespace {  // NOLINT
static const Network kDefaultNetwork = Networks::Devnet();
static const Network kCustomNetwork {
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};
/**/
static const NetworkManager kDefaultNetworkManager = NetworkManager();
static const NetworkManager kCustomNetworkManager = NetworkManager(kCustomNetwork);
}  //namespace

/**/

TEST(managers, network_manager_constructor_default) {
  NetworkManager networkManager;
  bool isMatching = kDefaultNetworkManager == networkManager;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, network_manager_network_constructor) {
  NetworkManager networkManager(kCustomNetwork);
  bool isMatching = kCustomNetworkManager == networkManager;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, network_manager_get) {
  NetworkManager networkManager;
  bool isMatching = kDefaultNetworkManager == networkManager;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, network_manager_set) {
  NetworkManager networkManager;
  networkManager.setNetwork(kCustomNetwork);
  bool isMatching = kCustomNetworkManager == networkManager;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, network_manager_comparison_equals) {
  NetworkManager networkManager;
  bool isMatching = kDefaultNetworkManager == networkManager;
  ASSERT_TRUE(isMatching);
}

/**/

TEST(managers, network_manager_comparison_not_equal) {
  NetworkManager networkManager(kCustomNetwork);
  bool notMatching = kDefaultNetworkManager != networkManager;
  ASSERT_TRUE(notMatching);
}