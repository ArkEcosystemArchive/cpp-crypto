
cmake_minimum_required(VERSION 3.2)

project(${PROJECT_NAME}_tests C CXX)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

# ------------------------------------------------------------------------------
# External Libraries
# ------------------------------------------------------------------------------

include(${CMAKE_SOURCE_DIR}/cmake/GTest.cmake)

include_directories(${ARDUINO_JSON_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Link the directories to be included
# ------------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# ARK C++ Crypto Test Source
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Common

set(COMMON_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/common/configuration.cpp
    ${PROJECT_SOURCE_DIR}/common/fee_policy.cpp
    ${PROJECT_SOURCE_DIR}/common/network.cpp)

# ------------------------------------------------------------------------------
# Crypto

set(CRYPTO_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/crypto/curve.cpp
    ${PROJECT_SOURCE_DIR}/crypto/hash.cpp
    ${PROJECT_SOURCE_DIR}/crypto/message.cpp
    ${PROJECT_SOURCE_DIR}/crypto/slot.cpp)

# ------------------------------------------------------------------------------
# Defaults

set(DEFAULTS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/defaults/static_fees.cpp
    ${PROJECT_SOURCE_DIR}/defaults/transaction_types.cpp)

# ------------------------------------------------------------------------------
# Identities

set(IDENTITIES_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/identities/address.cpp
    ${PROJECT_SOURCE_DIR}/identities/keys.cpp
    ${PROJECT_SOURCE_DIR}/identities/privatekey.cpp
    ${PROJECT_SOURCE_DIR}/identities/publickey.cpp
    ${PROJECT_SOURCE_DIR}/identities/wif.cpp)

# ------------------------------------------------------------------------------
# Managers

set(MANAGERS_SOURCE
    ${PROJECT_SOURCE_DIR}/managers/fee_manager.cpp
    ${PROJECT_SOURCE_DIR}/managers/network_manager.cpp)

# ------------------------------------------------------------------------------
# Networks

set(NETWORKS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/networks/devnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/mainnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/testnet.cpp)

# ------------------------------------------------------------------------------
# Transactions

set(TRANSACTIONS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/transactions/builder.cpp
    ${PROJECT_SOURCE_DIR}/transactions/deserializer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/serializer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/transaction.cpp)

# ------------------------------------------------------------------------------
# Utils

set(UTILS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/utils/base58.cpp
    ${PROJECT_SOURCE_DIR}/utils/crypto_helpers.cpp
    ${PROJECT_SOURCE_DIR}/utils/hex.cpp
    ${PROJECT_SOURCE_DIR}/utils/str.cpp)

# ------------------------------------------------------------------------------
# ARK C++ Library Source

set(ARK_TEST_SOURCE
    ${COMMON_TEST_SOURCE}
    ${CRYPTO_TEST_SOURCE}
    ${DEFAULTS_TEST_SOURCE}
    ${IDENTITIES_TEST_SOURCE}
    ${MANAGERS_TEST_SOURCE}
    ${NETWORKS_TEST_SOURCE}
    ${TRANSACTIONS_TEST_SOURCE}
    ${UTILS_TEST_SOURCE})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Link ARK C++ Crypto to the Test Libraries
# ------------------------------------------------------------------------------

find_library(${PROJECT_NAME} PUBLIC)

add_executable(${PROJECT_NAME} ${ARK_TEST_SOURCE})

target_link_libraries(${PROJECT_NAME} ark_cpp_crypto gtest gtest_main)

add_test(NAME test COMMAND ${PROJECT_NAME})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Coverage 2:2
# ------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include("${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake")

    setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_NAME}_tests coverage)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

# ------------------------------------------------------------------------------
