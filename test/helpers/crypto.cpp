
#include "gtest/gtest.h"

#include <array>

#include "identities/privatekey.hpp"
#include "identities/publickey.hpp"

#include "bcl/Sha256.hpp"
#include "bcl/Uint256.hpp"

#include "helpers/crypto.h"

namespace { // NOLINT
  std::vector<uint8_t> MessageHashTestBytes = {
    165, 145, 166, 212,  11, 244,  32,  64,
     74,   1,  23,  51, 207, 183, 177, 144,
    214,  44, 101, 191,  11, 205, 163,  43,
     87, 178, 119, 217, 173, 159,  20, 110
  };

  std::array<uint8_t, 32> PrivateKeyTestBytes = {
    216, 131, 156,  36,  50, 191, 208, 166,
    126, 241,  10, 128,  75, 169, 145, 234,
    187, 161, 159,  21,  74,  61, 112, 121,
    23, 104,  29,  69, 130,  42,  87,  18
  };

  std::array<uint8_t, 33> PublicKeyTestBytes = {
      3,
     65,  81, 163, 236,  70, 181, 103,  10,
    104,  43,  10,  99,  57,  79, 134,  53,
    135, 209, 188, 151,  72,  59,  27, 108,
    112, 235,  88, 231, 240, 174, 209, 146
  };
  std::array<uint8_t, 33> InvalidPublicKeyTestBytes = {
      3,
     66,  81, 163, 236,  70, 181, 103,  10,
    104,  43,  10,  99,  57,  79, 134,  53,
    135, 209, 188, 151,  72,  59,  27, 108,
    112, 235,  88, 231, 240, 174, 209, 146
  };

  std::vector<uint8_t> RValueTestBytes = {
     15, 180, 173, 221, 209, 241, 214,  82,
    181,  68, 234, 106, 182,  40,  40, 160,
    166,  91, 113,  46, 212,  71, 226,  83,
    141, 176, 202, 235, 250, 104, 146, 158
  };

  std::vector<uint8_t> SValueTestBytes = {
     94, 203,  46,  28,  99, 178, 152, 121,
    194, 236, 241,  37,  93, 181,   6, 214,
    113, 200, 179, 250,  96,  23, 246, 124,
    253,  27, 240, 126, 110, 221,  28, 200
  };

  std::vector<uint8_t> SignatureTestBytes = {
     48,  68,   2,  32,  15, 180, 173, 221, 209, 241,
    214,  82, 181,  68, 234, 106, 182,  40,  40, 160,
    166,  91, 113,  46, 212,  71, 226,  83, 141, 176,
    202, 235, 250, 104, 146, 158,   2,  32,  94, 203,
     46,  28,  99, 178, 152, 121, 194, 236, 241,  37,
     93, 181,   6, 214, 113, 200, 179, 250,  96,  23,
    246, 124, 253,  27, 240, 126, 110, 221,  28, 200
  };
};

/**/

TEST(helpers, crypto_sign) {
  Sha256Hash hash(&MessageHashTestBytes[0], MessageHashTestBytes.size());
  Ark::Crypto::identities::PrivateKey privateKey(PrivateKeyTestBytes);
  std::vector<uint8_t> signature;
  cryptoSign(
      hash,
      privateKey,
      signature);

  for (auto i = 0U; i < signature.size(); ++i) {
    ASSERT_EQ(signature[i], SignatureTestBytes[i]);
  };
}

/**/

TEST(helpers, crypto_verify_valid) {
  Ark::Crypto::identities::PublicKey publicKey(PublicKeyTestBytes);
  Sha256Hash hash(&MessageHashTestBytes[0], MessageHashTestBytes.size());

  bool isValid = cryptoVerify(
      publicKey,
      hash,
      SignatureTestBytes);
  ASSERT_TRUE(isValid);
}

/**/

TEST(helpers, crypto_verify_invalid) {
  Ark::Crypto::identities::PublicKey publicKey(InvalidPublicKeyTestBytes);
//   Ark::Crypto::identities::PublicKey publicKey(&InvalidPublicKeyTestBytes[0]);
  Sha256Hash hash(&MessageHashTestBytes[0], MessageHashTestBytes.size());

  bool isValid = cryptoVerify(
      publicKey,
      hash,
      SignatureTestBytes);
  ASSERT_FALSE(isValid);
}
