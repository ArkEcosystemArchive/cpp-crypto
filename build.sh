#!/bin/bash

rm -dfr build

mkdir build

cd build

if [ "$1" == "--BUILD_TESTS" ]; then
  cmake .. -DBUILD_TESTS=ON
else
  cmake ..
fi

cmake --build .
