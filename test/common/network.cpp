
#include "gtest/gtest.h"

#include <arkCrypto.h>

namespace {
const Network CustomNetwork {
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};
const Network InvalidNetwork {
    "2a44f340d76ffc3df204c5f38cd355b7496c9065a1ade2ef92071436bd72e867",
    1,
    0xaa,
    0x00,
    "2017-03-21T13:00:00.000Z"
};
}  // namespace

/**/

TEST(common, network_constructor) {
  Network network(CustomNetwork);
  ASSERT_TRUE(network == CustomNetwork);
}

/**/

TEST(common, network_get_parameters) {
  Network network(Devnet);
  ASSERT_STREQ(network.nethash.c_str(), Devnet.nethash.c_str());
  ASSERT_EQ(network.slip44,             Devnet.slip44);
  ASSERT_EQ(network.wif,                Devnet.wif);
  ASSERT_EQ(network.version,            Devnet.version);
  ASSERT_STREQ(network.epoch.c_str(),   Devnet.epoch.c_str());
}

/**/

TEST(common, network_comparison_equals) {
  Network network(CustomNetwork);
  ASSERT_TRUE(network == CustomNetwork);
}

/**/

TEST(common, network_comparison_not_equal) {
  Network network(CustomNetwork);
  ASSERT_TRUE(network != Devnet);

  Network invalid(InvalidNetwork);
  ASSERT_TRUE(invalid != Devnet);
}
