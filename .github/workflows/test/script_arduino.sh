#!/usr/bin/env bash

bash ./extras/ARDUINO_IDE.sh --auto

mkdir -p ~/Arduino/libraries/cpp-crypto/
mv ${GITHUB_WORKSPACE}/* ~/Arduino/libraries/cpp-crypto/

arduino-cli lib install "ArduinoJson@6.12.0"
arduino-cli lib install "BIP66@0.2.0"
arduino-cli lib install "micro-ecc@1.0.0"
arduino-cli lib install "avr_stl@1.2.2"

#arduino-cli compile --output temp.bin -b esp32:esp32:esp32 ~/Arduino/libraries/cpp-crypto/examples/arduino/ESP32/ESP32.ino --debug

#arduino-cli compile --output temp.bin -b esp8266:esp8266:nodemcu ~/Arduino/libraries/cpp-crypto/examples/arduino/ESP8266/ESP8266.ino --debug

arduino-cli compile --output temp.bin -v -b arduino:avr:uno --build-properties build.extra_flags=-D__avr_libc_does_not_implement_long_long_in_printf_or_scanf ~/Arduino/libraries/cpp-crypto/examples/arduino/ATMEGA328P/ATMEGA328P.ino --debug
