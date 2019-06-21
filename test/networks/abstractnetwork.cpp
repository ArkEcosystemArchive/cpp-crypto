
#include "gtest/gtest.h"

#include "networks/abstractnetwork.h"
using namespace Ark::Crypto::Networks;

#include <string>

AbstractNetwork CUSTOM_NETWORK = {
  {
    0x01,  // BASE58_ADDRESS_P2PKH
    0x02,  // BASE58_ADDRESS_P2SH
    0x03   // BASE58_WIF
  },
  {
    00010100,  // BIP32_PREFIX_XPUB
    00010101   // BIP32_PREFIX_XPRV
  },
  "0000-00-00T00:00:00.000Z",  // Epoch
  false                        // isLocked
};

/**/

TEST(networks, abstract_network_default) {
  AbstractNetwork abstractNetwork;
  ASSERT_FALSE(abstractNetwork.isLocked());
};

/**/

TEST(networks, abstract_network_custom) {
  base58_t base58 = { 0x01, 0x02, 0x03 };
  bip32_t bip32 = { 00010100, 00010101 };
  const auto epoch = "0000-00-00T00:00:00.000Z";

  AbstractNetwork testNetwork(base58, bip32, epoch, true);

  ASSERT_EQ(
      CUSTOM_NETWORK.getBase58Prefix(BASE58_ADDRESS_P2PKH),
      testNetwork.getBase58Prefix(BASE58_ADDRESS_P2PKH));
  ASSERT_EQ(
      CUSTOM_NETWORK.getBase58Prefix(BASE58_ADDRESS_P2SH),
      testNetwork.getBase58Prefix(BASE58_ADDRESS_P2SH));
  ASSERT_EQ(
      CUSTOM_NETWORK.getBase58Prefix(BASE58_WIF),
      testNetwork.getBase58Prefix(BASE58_WIF));
  ASSERT_TRUE(testNetwork.isLocked());
}

/**/

TEST(networks, abstract_network_base58_prefix_get) {
  ASSERT_EQ(1, CUSTOM_NETWORK.getBase58Prefix(BASE58_ADDRESS_P2PKH));
  ASSERT_EQ(2, CUSTOM_NETWORK.getBase58Prefix(BASE58_ADDRESS_P2SH));
  ASSERT_EQ(3, CUSTOM_NETWORK.getBase58Prefix(BASE58_WIF));
}

/**/

TEST(networks, abstract_network_base58_prefix_set) {
  AbstractNetwork testNetwork = CUSTOM_NETWORK;

  testNetwork.setBase58Prefix(BASE58_ADDRESS_P2PKH, 0x10);
  ASSERT_EQ(0x10, testNetwork.getBase58Prefix(BASE58_ADDRESS_P2PKH));

  testNetwork.setBase58Prefix(BASE58_ADDRESS_P2SH, 0x20);
  ASSERT_EQ(0x20, testNetwork.getBase58Prefix(BASE58_ADDRESS_P2SH));

  testNetwork.setBase58Prefix(BASE58_WIF, 0x30);
  ASSERT_EQ(0x30, testNetwork.getBase58Prefix(BASE58_WIF));
}

/**/

TEST(networks, abstract_network_bip32_prefix_get) {
  ASSERT_EQ(00010100, CUSTOM_NETWORK.getBIP32Prefix(BIP32_PREFIX_XPUB));
  ASSERT_EQ(00010101, CUSTOM_NETWORK.getBIP32Prefix(BIP32_PREFIX_XPRV));
}

/**/

TEST(networks, abstract_network_bip32_prefix_set) {
  AbstractNetwork testNetwork = CUSTOM_NETWORK;

  testNetwork.setBIP32Prefix(BIP32_PREFIX_XPUB, 1000000);
  ASSERT_EQ(1000000, testNetwork.getBIP32Prefix(BIP32_PREFIX_XPUB));

  testNetwork.setBIP32Prefix(BIP32_PREFIX_XPRV, 1000001);
  ASSERT_EQ(1000001, testNetwork.getBIP32Prefix(BIP32_PREFIX_XPRV));
}

/**/

TEST(networks, abstract_network_epoch) {
  const auto expected = "0000-00-00T00:00:00.000Z";
  ASSERT_STREQ(expected, CUSTOM_NETWORK.epoch());
}

/**/

TEST(networks, abstract_network_is_locked) {
  ASSERT_EQ(false, CUSTOM_NETWORK.isLocked());
}

/**/

TEST(networks, abstract_network_version) {
  AbstractNetwork customNetwork = CUSTOM_NETWORK;
  customNetwork.setBase58Prefix(BASE58_ADDRESS_P2PKH, 0x14);
  ASSERT_EQ(20, customNetwork.version());
}
