
#include "gtest/gtest.h"

#include "identities/wif.h"
using namespace Ark::Crypto::Identities;

namespace {
    const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
    const uint8_t testWIFBytes[52] = {
        83, 69, 90, 117, 74, 90, 111, 117, 78, 75, 56, 71, 76, 88, 78, 65,
        112, 106, 99, 105, 72, 52, 81, 110, 83, 75, 105, 78, 114, 57, 55, 49,
        101, 120, 86, 99, 76, 50, 89, 54, 88, 102, 114, 68, 70, 53, 111, 57, 55, 55, 122, 66 
    };
    const uint8_t wifByte = 0xaa;
}

TEST(identities, wif_from_bytes)
{
    WIF wif(testWIFBytes);
    ASSERT_STREQ("SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB", wif.toString().c_str());
}

TEST(identities, wif_from_passphrase)
{
    WIF wif = WIF::fromPassphrase(passphrase, wifByte);
    ASSERT_STREQ("SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB", wif.toString().c_str());
}

TEST(identities, wif_from_string)
{
    WIF wif("SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB");
    ASSERT_STREQ("SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB", wif.toString().c_str());
}

TEST(identities, wif_get_bytes)
{
    WIF wif("SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB");
    const auto wifBytes = wif.toBytes();
    for (unsigned int i = 0; i < WIF_SIZE; i++)
    {
        ASSERT_EQ(wifBytes[i], testWIFBytes[i]);
    };
}
