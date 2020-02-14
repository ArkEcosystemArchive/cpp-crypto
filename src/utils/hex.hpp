/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_HEX_HPP
#define ARK_UTILS_HEX_HPP

#include <array>
#include <string>
#include <vector>

#include "interfaces/constants.h"

////////////////////////////////////////////////////////////////////////////////
// Bytes to Hex
template <typename T>
inline std::string BytesToHex(const T itbegin, const T itend) {
    const char hexmap[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f'
    };

    std::string rv;
    rv.reserve((itend - itbegin) * 3);

    for (T it = itbegin; it < itend; ++it) {
        const auto val = static_cast<uint8_t>(*it);
        rv.push_back(hexmap[val >> 4]);
        rv.push_back(hexmap[val & 15]);
    }

    return rv;
}

////////////////////////////////////////////////////////////////////////////////
// Bytes to Hex
template <typename T> inline std::string BytesToHex(const T& vch) {
    return BytesToHex(vch.begin(), vch.end());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
constexpr size_t HEX_TABLE_LEN = 256U;

////////////////////////////////////////////////////////////////////////////////
constexpr std::array<int8_t, HEX_TABLE_LEN> HexTable = {{
    #include "utils/hex.table"
}};

////////////////////////////////////////////////////////////////////////////////
inline int8_t HexDigit(char c) {
  return HexTable[static_cast<int8_t>(c)];
}

////////////////////////////////////////////////////////////////////////////////
inline std::vector<uint8_t> HexToBytes(const char* psz) {
    // convert hex dump to vector
    std::vector<uint8_t> vch;

    for (;;) {
        while (isspace(*psz) != 0) { psz++; };

        auto a = HexDigit(*psz++);
        if (a < 0) { break; }

        auto b = HexDigit(*psz++);
        if (b < 0) { break; }

        vch.push_back(b |= a << 4);
    }

    return vch;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Hex string to Byte Array.
// Same as HexToBytes, but using std::array.
// This is a bit lighter and faster than using the vector method.
//
// Default size is 32-bytes.
// The template 'SIZE' should be 1/2x the Hex length.
// e.g. A 66-character Hex string represents 33-bytes
//
// Examples:
// auto privateKeyFromHex = HexToBytesArray<>(my_privatekey_hex_string);
// auto publicKeyFromHex = HexToBytesArray<33>(my_publickey_hex_string);
template<size_t SIZE = HASH_32_LEN>
inline std::array<uint8_t, SIZE> HexToBytesArray(const char *psz) {
    if (psz == nullptr) { return std::array<uint8_t, SIZE>(); };

    std::array<uint8_t, SIZE> arr {};
    for (auto &e : arr) {
        while (isspace(*psz) != 0) { psz++; };

        auto a = HexDigit(*psz++);
        if (a < 0) { return {}; }

        auto b = HexDigit(*psz++);
        if (b < 0) { return {}; }

        e = b |= a << 4;
    }

    return arr;
}

#endif
