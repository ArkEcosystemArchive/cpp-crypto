
cmake_minimum_required(VERSION 3.2)

project(ark_cpp_crypto C CXX)

# ------------------------------------------------------------------------------
# External Libraries
# ------------------------------------------------------------------------------

include(${CMAKE_SOURCE_DIR}/cmake/External.cmake)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Internal Libraries
# ------------------------------------------------------------------------------

set(INTERNAL_LIBRARY_SOURCE_DIRS
    ${PROJECT_SOURCE_DIR}/lib/bcl
    ${PROJECT_SOURCE_DIR}/lib/rfc6979)

include_directories(${INTERNAL_LIBRARY_SOURCE_DIRS})

# ------------------------------------------------------------------------------

set(BCL_SOURCE
    lib/bcl/Base58Check.cpp
    lib/bcl/CurvePoint.cpp
    lib/bcl/Ecdsa.cpp
    lib/bcl/FieldInt.cpp
    lib/bcl/Ripemd160.cpp
    lib/bcl/Sha256Hash.cpp
    lib/bcl/Sha256.cpp
    lib/bcl/Sha512.cpp
    lib/bcl/Uint256.cpp
    lib/bcl/Utils.cpp)

set(INTERNAL_LIBRARY_SOURCE ${BCL_SOURCE})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# ARK C++ Crypto Source
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Common

set(COMMON_SOURCE
    common/configuration.cpp
    common/network.cpp)

# ------------------------------------------------------------------------------
# Crypto

set(CRYPTO_SOURCE
    crypto/curve.cpp
    crypto/hash.cpp
    crypto/message.cpp
    crypto/slot.cpp)

# ------------------------------------------------------------------------------
# Identities

set(IDENTITIES_SOURCE
    identities/address.cpp
    identities/keys.cpp
    identities/privatekey.cpp
    identities/publickey.cpp
    identities/wif.cpp)

# ------------------------------------------------------------------------------
# Managers

set(MANAGERS_SOURCE
    managers/fee_manager.cpp
    managers/network_manager.cpp
)

# ------------------------------------------------------------------------------
# Transactions

set(TRANSACTIONS_SOURCE
    transactions/builder.cpp
    transactions/deserializer.cpp
    transactions/serializer.cpp
    transactions/transaction.cpp)

# ------------------------------------------------------------------------------
# Utils

set(UTILS_SOURCE utils/base58.cpp)

# ------------------------------------------------------------------------------
# ARK C++ Crypto Library Source

set(ARK_SOURCE
    ${COMMON_SOURCE}
    ${CRYPTO_SOURCE}
    ${IDENTITIES_SOURCE}
    ${MANAGERS_SOURCE}
    ${TRANSACTIONS_SOURCE}
    ${UTILS_SOURCE})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Add the Source Files to the Library
# ------------------------------------------------------------------------------

add_library(${PROJECT_NAME} STATIC
            ${EXTERNAL_LIBRARY_SOURCE}
            ${INTERNAL_LIBRARY_SOURCE}
            ${ARK_SOURCE})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Set the Source Folders
# ------------------------------------------------------------------------------

set(ARK_CPP_CRYPTO_SOURCE_DIR
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/cpp-crypto
    ${PROJECT_SOURCE_DIR}/lib/)

include_directories(${ARK_CPP_CRYPTO_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${ARK_CPP_CRYPTO_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Windows: Link to `crypt32`
# ------------------------------------------------------------------------------

if (MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()

# ------------------------------------------------------------------------------
