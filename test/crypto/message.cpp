
#include "gtest/gtest.h"

#include <map>

#include "crypto/message.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
#include "utils/hex.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;


TEST(crypto, message_to_array) {
  Message message;
  message.sign(tMessageString, tPassphrase);
  auto messageArray = message.toArray();

  ASSERT_STREQ(tMessageString, messageArray["message"].c_str());
  ASSERT_STREQ(tPublicKeyHex, messageArray["publickey"].c_str());
  ASSERT_STREQ(tSignatureString, messageArray["signature"].c_str());
}

/**/

TEST(crypto, message_to_json) {
  Message message;
  message.sign(tMessageString, tPassphrase);
  ASSERT_STREQ(message.toJson().c_str(), tMessageJsonString);
}
