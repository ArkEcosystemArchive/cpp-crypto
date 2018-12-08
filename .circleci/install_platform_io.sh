# install PlatformIO
sudo pip install -U platformio

# update PlatformIO
platformio update

# install AUnit (2778) micro-ecc (1665) bip39 (5886) libraries
platformio lib -g install 2778 1665 5886

# ensure all git submodules have bee clone
git submodule update --init --recursive
