#!/usr/bin/env bash

bash ./extras/ARDUINO_IDE.sh --auto

mkdir -p ~/Arduino/libraries/cpp-crypto/
mv ~/work/cpp-crypto/cpp-crypto/* ~/Arduino/libraries/cpp-crypto

arduino-cli lib install "ArduinoJson@6.10.0"
arduino-cli lib install "BIP66"
arduino-cli lib install "micro-ecc"

arduino-cli compile --output temp.bin -b esp32:esp32:esp32 ~/Arduino/libraries/cpp-crypto/examples/arduino/ESP32/ESP32.ino --debug
