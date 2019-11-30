
# PlatformIO IDE

## Python

Use an installer package from the following link or use your preferred method to install Python:

* `https://www.python.org/downloads/`

Install PlatformIO:

* `pip install -U platformio`

or

* `python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"`

## Dependencies

Install `ArduinoJson@6.12.0`, `BIP66@0.2.1`, and `micro-ecc@1.0.0`.

* `platformio lib -g ArduinoJson@6.12.0 BIP66@0.2.1 micro-ecc@1.0.0`

## Build and Run Live Tests on the ESP32

>| board | command                                      |
>| :---- | :------                                      |
>| ESP32 | `pio run -e esp32_tests -d test/ -t upload`  |
