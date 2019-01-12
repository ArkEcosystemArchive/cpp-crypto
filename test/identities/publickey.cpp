
#include "gtest/gtest.h"

#include "identities/publickey.h"
using namespace Ark::Crypto::Identities;

namespace {
    const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
    const uint8_t testPublicKeyBytes[33] = {
        2, 159, 223, 65, 167, 214, 157, 142,
        252, 123, 35, 108, 33, 185, 80, 154,
        35, 216, 98, 234, 78, 216, 177, 58,
        86, 227, 30, 238, 88, 219, 253, 151, 180
    };
}

TEST(identities, publickey_from_bytes)
{
    PublicKey publicKey(testPublicKeyBytes);
    ASSERT_STREQ("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4", publicKey.toString().c_str());
}

TEST(identities, publickey_from_hex)
{
    PublicKey publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
    ASSERT_STREQ("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4", publicKey.toString().c_str());
}

TEST(identities, publickey_from_passphrase)
{
    PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
    ASSERT_STREQ("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4", publicKey.toString().c_str());
}

TEST(identities, publickey_from_string)
{
    PublicKey publicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
    ASSERT_STREQ("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4", publicKey.toString().c_str());
}

TEST(identities, publickey_get_bytes)
{
    PublicKey publicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
    const auto publicKeyBytes = publicKey.toBytes();
    for (unsigned int i = 0; i < COMPRESSED_PUBLICKEY_SIZE; i++)
    {
        ASSERT_EQ(publicKeyBytes[i], testPublicKeyBytes[i]);
    };
}

TEST(identities, publickey_validate)
{
    PublicKey publicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
    ASSERT_TRUE(PublicKey::validate(publicKey));
}

TEST(identities, publickey_validate_bytes)
{
    ASSERT_TRUE(PublicKey::validate(testPublicKeyBytes));
}

TEST(identities, publickey_validate_string)
{
    ASSERT_TRUE(PublicKey::validate("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4"));
}
