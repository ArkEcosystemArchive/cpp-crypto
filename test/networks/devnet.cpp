#include "gtest/gtest.h"

#include "arkCrypto.h"

TEST(networks, devnet_base58_prefix_get)
{
    ASSERT_EQ(0x1E, Devnet.getBase58Prefix(BASE58_ADDRESS_P2PKH));
    ASSERT_EQ(0x00, Devnet.getBase58Prefix(BASE58_ADDRESS_P2SH));
    ASSERT_EQ(0xaa, Devnet.getBase58Prefix(BASE58_WIF));
}

TEST(networks, devnet_bip32_prefix_get)
{
    ASSERT_EQ(46090600, Devnet.getBIP32Prefix(BIP32_PREFIX_XPUB));
    ASSERT_EQ(46089520, Devnet.getBIP32Prefix(BIP32_PREFIX_XPRV));
}

TEST(networks, devnet_epoch)
{
    ASSERT_STREQ("2017-03-21T13:00:00Z", Devnet.epoch());
}

TEST(networks, devnet_is_locked)
{
    ASSERT_EQ(true, Devnet.isLocked());
}

TEST(networks, devnet_version)
{
    ASSERT_EQ(30, Devnet.version());
}
