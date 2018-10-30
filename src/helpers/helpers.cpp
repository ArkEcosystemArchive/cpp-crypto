#include "helpers/helpers.h"

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
