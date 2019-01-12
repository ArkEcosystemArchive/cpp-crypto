
#include "gtest/gtest.h"

#include "identities/address.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"
using namespace Ark::Crypto::Identities;

namespace {
    const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
    const uint8_t networkVersion = 0x1E;
}

TEST(identities, address_from_passphrase)
{
    Address address = Address::fromPassphrase(passphrase, networkVersion);
    ASSERT_STREQ("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV", address.toString().c_str());
}

TEST(identities, address_from_privatekey)
{
    PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
    Address address = Address::fromPrivateKey(privateKey, networkVersion);
    ASSERT_STREQ("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV", address.toString().c_str());
}

TEST(identities, address_from_publickey)
{
    PublicKey publicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
    Address address = Address::fromPublicKey(publicKey, networkVersion);
    ASSERT_STREQ("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV", address.toString().c_str());
}

TEST(identities, address_from_string)
{
    Address address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
    ASSERT_STREQ("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV", address.toString().c_str());
}

TEST(identities, address_validate)
{
    Address address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
    ASSERT_TRUE(Address::validate(address, networkVersion));
}
