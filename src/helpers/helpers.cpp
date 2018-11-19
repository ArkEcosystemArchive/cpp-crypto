#include "helpers/helpers.h"

#if !defined USE_IOT

#include <random>

namespace {

  uint32_t generate_random_number_with_fresh_seed(uint32_t min, uint32_t max) {
    std::default_random_engine generator;
    std::uniform_int_distribution<uint32_t> distribution(min, max);
    return distribution(generator);
  }

  uint32_t generate_random_number_with_static_seed(uint32_t min, uint32_t max) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<uint32_t> distribution(min, max);
    return distribution(generator);
  }

}

uint32_t generate_random_number(uint32_t min, uint32_t max, bool static_seed /* = false */) {
  return static_seed ? generate_random_number_with_static_seed(min, max) : generate_random_number_with_fresh_seed(min, max);
}

#endif

#if (defined ESP8266)

// Add missing functions from abs.cpp.  PlatformIO is not up to the latest on github
// https://github.com/esp8266/Arduino/issues/3358
namespace std {

void __throw_bad_cast(void)
{
  panic();
}

void __throw_ios_failure(const char* str)
{
  (void)str;
  panic();
}

void __throw_runtime_error(const char* str)
{
  (void)str;
  panic();
}

}

#endif

#if (defined PLATFORMIO && !defined UNIT_TEST)

void setup() {}
void loop() { delay(1000); }

#endif
