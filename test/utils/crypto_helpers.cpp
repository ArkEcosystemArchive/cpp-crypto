
#include "gtest/gtest.h"

#include "utils/crypto_helpers.h"

#include <cstdint>
#include <vector>

TEST(utils, pack_unpack) {
  std::vector<uint8_t> packBuffer;
  const uint8_t packValue = 23U;
  pack(packBuffer, packValue);

  uint8_t unpackValue;
  unpack(&unpackValue, &packBuffer[0]);
  ASSERT_EQ(packValue, unpackValue);
}

/**/

TEST(utils, join) {
  const std::string strBuffer = "123";
  const std::string strBuffer2 = "456";
  std::vector<std::string> vstr { strBuffer, strBuffer2 };

  std::string joined = join(vstr);

  ASSERT_STREQ(joined.c_str(), std::string(strBuffer + strBuffer2).c_str());
}

/**/

TEST(utils, join_offset) {
  const std::string strBuffer = "654";
  const std::string strBuffer2 = "321";
  std::vector<std::string> vstr { strBuffer, strBuffer2 };

  std::string joined = join(vstr, 1);

  ASSERT_STREQ(joined.c_str(),
               std::string(strBuffer.substr(1) +
                           strBuffer2.substr(1)).c_str());
}