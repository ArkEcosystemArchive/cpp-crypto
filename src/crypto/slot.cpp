/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "crypto/slot.hpp"

#include <cstdint>

#include "common/network.hpp"
#include "utils/crypto_helpers.h"

#ifndef USE_IOT // Desktop and Server

  #include <chrono>
  #include <sstream>

  #undef round
  #include "date/date.h"

  namespace Ark {
  namespace Crypto {

  namespace {
  constexpr const uint64_t SECONDS_DIVISOR = 1000ULL;
  }  // namespace

  // Get the Epoch of a given Network.
  uint64_t Slot::epoch(const Network& network) {
    std::istringstream in(network.epoch);
    std::chrono::system_clock::time_point timePoint;
    in >> date::parse("%FT%TZ", timePoint);

  // cast milliseconds as uint64_t in seconds(/1000)
  return std::chrono::duration_cast<std::chrono::milliseconds>(
                timePoint.time_since_epoch())
                .count() / SECONDS_DIVISOR;
  }  // src: https://stackoverflow.com/questions/33421450/c-c-time-zone-correct-time-conversion-to-seconds-since-epoch/33438989#33438989

  // Get the current Network time.
  uint64_t Slot::time(const Ark::Crypto::Network& network) {
    const auto systemTime =
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    return systemTime - epoch(network);
  }

  }  // namespace Crypto
  }  // namespace Ark

#endif

#if defined(ESP32) || defined(ESP8266)

  #include <ctime>
  #include <stdlib.h> /* strtol */
  #include <string>

  namespace Ark {
  namespace Crypto {


  // Get the Epoch of a given Network.
  uint64_t Slot::epoch(const Ark::Crypto::Network& network) {
    const uint8_t TIMESTAMP_LEN = 24U;
    const uint8_t OFFSET_YEAR    = 0U;
    const uint8_t OFFSET_MONTH   = 5U;
    const uint8_t OFFSET_DAY     = 8U;
    const uint8_t OFFSET_HOUR    = 11U;
    const uint8_t OFFSET_MINUTE  = 14U;
    const uint8_t OFFSET_SECOND  = 17U;
    const uint8_t BASE10         = 10U;
    const uint16_t YEAR_1900     = 1900U;

    //  If unexpected ISO 8601 date/time length
    if (network.epoch.length() != TIMESTAMP_LEN) {  
      return 0ULL;
    };

    std::string input(network.epoch);

    struct tm time;
    time.tm_year = strtol(&input[OFFSET_YEAR], nullptr, BASE10) - YEAR_1900;
    time.tm_mon = strtol(&input[OFFSET_MONTH], nullptr, BASE10) - 1;
    time.tm_mday = strtol(&input[OFFSET_DAY], nullptr, BASE10);
    time.tm_hour = strtol(&input[OFFSET_HOUR], nullptr, BASE10);
    time.tm_min = strtol(&input[OFFSET_MINUTE], nullptr, BASE10);
    time.tm_sec = strtol(&input[OFFSET_SECOND], nullptr, BASE10);
    time.tm_isdst = 0;

    return mktime(&time);
  }

  // Get the current Network time.
  uint64_t Slot::time(const Ark::Crypto::Network& network) {
    return std::time(0) - epoch(network);
  }

  }  // namespace Crypto
  }  // namespace Ark

#endif
