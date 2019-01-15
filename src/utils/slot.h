#ifndef ARK_UTILITIES_SLOTS_H
#define ARK_UTILITIES_SLOTS_H

#include "configuration/network.h"

#include <chrono>
#include <cstdint>

namespace Ark {
namespace Crypto {
namespace Utils {

class Slot {
 public:
  static uint64_t epoch_time(Crypto::Networks::AbstractNetwork network) { return epoch_time(now(), network); }
  static uint64_t epoch_time(uint64_t time, Crypto::Networks::AbstractNetwork network);
  static uint64_t begin_epoch_time(Crypto::Networks::AbstractNetwork network);
  static uint64_t time(Crypto::Networks::AbstractNetwork network) { return Slot::time(now(), network); }
  static uint64_t time(uint64_t time, Crypto::Networks::AbstractNetwork network);
  static uint64_t real_time(Crypto::Networks::AbstractNetwork network) {
    return real_time(Slot::time(network), network);
  }
  static uint64_t real_time(uint64_t epoch_time, Crypto::Networks::AbstractNetwork network);

 private:
  static uint64_t now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
  }
};

}  // namespace Utils
}  // namespace Crypto
}  // namespace Ark
#endif
