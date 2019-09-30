#!/bin/bash

rm -dfr build
mkdir build
cd build

# Mimic submodule process by copying cpp-crypto src into the expected directory
# git doesn't like nested .gitmodule files
rm -dfr ../lib/cpp-crypto/
mkdir ../lib/cpp-crypto/
cp -R ../../../src ../lib/cpp-crypto/

if [ "$1" == "--BUILD_TESTS" ]; then
  cmake .. -DBUILD_TESTS=ON
else
  cmake ..
fi

cmake --build .
