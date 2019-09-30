
# OS Builds

## Dependencies

**CMake:**

Use an installer package:

> `https://www.cmake.org/download/`

Homebrew:

> `brew install cmake`

_note: all other library dependencies will be automatically installed via CMake and Git submodule._

## Make and Build

### Linux/macOS

> `./build.sh`

### Windows

> `./build.cmd`

### CMake (manually)

1) `mkdir build && cd build`
2) `cmake ..`
3) `./tests/ark_cpp_crypto_tests`

## Build and Run Tests

### Linux/macOS

> `./run_tests.sh`

### Windows

> `./run_tests.cmd`

### CMake (manually)

1) `mkdir build && cd build`
2) `cmake ..`
3) `./tests/ark_cpp_crypto_tests`
