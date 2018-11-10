

#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <cstring>
#include <numeric>
#include <vector>

const auto ADDRESS_LENGTH = 34u;
const auto COMPRESSED_PUBLICKEY_SIZE = 33u;
const auto PRIVATEKEY_SIZE = 32u;
const auto WIF_SIZE = 52u;


#if (defined ARDUINO || defined ESP8266 || defined ESP32)

#define USE_IOT

// Including missing implementations of std::to_string
#include "stl/details/to_string.h"

#include <Arduino.h>
#include <pgmspace.h>

// undef the C macros to allow the C++ STL to take over
// This is to have compatibility with various board implementations of the STL
#undef min
#undef max

inline uint32_t generate_random_number(uint32_t min, uint32_t max, bool /* static_seed */ = false) {
  return random(min, max);
}

#else

#define PROGMEM
#define PGM_P const char*

#define pgm_read_ptr_far(p) (*p)
#define strcpy_P strcpy

uint32_t generate_random_number(uint32_t min, uint32_t max, bool static_seed = false);

#endif



// Write data into dst
template <typename T>
inline void pack (std::vector<uint8_t>& dst, T& data) {
    const uint8_t * src = reinterpret_cast<const uint8_t* >(&data);
    dst.insert(dst.end(), src, src + sizeof (T));
}

// Read size bytes into dst from src
template <typename T>
inline void unpack (T* dst, uint8_t* src, size_t size = -1) {
    memcpy(dst, src, size == -1 ? sizeof(*dst) : size);
}


// Join string vector
inline std::string join(const std::vector<std::string>& strings) {
    return std::accumulate(strings.begin(), strings.end(), std::string(),
        [](const std::string& a, const std::string& b) -> std::string {
            return a + b;
        }
    );
}

#endif
