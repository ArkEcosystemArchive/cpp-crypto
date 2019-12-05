
# Desktop/Server

Linux, macOS and Windows.

## Requirements

**CMake:**

Installing Cmake:

* Linux:
  * `sudo apt-get -y install cmake`
* macOS:
  * `brew install cmake`
* Windows Installer Pkg:
  * `https://www.cmake.org/download/`

## Dependencies

The following external libraries are cloned during the build process:

* [`ArduinoJson@6.12.0`](https://github.com/bblanchon/ArduinoJson)
* [`BIP66@0.3.2`](https://github.com/sleepdefic1t/BIP66)
* [`micro-ecc@1.0.0`](https://github.com/kmackay/micro-ecc)

## Building

### make and build

* `cd cpp-crypto`
* `mkdir build && cd build`
* `cmake -DUNIT_TEST=ON ..`
* `cmake --build .`

### run tests (Linux, macOS)

* `./test/ark_cpp_crypto_tests`

### run tests (Windows)

* `.\test\Debug\ark_cpp_crypto_tests.exe`
