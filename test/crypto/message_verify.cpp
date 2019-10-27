
#include "gtest/gtest.h"

#include <map>

#include "crypto/message.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
#include "utils/hex.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

TEST(crypto, message_verify) {
  Message message(tMessageString,
                  tPublicKeyBytes,
                  { tMessageSignatureBytes.begin(),
                    tMessageSignatureBytes.end() });
  ASSERT_TRUE(message.verify());
}
