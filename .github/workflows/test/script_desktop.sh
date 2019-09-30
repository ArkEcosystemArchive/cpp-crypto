#!/usr/bin/env bash

# run desktop builds
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage
cmake --build .

# build examples
cd ../examples/cmake_example
chmod +x ./build.sh
./build.sh

# # run Gtest
cd ../../build
./test/ark_cpp_crypto_tests
