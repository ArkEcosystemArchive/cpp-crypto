# run desktop builds
cmake . -DCMAKE_BUILD_TYPE=Coverage
cmake --build .

# build examples
cd ./extras/cmake_example
cmake .
cmake --build .

# run Gtest
./test/Ark-Cpp-Crypto-tests
