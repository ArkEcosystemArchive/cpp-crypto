
# OS Builds

## Linux, macOS and Windows

**CMake:**

Use an installer package from the following link, Homebrew, or use your preferred method:

* `https://www.cmake.org/download/`

using **Homebrew:**

* `brew install cmake`

> note: all other dependencies will be automatically installed via CMake.

### make and build

* `cd cpp-crypto`
* `mkdir build && cd build`
* `cmake -DUNIT_TEST=ON ..`
* `cmake --build .`

### run tests (Linux, macOS)

* `./test/ark_cpp_crypto_tests`

### run tests (Windows)

* `.\test\Debug\ark_cpp_crypto_tests.exe`