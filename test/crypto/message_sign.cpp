
#include "gtest/gtest.h"

#include <map>

#include "crypto/message.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
#include "utils/hex.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

TEST(crypto, message_sign) {
  Message message;
  message.sign(tMessageString, tPassphrase);

  ASSERT_STREQ(BytesToHex(message.signature.begin(),
                          message.signature.end()).c_str(),
               tSignatureString);
}
