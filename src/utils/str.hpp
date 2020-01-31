/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_STR_HPP
#define ARK_UTILS_STR_HPP

#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "interfaces/constants.h"

////////////////////////////////////////////////////////////////////////////////
constexpr size_t ALPHANUM_TABLE_LEN = 128U;

////////////////////////////////////////////////////////////////////////////////
constexpr std::array<int8_t, ALPHANUM_TABLE_LEN> AlphaNumericTable = {{
    #include "utils/str.table"
}};

////////////////////////////////////////////////////////////////////////////////
// Checks string length with bounds and char checking.
// returned length excludes the null terminator.
inline size_t strlenSafe(const char* str) {
    size_t count = 0;
    while (str[count] != 0 ||
           isspace(static_cast<int>(str[count])) != 0 ||
           AlphaNumericTable.at(str[count]) > 0) {
        count++;
    };

    return count;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Converts an ASCII string to a uint8_t/bytes vector representation.
inline const std::vector<uint8_t> StringToBytes(const std::string& str) {
    return { str.begin(), str.end() };
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Convert an Unsigned Integer to its string representation.
inline const std::string UintToString(uint64_t amount) {
    if (amount == 0ULL) {
        return "0";
    }

    const uint8_t STRING_SIZE   = 20U;
    const char *STRING_TABLE    = "0123456789";

    std::string result;
    result.reserve(STRING_SIZE);

    uint64_t q = amount;

    while (q != 0U) {
        result += STRING_TABLE[q % BASE_10];
        q /= BASE_10;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

#endif
