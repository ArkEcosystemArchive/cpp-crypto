#include "gtest/gtest.h"

#include "networks/mainnet.h"
using namespace Ark::Crypto::Networks;

TEST(networks, mainnet_base58_prefix_get) {
  ASSERT_EQ(0x17, Mainnet.getBase58Prefix(BASE58_ADDRESS_P2PKH));
  ASSERT_EQ(0x00, Mainnet.getBase58Prefix(BASE58_ADDRESS_P2SH));
  ASSERT_EQ(0xaa, Mainnet.getBase58Prefix(BASE58_WIF));
}

TEST(networks, mainnet_bip32_prefix_get) {
  ASSERT_EQ(46090600, Mainnet.getBIP32Prefix(BIP32_PREFIX_XPUB));
  ASSERT_EQ(46089520, Mainnet.getBIP32Prefix(BIP32_PREFIX_XPRV));
}

TEST(networks, mainnet_epoch) {
  ASSERT_STREQ("2017-03-21T13:00:00Z", Mainnet.epoch());
}

TEST(networks, mainnet_is_locked) { ASSERT_EQ(true, Mainnet.isLocked()); }

TEST(networks, mainnet_version) { ASSERT_EQ(23, Mainnet.version()); }
