
#include "gtest/gtest.h"

#include "utils/hex.hpp"

#include "fixtures/message.hpp"
using namespace Ark::Crypto;
using namespace fixtures::message;

TEST(helpers, hex_bytes_to_hex) {
  const auto result = BytesToHex(tMessageSignatureBytes.begin(),
                                 tMessageSignatureBytes.end());
  ASSERT_STREQ(result.c_str(), tSignatureString);
}

/**/

TEST(utils, hex_hex_to_bytes) {
  const auto result = HexToBytes(tSignatureString);
  for (auto i = 0U; i < result.size(); ++i) {
    ASSERT_TRUE(result.at(i) == tMessageSignatureBytes.at(i));
  };
}

/**/

TEST(utils, hex_hex_to_bytes_spaces) {
  const auto result = HexToBytes(tSignatureStringSpaces);
  for (auto i = 0U; i < result.size(); ++i) {
    ASSERT_TRUE(result.at(i) == tMessageSignatureBytes.at(i));
  };
}

/**/

TEST(utils, hex_hex_to_bytes_array) {
  const auto result = HexToBytesArray<>(tSignatureString);
  for (auto i = 0U; i < result.size(); ++i) {
    ASSERT_TRUE(result.at(i) == tMessageSignatureBytes[i]);
  };
}

/**/

TEST(utils, hex_hex_to_bytes_array_spaces) {
  const auto result = HexToBytesArray<>(tSignatureStringSpaces);
  for (auto i = 0U; i < result.size(); ++i) {
    ASSERT_TRUE(result.at(i) == tMessageSignatureBytes.at(i));
  };
}

/**/

TEST(utils, hex_hex_to_bytes_array_null_input) {
  const auto result = HexToBytesArray<>(nullptr);
  for (unsigned char i : result) {
    ASSERT_EQ(result.at(i), 0);
  };
}
