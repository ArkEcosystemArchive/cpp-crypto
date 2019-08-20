
#include "gtest/gtest.h"

#include "utils/crypto_helpers.h"

#include <cstdint>
#include <vector>

TEST(utils, pack_unpack) {
  std::vector<uint8_t> packBuffer;
  uint8_t packValue = 23;
  pack(packBuffer, packValue);

  uint8_t unpackValue;
  unpack(&unpackValue, &packBuffer[0]);
  ASSERT_EQ(packValue, unpackValue);
}

/**/

TEST(utils, join) {
  const auto strBuffer = "123";
  std::vector<std::string> vstr(3);
  vstr[0] = strBuffer[0];
  vstr[1] = strBuffer[1];
  vstr[2]= strBuffer[2];

  std::string joined = join(vstr);
  ASSERT_STREQ(joined.c_str(), strBuffer);
}
