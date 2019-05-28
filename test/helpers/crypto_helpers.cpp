
#include "gtest/gtest.h"

#include "enums/types.h"

TEST(helpers, pack) {
}

TEST(helpers, unpack) {
}

TEST(helpers, join) {
}

// // Write data into dst
// template <typename T>
// inline void pack(std::vector<uint8_t>& dst, T& data) {
//   const auto src = reinterpret_cast<const uint8_t*>(&data);
//   dst.insert(dst.end(), src, src + sizeof(T));
// }
// /**/
// // Read size bytes into dst from src
// template <typename T>
// inline void unpack(T* dst, uint8_t* src, size_t size = -1) {
//   memcpy(dst, src, size == -1 ? sizeof(*dst) : size);
// }
// /**/
// // Join string vector
// inline std::string join(const std::vector<std::string>& strings) {
//   return std::accumulate(
//     strings.begin(),
//     strings.end(),
//     std::string(),
//     [](const std::string& a, const std::string& b) -> std::string { return a + b; }
//   );
// }
