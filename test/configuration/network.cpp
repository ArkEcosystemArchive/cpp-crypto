
#include "arkCrypto.h"
#include "gtest/gtest.h"

TEST(configuration, network_get) {
  auto network = Network().get();  // defaults to devnet
  ASSERT_EQ(0x1E, network.getBase58Prefix(BASE58_ADDRESS_P2PKH));
  ASSERT_EQ(0x00, network.getBase58Prefix(BASE58_ADDRESS_P2SH));
  ASSERT_EQ(0xaa, network.getBase58Prefix(BASE58_WIF));
  ASSERT_EQ(46090600, network.getBIP32Prefix(BIP32_PREFIX_XPUB));
  ASSERT_EQ(46089520, network.getBIP32Prefix(BIP32_PREFIX_XPRV));
  ASSERT_STREQ("2017-03-21T13:00:00.000Z", network.epoch());
  ASSERT_EQ(true, network.isLocked());
  ASSERT_EQ(30, network.version());
}

/**/

TEST(configuration, network_set) {
  Network network;
  network.set(Testnet);
  auto testnet = network.get();
  ASSERT_EQ(0x17, testnet.getBase58Prefix(BASE58_ADDRESS_P2PKH));
  ASSERT_EQ(0x00, testnet.getBase58Prefix(BASE58_ADDRESS_P2SH));
  ASSERT_EQ(0xba, testnet.getBase58Prefix(BASE58_WIF));
  ASSERT_EQ(70617039, testnet.getBIP32Prefix(BIP32_PREFIX_XPUB));
  ASSERT_EQ(70615956, testnet.getBIP32Prefix(BIP32_PREFIX_XPRV));
  ASSERT_STREQ("2017-03-21T13:00:00.000Z", testnet.epoch());
  ASSERT_EQ(true, testnet.isLocked());
  ASSERT_EQ(23, testnet.version());
}
