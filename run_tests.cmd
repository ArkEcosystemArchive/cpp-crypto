
rmdir /S /Q build
mkdir build
cd build

cmake -DUNIT_TEST=ON ..
cmake --build .

cd ..

.\build\test\Debug\ark_cpp_crypto_tests
