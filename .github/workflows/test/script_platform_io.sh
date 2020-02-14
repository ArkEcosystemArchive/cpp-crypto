#!/usr/bin/env bash

# run PlatformIO builds
platformio run

# platformio run -e esp8266_tests -d test
platformio run -e esp32_tests -d test
