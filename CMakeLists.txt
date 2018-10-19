cmake_minimum_required(VERSION 3.2.2)
set(HUNTER_STATUS_DEBUG ON)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake")

include("${CMAKE_SOURCE_DIR}/cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.29.tar.gz"
    SHA1 "797be99a8a4f4666766257563fad8aa3aa032da2"
)

project(Ark-Cpp-Crypto)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${PROJECT_INCLUDE_DIR}/)
include_directories(${PROJECT_INCLUDE_DIR}/bcl)
include_directories(${PROJECT_INCLUDE_DIR}/uECC)
include_directories(${PROJECT_INCLUDE_DIR}/rfc6979)

# clone submodules
execute_process(
	COMMAND git submodule update --init
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

if (MSVC)
	add_definitions(
		-D_CRT_SECURE_NO_WARNINGS
		-D_SCL_SECURE_NO_WARNINGS
		-DNOMINMAX
	)
elseif (UNIX)
	set (CMAKE_CXX_FLAGS "-std=c++11")
endif()

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(test)
