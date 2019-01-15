
#include "gtest/gtest.h"

#include "identities/privatekey.h"
using namespace Ark::Crypto::Identities;

namespace {
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const uint8_t testPrivateKeyBytes[32] = {149, 9, 129, 206, 23,  223, 102, 45, 188, 29, 37, 48,  95, 133, 151, 167,
                                         19,  9, 251, 143, 114, 50,  32,  58, 9,   68, 71, 126, 37, 52,  176, 33};
const uint8_t wifByte = 0xaa;

}  // namespace

TEST(identities, privatekey_construct_bytes) {
  PrivateKey privateKey(testPrivateKeyBytes);
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_construct_string) {
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_from_hex) {
  PrivateKey privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_from_passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_from_string) {
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_from_wif_string) {
  const char* wifStr = "SEZuJZouNK8GLXNApjciH4QnSKiNr971exVcL2Y6XfrDF5o977zB";
  PrivateKey privateKey = PrivateKey::fromWIFString(wifStr, wifByte);
  ASSERT_STREQ("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021", privateKey.toString().c_str());
}

TEST(identities, privatekey_get_bytes) {
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  const auto privateKeyBytes = privateKey.toBytes();
  for (unsigned int i = 0; i < PRIVATEKEY_SIZE; i++) {
    ASSERT_EQ(privateKeyBytes[i], testPrivateKeyBytes[i]);
  };
}

TEST(identities, privatekey_validate) {
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  ASSERT_TRUE(PrivateKey::validate(privateKey));
}

TEST(identities, privatekey_validate_bytes) {
  ASSERT_TRUE(PrivateKey::validate(testPrivateKeyBytes));
}

TEST(identities, privatekey_validate_string) {
  ASSERT_TRUE(PrivateKey::validate("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021"));
}
