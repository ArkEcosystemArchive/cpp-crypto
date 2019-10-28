
#include "gtest/gtest.h"

#include "crypto/curve.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

/**/
TEST(crypto, curve_ecdsa_sign) {
  std::vector<uint8_t> signature;
  Curve::Ecdsa::sign(tMessageSha256Bytes.data(),
                     tPrivateKeyBytes.data(),
                     signature);

  for (auto i = 0U; i < signature.size(); ++i) {
    ASSERT_EQ(signature.at(i), tMessageSignatureBytes.at(i));
  };
}
