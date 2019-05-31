
#include "helpers/crypto_helpers.h"
#include "utils/slot.h"

#ifndef USE_IOT // OS Builds

  #include <chrono>
  #include <sstream>

  #undef round
  #include "date/date.h"

  uint64_t Ark::Crypto::Utils::Slot::epoch(const Crypto::Networks::AbstractNetwork& network) {
    // https://stackoverflow.com/questions/33421450/c-c-time-zone-correct-time-conversion-to-seconds-since-epoch/33438989#33438989
    std::istringstream in(network.epoch());
    std::chrono::system_clock::time_point tp;
    in >> date::parse("%FT%TZ", tp);

    // cast milliseconds as uint64_t in seconds(/ 1000)
    return static_cast<uint64_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(
        tp.time_since_epoch()
      ).count()
    ) / 1000;
  }

  uint64_t Ark::Crypto::Utils::Slot::now() {
    return std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  }

#endif

uint64_t Ark::Crypto::Utils::Slot::time(const Crypto::Networks::AbstractNetwork& network) {
  const auto time = now() - epoch(network);
  return (time > 0) ? time : 0;
}

#if defined(ESP32) || defined(ESP8266)

  #include <time.h>
  #include <stdlib.h> /* strtol */
  #include <string>

  uint64_t Ark::Crypto::Utils::Slot::epoch(const Crypto::Networks::AbstractNetwork& network) {
    constexpr const size_t expectedLength = sizeof("2017-03-21T13:00:00.000Z") - 1;
    if (expectedLength != 24) { return 0; } //  Unexpected ISO 8601 date/time length

    std::string input(network.epoch());

    if (input.length() < expectedLength) {
      return 0;
    };

    struct tm time;
    time.tm_year = strtol(&input[0], nullptr, 10) - 1900;
    time.tm_mon = strtol(&input[5], nullptr, 10) - 1;
    time.tm_mday = strtol(&input[8], nullptr, 10);
    time.tm_hour = strtol(&input[11], nullptr, 10);
    time.tm_min = strtol(&input[14], nullptr, 10);
    time.tm_sec = strtol(&input[17], nullptr, 10);
    time.tm_isdst = 0;

    return mktime(&time);
  }

  /***/

  // 'time(0) will collide with Slot::time
  // so we create the call outside the Slot namespace.
  static uint64_t Now() { return time(0); }

  uint64_t Ark::Crypto::Utils::Slot::now() {
    return Now();
  }

#endif
