
#include "gtest/gtest.h"

#include "crypto/curve.hpp"

#include "fixtures/identity.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;

TEST(crypto, curve_publickey_compute) {
  const auto publicKey = Curve::PublicKey::compute(tPrivateKeyBytes.data());
  for (auto i = 0; i < PUBLICKEY_COMPRESSED_BYTE_LEN; ++i) {
    ASSERT_EQ(publicKey.at(i), tPublicKeyBytes.at(i));
  };
}

/**/

TEST(crypto, curve_publickey_compute_invalid) {
  const auto publicKey =
      Curve::PublicKey::compute(invalid::tPrivateKeyBytes.data());
  for (auto& e : publicKey) {
    ASSERT_EQ(e, 0);
  };
}

/**/

TEST(utils, curve_publickey_validate) {
  ASSERT_TRUE(Curve::PublicKey::validate(tPublicKeyBytes.data()));
}

/**/

TEST(utils, curve_publickey_validate_invalid) {
  ASSERT_FALSE(Curve::PublicKey::validate(invalid::tPublicKeyBytes.data()));
}