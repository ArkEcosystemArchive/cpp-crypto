/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_PLATFORM_H
#define ARK_UTILS_PLATFORM_H

////////////////////////////////////////////////////////////////////////////////

#if (defined ARDUINO || defined ESP8266 || defined ESP32)

#define USE_IOT

#include <Arduino.h>
#include <pgmspace.h>

#endif  // (defined ARDUINO || defined ESP8266 || defined ESP32)

////////////////////////////////////////////////////////////////////////////////

#ifndef USE_IOT

#define __STDC_FORMAT_MACROS 1
#include <cinttypes>

#endif  // ifndef USE_IOT

////////////////////////////////////////////////////////////////////////////////

#endif
