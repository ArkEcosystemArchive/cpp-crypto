
#include "gtest/gtest.h"

#include "utils/message.h"

#include <map>

namespace { // NOLINT
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";
const auto expectedSignature = "3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93";
const auto expectedPublicKey = "0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456";
const auto expectedJsonString = "{\"publickey\":\"0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456\",\"signature\":\"3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93\",\"message\":\"Computer science is no more about computers than astronomy is about telescopes.\"}";
}  // namespace

TEST(utils, message_sign) {
  Ark::Crypto::Utils::Message message;

  message.sign(text, passphrase);

  ASSERT_STREQ(expectedSignature, BytesToHex(message.signature).c_str());
  ASSERT_TRUE(message.verify());
}

TEST(utils, message_to_array) {
  Ark::Crypto::Utils::Message message;

  message.sign(text, passphrase);

  std::map<std::string, std::string> messageArray = message.toArray();

  ASSERT_STREQ(expectedPublicKey, messageArray["publickey"].c_str());
  ASSERT_STREQ(expectedSignature, messageArray["signature"].c_str());
  ASSERT_STREQ(text, messageArray["message"].c_str());
}

TEST(utils, message_to_json) {
  Ark::Crypto::Utils::Message message;

  message.sign(text, passphrase);

  ASSERT_STREQ(expectedJsonString, message.toJson().c_str());
}

TEST(utils, message_verify) {
  PublicKey publicKey = PublicKey::fromHex(expectedPublicKey);
  std::vector<uint8_t> signature = HexToBytes(expectedSignature);

  Ark::Crypto::Utils::Message message(text, publicKey, signature);

  ASSERT_TRUE(message.verify());
}
