
# PlatformIO IDE

## Requirements

### Python

* Linux:
  * `sudo apt-get install python`
* macOS:
  * `brew install python`
* Windows Installer Pkg:
  * `https://www.python.org/downloads/windows/`

### PlatformIO

* Linux/macOS/Windows using PIP:
  * `pip install -U platformio`
* Linux/macOS/Windows using cURL:
  * `python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"`

## Dependencies

The following external libraries are fetched during the build process:

* [`ArduinoJson@6.12.0`](https://github.com/bblanchon/ArduinoJson)
* [`BIP66@0.2.1`](https://github.com/sleepdefic1t/BIP66)
* [`micro-ecc@1.0.0`](https://github.com/kmackay/micro-ecc)

## Build and Run Live Tests on the ESP32

> | board | command                                      |
> | :---- | :------                                      |
> | ESP32 | `pio run -e esp32_tests -d test/ -t upload`  |
