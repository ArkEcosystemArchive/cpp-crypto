# run PlatformIO builds
platformio run
cd test
platformio run -e esp8266_tests
platformio run -e esp32_tests
