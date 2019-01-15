#include "helpers/helpers.h"  // include helpers first to pick up patched STL std::to_string functions for IoT

#include "utils/slot.h"

#undef round
#include "date/date.h"

#include <cmath>
#include <sstream>

namespace Ark {
namespace Crypto {
namespace Utils {

uint64_t Slot::epoch_time(uint64_t time, Crypto::Networks::AbstractNetwork network) {
  const auto start = Slot::begin_epoch_time(network);
  return static_cast<uint64_t>(std::floor((time - start) / 1000));
}

uint64_t Slot::begin_epoch_time(Crypto::Networks::AbstractNetwork network) {
  // https://stackoverflow.com/questions/33421450/c-c-time-zone-correct-time-conversion-to-seconds-since-epoch/33438989#33438989
  std::istringstream in(network.epoch());
  date::sys_seconds tp;
  in >> date::parse("%FT%TZ", tp);
  if (in.fail()) {
    in.clear();
    in.str(network.epoch());
    in >> date::parse("%FT%T%z", tp);
  }
  return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count());
}

uint64_t Slot::time(uint64_t time, Crypto::Networks::AbstractNetwork network) {
  return Slot::epoch_time(time, network);
}

uint64_t Slot::real_time(uint64_t epoch_time, Crypto::Networks::AbstractNetwork network) {
  const auto start = std::floor(Slot::begin_epoch_time(network) / 1000) * 1000;
  return static_cast<uint64_t>(start + epoch_time * 1000.0);
}

}  // namespace Utils
}  // namespace Crypto
}  // namespace Ark
