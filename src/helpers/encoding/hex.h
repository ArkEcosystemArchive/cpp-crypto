/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef HEX_H
#define HEX_H

#include <string>
#include <vector>

/**
 * Hex Helpers
 **/
template <typename T>
inline std::string BytesToHex(const T itbegin, const T itend, bool fSpaces = false) {
  std::string rv;
  static const char hexmap[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  rv.reserve((itend - itbegin) * 3);
  for (T it = itbegin; it < itend; ++it) {
    const auto val = static_cast<uint8_t>(*it);
    if (fSpaces && it != itbegin) {
      rv.push_back(' ');
    }
    rv.push_back(hexmap[val >> 4]);
    rv.push_back(hexmap[val & 15]);
  }

  return rv;
}

/**/

template <typename T>
inline std::string BytesToHex(const T& vch, bool fSpaces = false) {
  return BytesToHex(vch.begin(), vch.end(), fSpaces);
}

/********/

const int8_t p_util_hexdigit[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  0,   1,   2,   3,
    4,  5,  6,  7,  8,  9,  -1, -1, -1, -1, -1, -1, -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
};

/**/

inline int8_t HexDigit(char c) {
  return p_util_hexdigit[static_cast<uint8_t>(c)];
}

/**/

inline std::vector<uint8_t> HexToBytes(const char* psz) {
  // convert hex dump to vector
  std::vector<uint8_t> vch;
  for (;;) {
    while (isspace(*psz) != 0) {
      psz++;
    }
    auto c = HexDigit(*psz++);
    if (c == static_cast<int8_t>(-1)) {
      break;
    }
    int8_t n = (c << 4);
    c = HexDigit(*psz++);
    if (c == static_cast<int8_t>(-1)) {
      break;
    }
    n |= c;
    vch.push_back(n);
  }
  return vch;
}

/**/

#endif
