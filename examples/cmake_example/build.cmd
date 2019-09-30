rmdir /S /Q build
mkdir build
cd build

REM Mimic submodule process by copying cpp-crypto src into the expected directory
REM git doesn't like nested .gitmodule files
rmdir /S /Q ..\lib\cpp-crypto\
mkdir ..\lib\cpp-crypto\
xcopy /E /Y /H /R ..\..\..\src ..\lib\
mkdir ..\extern\
xcopy /E /Y /H /R ..\..\..\extern ..\extern\

cmake --build .
