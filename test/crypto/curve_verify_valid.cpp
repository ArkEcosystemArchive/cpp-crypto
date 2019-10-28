
#include "gtest/gtest.h"

#include "crypto/curve.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

TEST(crypto, crypto_verify_valid) {
  ASSERT_TRUE(Curve::Ecdsa::verify(tMessageSha256Bytes.data(),
                                   tPublicKeyBytes.data(),
                                   { tMessageSignatureBytes.begin(),
                                     tMessageSignatureBytes.end() }));
}
