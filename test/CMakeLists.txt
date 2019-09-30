
cmake_minimum_required(VERSION 3.2.2)

project(ARK_CPP_CRYPTO_TESTS C CXX)

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------

option(BUILD_GMOCK OFF FORCE)
option(PACKAGE_TESTS OFF FORCE)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if (APPLE OR CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_subdirectory(../extern/googletest/googletest [EXCLUDE_FROM_ALL])
    include(GoogleTest)
else()
    add_subdirectory(../extern/googletest [EXCLUDE_FROM_ALL])
endif()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/../src/lib)
include_directories(${PROJECT_SOURCE_DIR}/../extern/arduinojson/src)
include_directories(${PROJECT_SOURCE_DIR}/../extern/googletest)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# ARK Tests Sources
# ------------------------------------------------------------------------------

set (ARK_TEST_SRC
    ${PROJECT_SOURCE_DIR}/common/configuration.cpp
    ${PROJECT_SOURCE_DIR}/common/fee_policy.cpp
    ${PROJECT_SOURCE_DIR}/common/network.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve.cpp
    ${PROJECT_SOURCE_DIR}/crypto/hash.cpp
    ${PROJECT_SOURCE_DIR}/crypto/message.cpp
    ${PROJECT_SOURCE_DIR}/crypto/slot.cpp
    ${PROJECT_SOURCE_DIR}/defaults/static_fees.cpp
    ${PROJECT_SOURCE_DIR}/defaults/transaction_types.cpp
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
    ${PROJECT_SOURCE_DIR}/utils/crypto_helpers.cpp
    ${PROJECT_SOURCE_DIR}/utils/hex.cpp
    ${PROJECT_SOURCE_DIR}/utils/str.cpp
)

# ------------------------------------------------------------------------------

find_library(ARK_CPP_CRYPTO_TESTS PUBLIC)

add_executable(ark_cpp_crypto_tests ${ARK_TEST_SRC})

target_link_libraries(ark_cpp_crypto_tests ARK_CPP_CRYPTO_LIB gtest gtest_main)

add_test(NAME test COMMAND  ark_cpp_crypto_tests)

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")

    if (UNIX)
        include_directories(${PROJECT_SOURCE_DIR}/../extern/googletest/google/src)
        include_directories(${PROJECT_SOURCE_DIR}/../extern/googletest/googletest/include)
    endif()

    include("${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake")

    setup_target_for_coverage(ARK_CRYPTO_TESTS_COVERAGE ark_cpp_crypto_tests coverage)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")

endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

# ------------------------------------------------------------------------------
