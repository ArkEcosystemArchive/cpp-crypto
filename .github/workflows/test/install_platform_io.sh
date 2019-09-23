#!/usr/bin/env bash

# install PlatformIO
sudo pip install -U platformio

# update PlatformIO
platformio update

# ensure all git submodules have bee clone
git submodule update --init --recursive
