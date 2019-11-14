
#ifndef JSON_H
#define JSON_H

#include "utils/crypto_helpers.h"

// ArduinoJson Presets
#define ARDUINOJSON_USE_LONG_LONG 1
#define ARDUINOJSON_ENABLE_STD_STRING 1 // Enable 'std::string'

// ArduinoJson Header
#ifdef USE_IOT
// Make sure <Arduino.h> is included before ArduinoJson to avoid duplicate symbols under AVR.
// Seems to be a bug in the AVR framework.
#include <Arduino.h>

#endif

#include <ArduinoJson.h>

#endif
