
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
    ${PROJECT_SOURCE_DIR}/lib/rfc6979
)

include_directories(${INTERNAL_LIBRARY_SOURCE_DIRS})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# ARK C++ Crypto Source
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Common

set(COMMON_SOURCE
    common/configuration.cpp
    common/network.cpp
)

# ------------------------------------------------------------------------------
# Crypto

set(CRYPTO_SOURCE
    crypto/curve.cpp
    crypto/hash.cpp
    crypto/message.cpp
    crypto/slot.cpp
)

# ------------------------------------------------------------------------------
# Identities

set(IDENTITIES_SOURCE
    identities/address.cpp
    identities/keys.cpp
    identities/privatekey.cpp
    identities/publickey.cpp
    identities/wif.cpp
)

# ------------------------------------------------------------------------------
# Transactions

# Types
set(TRANSACTIONS_TYPES_SOURCE
    transactions/types/transfer.cpp
    transactions/types/second_signature.cpp
    transactions/types/delegate_registration.cpp
    transactions/types/vote.cpp
    # transactions/types/multi_signature.cpp
    transactions/types/ipfs.cpp
    transactions/types/multi_payment.cpp
    transactions/types/htlc_lock.cpp
    transactions/types/htlc_claim.cpp
    transactions/types/htlc_refund.cpp
)

# Serialization/Deserialization
set(TRANSACTIONS_SERDE_SOURCE
    transactions/deserializer.cpp
    transactions/serializer.cpp
)

# Mapping
set(TRANSACTIONS_MAPPING_SOURCE
    transactions/mapping/json.cpp
    transactions/mapping/mapping.cpp
)

# Transaction Source Files
set(TRANSACTIONS_SOURCE
    ${TRANSACTIONS_TYPES_SOURCE}
    ${TRANSACTIONS_SERDE_SOURCE}
    ${TRANSACTIONS_MAPPING_SOURCE}
    transactions/transaction.cpp
)

# ------------------------------------------------------------------------------
# Utils

set(UTILS_SOURCE utils/base58.cpp)

# ------------------------------------------------------------------------------
# ARK C++ Crypto Library Source

set(ARK_LIBRARY_SOURCE
    ${COMMON_SOURCE}
    ${CRYPTO_SOURCE}
    ${IDENTITIES_SOURCE}
    ${TRANSACTIONS_SOURCE}
    ${UTILS_SOURCE}
)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Add the Source Files to the Library
# ------------------------------------------------------------------------------

add_library(${PROJECT_NAME} STATIC
            ${EXTERNAL_LIBRARY_SOURCE}
            ${INTERNAL_LIBRARY_SOURCE}
            ${ARK_LIBRARY_SOURCE}
)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Set the Include Folders
# ------------------------------------------------------------------------------

set(ARK_CPP_CRYPTO_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/cpp-crypto
    ${PROJECT_SOURCE_DIR}/lib/
)

include_directories(${ARK_CPP_CRYPTO_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${ARK_CPP_CRYPTO_INCLUDE_DIRS})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Windows: Link to `crypt32`
# ------------------------------------------------------------------------------

if (MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()

# ------------------------------------------------------------------------------
