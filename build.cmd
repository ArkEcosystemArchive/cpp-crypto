rmdir /S /Q build

mkdir build

cd build

IF "%var%"=="BUILD_TESTS" (
  cmake .. -DBUILD_TESTS=ON
) ELSE (
  cmake ..
)

cmake --build .

cd ..
