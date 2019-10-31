#ifndef CRYPTO_TEST_IOT_PLATFORM_HPP
#define CRYPTO_TEST_IOT_PLATFORM_HPP

#ifdef ESP8266

#include "ESP8266WiFi.h"

#endif

void optimize_for_testing() {

#ifdef ESP8266
  WiFi.forceSleepBegin(); // turn off WiFi to save power and processing time
  delay(1);               // give WiFi time to power down
#endif

}

#endif
