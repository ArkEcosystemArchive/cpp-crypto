cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-tests C CXX)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake/)
include(GetGTest)

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/../src/lib)
include_directories(${PROJECT_SOURCE_DIR}/../extern/ArduinoJson)

set (TEST_SRC
    ${PROJECT_SOURCE_DIR}/common/configuration.cpp
    ${PROJECT_SOURCE_DIR}/common/fee_policy.cpp
    ${PROJECT_SOURCE_DIR}/common/network.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve.cpp
    ${PROJECT_SOURCE_DIR}/crypto/hash.cpp
    ${PROJECT_SOURCE_DIR}/defaults/static_fees.cpp
    ${PROJECT_SOURCE_DIR}/defaults/transaction_types.cpp
    ${PROJECT_SOURCE_DIR}/helpers/crypto_helpers.cpp
    ${PROJECT_SOURCE_DIR}/identities/address.cpp
    ${PROJECT_SOURCE_DIR}/identities/keys.cpp
    ${PROJECT_SOURCE_DIR}/identities/privatekey.cpp
    ${PROJECT_SOURCE_DIR}/identities/publickey.cpp
    ${PROJECT_SOURCE_DIR}/identities/wif.cpp
    ${PROJECT_SOURCE_DIR}/managers/fee_manager.cpp
    ${PROJECT_SOURCE_DIR}/managers/network_manager.cpp
    ${PROJECT_SOURCE_DIR}/networks/devnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/mainnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/testnet.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builder.cpp
    ${PROJECT_SOURCE_DIR}/transactions/deserializer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/serializer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/transaction.cpp
    ${PROJECT_SOURCE_DIR}/utils/base58.cpp
    ${PROJECT_SOURCE_DIR}/utils/hex.cpp
    ${PROJECT_SOURCE_DIR}/utils/message.cpp
    ${PROJECT_SOURCE_DIR}/utils/slot.cpp
    ${PROJECT_SOURCE_DIR}/utils/str.cpp
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
