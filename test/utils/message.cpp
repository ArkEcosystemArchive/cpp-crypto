
#include "gtest/gtest.h"

#include "utils/message.h"

#include <map>

namespace { // NOLINT

// ARK Core test fixtures:
// https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/utils/message.test.ts
const auto text = "Hello World";
const auto passphrase = "this is a top secret passphrase";
const auto expectedSignature = "304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8";
const auto expectedPublicKey = "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
const auto expectedJsonString = "{\"publickey\":\"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192\",\"signature\":\"304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8\",\"message\":\"Hello World\"}";

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
