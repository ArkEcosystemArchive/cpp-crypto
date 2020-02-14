/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_CRYPTO_HELPERS_H
#define ARK_UTILS_CRYPTO_HELPERS_H

#include <cstring>
#include <numeric>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Write data into dst
template <typename T>
inline void pack(std::vector<uint8_t> &dst, T &data) {
    const auto src = reinterpret_cast<const uint8_t *>(&data);
    dst.insert(dst.end(), src, src + sizeof(T));
}

////////////////////////////////////////////////////////////////////////////////
// Read size bytes into dst from src
template <typename T>
inline void unpack(T *dst, uint8_t *src, size_t size = -1) {
    memcpy(dst, src, size == -1 ? sizeof(*dst) : size);
}

////////////////////////////////////////////////////////////////////////////////
// Join string vector
inline auto join(const std::vector<std::string> &strings) -> std::string {
    return std::accumulate(strings.begin(),
                           strings.end(),
                           std::string(),
                           [](const std::string &a, const std::string &b)
                                    -> std::string { return a + b; });
}

#endif
