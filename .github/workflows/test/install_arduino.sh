#!/usr/bin/env bash

sudo apt-get install bzip2
yes | sudo apt install python-pip
pip install pyserial
pip install --upgrade pip

wget -O arduino-cli-linux64.tar.bz2 https://github.com/arduino/arduino-cli/releases/download/0.3.3-alpha.preview/arduino-cli-0.3.3-alpha.preview-linux64.tar.bz2
bunzip2 arduino-cli-linux64.tar.bz2
tar xvf arduino-cli-linux64.tar

sudo mv arduino-cli-0.3.3-alpha.preview-linux64 /usr/local/share/arduino-cli
sudo ln -s /usr/local/share/arduino-cli /usr/local/bin/arduino-cli

printf "board_manager:
  additional_urls:
    - https://dl.espressif.com/dl/package_esp32_index.json
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json
    - https://adafruit.github.io/arduino-board-index/package_adafruit_index.json" >> .cli-config.yml
sudo mv .cli-config.yml /usr/local/share/

arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli core install esp8266:esp8266
arduino-cli core install arduino:samd
arduino-cli core install adafruit:samd
