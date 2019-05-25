cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-tests C CXX)

set(BUILD_GMOCK OFF FORCE)

add_subdirectory(lib/googletest)

include(CTest)
enable_testing()

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/../src/lib)
include_directories(${PROJECT_SOURCE_DIR}/../src/lib/ArduinoJson)
include_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set (TEST_SRC
	${PROJECT_SOURCE_DIR}/configuration/fee.cpp
	${PROJECT_SOURCE_DIR}/configuration/network.cpp
	${PROJECT_SOURCE_DIR}/enums/fees.cpp
	${PROJECT_SOURCE_DIR}/enums/types.cpp
	${PROJECT_SOURCE_DIR}/identities/address.cpp
	${PROJECT_SOURCE_DIR}/identities/privatekey.cpp
	${PROJECT_SOURCE_DIR}/identities/publickey.cpp
	${PROJECT_SOURCE_DIR}/identities/wif.cpp
	${PROJECT_SOURCE_DIR}/networks/abstractnetwork.cpp
	${PROJECT_SOURCE_DIR}/networks/devnet.cpp
	${PROJECT_SOURCE_DIR}/networks/mainnet.cpp
	${PROJECT_SOURCE_DIR}/networks/testnet.cpp
  ${PROJECT_SOURCE_DIR}/transactions/builder.cpp
  ${PROJECT_SOURCE_DIR}/transactions/deserializer.cpp
	${PROJECT_SOURCE_DIR}/transactions/serializer.cpp
	${PROJECT_SOURCE_DIR}/transactions/transaction.cpp
  ${PROJECT_SOURCE_DIR}/utils/message.cpp
	${PROJECT_SOURCE_DIR}/utils/slot.cpp
)

find_library(Ark-Cpp-Crypto-tests PUBLIC)

add_executable(Ark-Cpp-Crypto-tests ${TEST_SRC})

target_link_libraries(Ark-Cpp-Crypto-tests Ark-Cpp-Crypto-lib gtest gtest_main)

add_test(NAME test COMMAND Ark-Cpp-Crypto-tests)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include("${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake")

    setup_target_for_coverage(${PROJECT_NAME}_coverage Ark-Cpp-Crypto-tests coverage)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
  endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
