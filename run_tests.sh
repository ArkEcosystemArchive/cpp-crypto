#!/bin/bash

./build.sh --BUILD_TESTS

chmod +x ./build/test/ark_cpp_crypto_tests
./build/test/ark_cpp_crypto_tests
