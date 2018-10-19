
#include "gtest/gtest.h"
#include "arkCrypto.h"

TEST(utils, slot_epoch)
{
    const auto devnet = Ark::Crypto::Networks::Devnet;
    const auto epoch = Ark::Crypto::Utils::Slot::epoch(devnet);
#ifdef USE_IOT
    /* most Arduino do not have 64-bit precision */
    /* measured in seconds vs ms */
    ASSERT_EQ(1490101200, epoch );
#else
    ASSERT_EQ(1490101200000ull, epoch );
#endif
}

TEST(utils, slot_time)
{
    const auto devnet = Ark::Crypto::Networks::Devnet;
    const auto time = Ark::Crypto::Utils::Slot::time(devnet);
#ifdef USE_IOT
    /* most Arduino do not have 64-bit precision */
    /* measured in seconds vs ms */
    // ASSERT_TRUE(time > 46000000);
#else
    ASSERT_TRUE(time > 46000000000);
#endif
}
