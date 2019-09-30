rmdir /S /Q build
mkdir build
cd build

REM Mimic submodule process by copying cpp-crypto src into the expected directory
REM git doesn't like nested .gitmodule files
rmdir /S /Q ..\lib\cpp-crypto\
mkdir ..\lib\cpp-crypto\
xcopy /E /Y /H /R ..\..\..\src ..\lib\cpp-crypto\
mkdir ..\lib\extern\
xcopy /E /Y /H /R ..\..\..\extern ..\lib\extern\

IF "%var%"=="BUILD_TESTS" (
  cmake .. -DBUILD_TESTS=ON
) ELSE (
  cmake ..
)
cmake --build .
