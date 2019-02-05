

# PlatformIO

### dependencies

**Python:**  
Use an installer package from the following link:  
> ```https://www.python.org/downloads/```

#

**PlatformIO:**  
install PlatformIO if not already installed  
> ```pip install -U platformio```  
or  
> ```python -c "$(curl -fsSL > https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"```


also install platformio dependencies:  
> install AUnit (2778), micro-ecc (1665) bip39 (5886) ArduinoJson@5.13.4 libraries  
>```platformio lib -g install 2778 1665 5886 ArduinoJson@5.13.4```

#  

### running the tests on an Arduino board using PlatformIO

**`cd` into this directory "*.../Cpp-Crypto/test*"**  
> ```cd test```

**execute the following command to upload test to your board**  

>| board | command |
>|:-- |:-- |
>| ESP8266 | ```pio run -e esp8266 -t upload``` |
>| ESP32 | ```pio run -e esp32 -t upload``` |

> ^ the above runs the tests rooted in the following file:
> "*.../cpp-crypto/test/IoT/test_main.cpp*"  
