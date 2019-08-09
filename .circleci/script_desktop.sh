# run desktop builds
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage
cmake --build .

# build examples
cd ../examples/cmake_example
mkdir build
cd build
cmake .
cmake --build .

# run Gtest
cd ../../../build
./test/Ark-Cpp-Crypto-tests
