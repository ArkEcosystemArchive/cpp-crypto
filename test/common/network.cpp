
#include "gtest/gtest.h"

#include <arkCrypto.h>

namespace {  // NOLINT
static const Network kDevnetNetwork = Networks::Devnet();
/**/
static const std::string kCustomNethash  = "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df";
static const uint8_t kCustomSlip44       = 1;
static const uint8_t kCustomWif          = 0x53;
static const uint8_t kCustomVersion      = 0xaa;
static const std::string kCustomEpoch    = "2019-04-12T13:00:00.000Z";
/**/
static const Network kCustomNetwork {
  kCustomNethash,
  kCustomSlip44, kCustomWif, kCustomVersion,
  kCustomEpoch
};
}  // namespace

/**/

TEST(common, network_constructor_default) {
  Network network;
  bool networksMatch = kDevnetNetwork == network;
  ASSERT_TRUE(networksMatch);
}

/**/

TEST(common, network_constructor_list) {
  Network customNetwork = { kCustomNethash,
                            kCustomSlip44,
                            kCustomWif,
                            kCustomVersion,
                            kCustomEpoch };
  bool networksMatch = kCustomNetwork == customNetwork;
  ASSERT_TRUE(networksMatch);
}

/**/

TEST(common, network_comparison_equals) {
 Network customNetwork(kDevnetNetwork);
  bool networksMatch = kDevnetNetwork == customNetwork;
  ASSERT_TRUE(networksMatch);
}

/**/

TEST(common, network_comparison_not_equal) {
 Network customNetwork(kCustomNetwork);
  bool networksMatch = kDevnetNetwork != customNetwork;
  ASSERT_TRUE(networksMatch);
}

/**/

TEST(common, network_get_parameters) {
  Network network(kDevnetNetwork);
  ASSERT_STREQ(kDevnetNetwork.nethash().c_str(), network.nethash().c_str());
  ASSERT_EQ(kDevnetNetwork.slip44(),             network.slip44());
  ASSERT_EQ(kDevnetNetwork.wif(),                network.wif());
  ASSERT_EQ(kDevnetNetwork.version(),            network.version());
  ASSERT_STREQ(kDevnetNetwork.epoch().c_str(),   network.epoch().c_str());
}
