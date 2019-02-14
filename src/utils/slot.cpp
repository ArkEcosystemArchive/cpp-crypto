
#include "helpers/crypto_helpers.h"
#include "utils/slot.h"

#include <chrono>
#include <sstream>

#undef round
#include "lib/date/date.h"

uint64_t Ark::Crypto::Utils::Slot::epoch(Crypto::Networks::AbstractNetwork network) {
  // https://stackoverflow.com/questions/33421450/c-c-time-zone-correct-time-conversion-to-seconds-since-epoch/33438989#33438989
  std::istringstream in(network.epoch());
  std::chrono::system_clock::time_point tp;
  in >> date::parse("%FT%TZ", tp);
  if (in.fail()) {    
    in.clear();
    in.str(network.epoch());
    in >> date::parse("%FT%T%z", tp);
  };
  // cast milliseconds as uint64_t in seconds(/ 1000)
  return static_cast<uint64_t>(
    std::chrono::duration_cast<std::chrono::milliseconds>(
      tp.time_since_epoch()
    ).count()
  ) / 1000;
}

uint64_t Ark::Crypto::Utils::Slot::time(Crypto::Networks::AbstractNetwork network) {
  const auto time = now() - epoch(network);
  return (time > 0) ? time : 0;
}

#ifdef ESP32

uint64_t Ark::Crypto::Utils::Slot::now() {
  struct tm t;
  std::stringstream ss;
  if(getLocalTime(&t)){
    ss << std::mktime(&t);
  } else {
    return 0;
  };
  uint64_t temp;
  ss >> temp;
  return temp;
};

#elif defined(ESP8266)  //  NOT STABLE/NOT SUPPORTED

uint64_t Ark::Crypto::Utils::Slot::now() { return 0; }

#else // OS Builds

uint64_t Ark::Crypto::Utils::Slot::now() {
  return std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count();
}

#endif  // #ifndef USE_IOT
