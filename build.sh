#!/usr/bin/env bash

rm -dfr build
mkdir build
cd build

cmake ..
cmake --build .
