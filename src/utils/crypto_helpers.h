/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef CRYPTO_HELPERS_H
#define CRYPTO_HELPERS_H

#include <cstring>
#include <numeric>
#include <string>
#include <vector>

const auto ADDRESS_LENGTH = 34U;
const auto COMPRESSED_PUBLICKEY_SIZE = 33U;
const auto PRIVATEKEY_SIZE = 32U;
const auto WIF_SIZE = 52U;

#if defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_SAMD)

#define USE_IOT

#include <Arduino.h>

#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#endif

#endif

#ifndef USE_IOT

#define __STDC_FORMAT_MACROS 1
#include <cinttypes>

#endif

// Write data into dst
template <typename T>
inline void pack(std::vector<uint8_t>& dst, T& data) {
  const auto src = reinterpret_cast<const uint8_t*>(&data);
  dst.insert(dst.end(), src, src + sizeof(T));
}

// Read size bytes into dst from src
template <typename T>
inline void unpack(T* dst, uint8_t* src, size_t size = -1) {
  memcpy(dst, src, size == static_cast<size_t>(-1) ? sizeof(*dst) : size);
}

// Join string vector
inline std::string join(const std::vector<std::string>& strings, size_t offset = 0U) {
  return std::accumulate(
      strings.begin(),
      strings.end(),
      std::string(),
      [&](const std::string& a, const std::string& b)
          -> std::string { return a + b.substr(offset); });
}

#endif
