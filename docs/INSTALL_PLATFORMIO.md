

# PlatformIO

### dependencies

**Python:**

Use an installer package from the following link:

> `https://www.python.org/downloads/`

#

**PlatformIO:**

install PlatformIO if not already installed

> `pip install -U platformio`

_or_

> `python -c "$(curl -fsSL > https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"`

#

### running the tests on an Arduino board using PlatformIO

**`cd` into the ".../cpp-crypto/test" directory:**

> `cd test`

**execute the following command to upload and run tests on your board:**  

| board    | command                         |
|:-------- | :------------------------------ |
| ESP8266  | `pio run -e esp8266 -t upload`  |
| ESP32    | `pio run -e esp32 -t upload`    |
