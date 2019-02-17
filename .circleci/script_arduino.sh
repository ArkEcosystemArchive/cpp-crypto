#!/usr/bin/env bash

bash ./extras/ARDUINO_IDE.sh --auto

mkdir -p ~/Arduino/libraries/cpp-crypto/
mv ~/project/* ~/Arduino/libraries/cpp-crypto

arduino-cli lib install "ArduinoJson@5.13.4"

arduino-cli compile --output temp.bin -b esp32:esp32:esp32 ~/Arduino/libraries/cpp-crypto/examples/ESP32/ESP32.ino --debug
