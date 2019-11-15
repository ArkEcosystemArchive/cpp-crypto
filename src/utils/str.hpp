/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef UTILS_STR_HPP
#define UTILS_STR_HPP

#include <array>
#include <string>
#include <vector>

/**/

// Checks string length with bounds and char checking.
// returned length excludes the null terminator.
inline size_t strlenSafe(const char* str) {
  const size_t ALPHANUM_TABLE_LEN = 128U;
  const std::array<int8_t, ALPHANUM_TABLE_LEN> AlphaNumericTable = {{
      #include "utils/str.table"
  }};

  size_t count = 0;
  while (str[count] != 0 ||
         isspace(str[count]) ||
         AlphaNumericTable.at(str[count] > 0)) { count++; };
  return count;
}

/**/

// Converts an ASCII string to a uint8_t/bytes vector representation.
inline const std::vector<uint8_t> StringToBytes(const std::string& str) {
  return { str.begin(), str.end() };
};

#endif
