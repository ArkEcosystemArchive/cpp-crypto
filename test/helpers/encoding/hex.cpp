
#include "gtest/gtest.h"

#include "helpers/encoding/hex.h"

namespace { // NOLINT
  std::vector<uint8_t> SignatureTestBytes = {
     48,  68,   2,  32,  15, 180, 173, 221, 209, 241,
    214,  82, 181,  68, 234, 106, 182,  40,  40, 160,
    166,  91, 113,  46, 212,  71, 226,  83, 141, 176,
    202, 235, 250, 104, 146, 158,   2,  32,  94, 203,
     46,  28,  99, 178, 152, 121, 194, 236, 241,  37,
     93, 181,   6, 214, 113, 200, 179, 250,  96,  23,
    246, 124, 253,  27, 240, 126, 110, 221,  28, 200
  };
  const auto SignatureTestString = "304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8";
  const auto SignatureTestStringSpaces = "30 44 02 20 0f b4 ad dd d1 f1 d6 52 b5 44 ea 6a b6 28 28 a0 a6 5b 71 2e d4 47 e2 53 8d b0 ca eb fa 68 92 9e 02 20 5e cb 2e 1c 63 b2 98 79 c2 ec f1 25 5d b5 06 d6 71 c8 b3 fa 60 17 f6 7c fd 1b f0 7e 6e dd 1c c8";
}

TEST(helpers, hex_bytes_to_hex) {
  const auto result = BytesToHex(&SignatureTestBytes[0], &SignatureTestBytes[0] + SignatureTestBytes.size());
  ASSERT_STREQ(result.c_str(), SignatureTestString);
}

/**/

TEST(helpers, hex_hex_to_bytes) {
  const auto result = HexToBytes(SignatureTestString);
  for (auto i = 0; i < result.size(); ++i) {
    ASSERT_TRUE(result[i] == SignatureTestBytes[i]);
  };
}

/**/

TEST(helpers, hex_hex_to_bytes_spaces) {
  const auto result = HexToBytes(SignatureTestStringSpaces);
  for (auto i = 0; i < result.size(); ++i) {
    ASSERT_TRUE(result[i] == SignatureTestBytes[i]);
  };
}
