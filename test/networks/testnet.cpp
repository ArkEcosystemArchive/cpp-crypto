#include "gtest/gtest.h"

#include "arkCrypto.h"

TEST(networks, testnet_base58_prefix_get)
{
    ASSERT_EQ(0x17, Testnet.getBase58Prefix(BASE58_ADDRESS_P2PKH));
    ASSERT_EQ(0x00, Testnet.getBase58Prefix(BASE58_ADDRESS_P2SH));
    ASSERT_EQ(0xba, Testnet.getBase58Prefix(BASE58_WIF));
}

TEST(networks, testnet_bip32_prefix_get)
{
    ASSERT_EQ(70617039, Testnet.getBIP32Prefix(BIP32_PREFIX_XPUB));
    ASSERT_EQ(70615956, Testnet.getBIP32Prefix(BIP32_PREFIX_XPRV));
}

TEST(networks, testnet_epoch)
{
    ASSERT_STREQ("2017-03-21T13:00:00.000Z", Testnet.epoch());
}

TEST(networks, testnet_is_locked)
{
    ASSERT_EQ(true, Testnet.isLocked());
}

TEST(networks, testnet_version)
{
    ASSERT_EQ(23, Testnet.version());
}
