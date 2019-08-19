# run desktop builds
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage
cmake --build .

# # run Gtest
./test/Ark-Cpp-Crypto-tests
