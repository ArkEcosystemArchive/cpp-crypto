
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
    ${PROJECT_SOURCE_DIR}/common/network.cpp
)

# ------------------------------------------------------------------------------
# Crypto

set(CRYPTO_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/crypto/curve_ecdsa_sign_null_hash.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve_ecdsa_sign_null_privatekey.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve_ecdsa_sign.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve_publickey.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve_verify_invalid.cpp
    ${PROJECT_SOURCE_DIR}/crypto/curve_verify_valid.cpp
    ${PROJECT_SOURCE_DIR}/crypto/hash.cpp
    ${PROJECT_SOURCE_DIR}/crypto/message_sign.cpp
    ${PROJECT_SOURCE_DIR}/crypto/message_verify.cpp
    ${PROJECT_SOURCE_DIR}/crypto/message.cpp
    ${PROJECT_SOURCE_DIR}/crypto/slot.cpp
)

# ------------------------------------------------------------------------------
# Identities

set(IDENTITIES_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/identities/address.cpp
    ${PROJECT_SOURCE_DIR}/identities/keys.cpp
    ${PROJECT_SOURCE_DIR}/identities/keys_publickey.cpp
    ${PROJECT_SOURCE_DIR}/identities/privatekey.cpp
    ${PROJECT_SOURCE_DIR}/identities/publickey.cpp
    ${PROJECT_SOURCE_DIR}/identities/wif.cpp
)

# ------------------------------------------------------------------------------
# Managers

set(MANAGERS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/managers/fee_manager.cpp
    ${PROJECT_SOURCE_DIR}/managers/network_manager.cpp
)

# ------------------------------------------------------------------------------
# Networks

set(NETWORKS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/networks/devnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/mainnet.cpp
    ${PROJECT_SOURCE_DIR}/networks/testnet.cpp
)

# ------------------------------------------------------------------------------
# Transactions Test Sources
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Builders

set(TRANSACTIONS_BUILDERS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/transactions/builders/transfer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/second_signature.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/delegate_registration.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/vote.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/ipfs.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/multi_payment.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/htlc_lock.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/htlc_claim.cpp
    ${PROJECT_SOURCE_DIR}/transactions/builders/htlc_refund.cpp
)

# ------------------------------------------------------------------------------
# Defaults

set(TRANSACTIONS_DEFAULTS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/transactions/defaults/fees_types.cpp
)


# ------------------------------------------------------------------------------
# Serialization/Deserialization

set(TRANSACTIONS_SERDE_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/transactions/deserializer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/serializer.cpp
)

# ------------------------------------------------------------------------------
# v1 Types

set(TRANSACTIONS_TYPES_V1_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/transactions/types/transfer_v1.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/second_signature_v1.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/delegate_registration_v1.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/vote_v1.cpp
)

# ------------------------------------------------------------------------------
# Types

set(TRANSACTIONS_TYPES_TEST_SOURCE
    ${TRANSACTIONS_TYPES_V1_SOURCE}
    ${PROJECT_SOURCE_DIR}/transactions/types/transfer.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/second_signature.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/delegate_registration.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/vote.cpp
    # ${PROJECT_SOURCE_DIR}/transactions/types/multi_signature.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/ipfs.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/multi_payment.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/delegate_resignation.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/htlc_lock.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/htlc_claim.cpp
    ${PROJECT_SOURCE_DIR}/transactions/types/htlc_refund.cpp
)

# ------------------------------------------------------------------------------
# Transactions Test Source Files

set(TRANSACTIONS_TEST_SOURCE
    ${TRANSACTIONS_BUILDERS_TEST_SOURCE}
    ${TRANSACTIONS_DEFAULTS_TEST_SOURCE}
    ${TRANSACTIONS_SERDE_TEST_SOURCE}
    ${TRANSACTIONS_TYPES_V1_TEST_SOURCE}
    ${TRANSACTIONS_TYPES_TEST_SOURCE}
    ${TRANSACTIONS_TRANSACTION_TEST_SOURCE}

    ${PROJECT_SOURCE_DIR}/transactions/transaction.cpp
)

# ------------------------------------------------------------------------------
# Utils

set(UTILS_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/utils/base58.cpp
    ${PROJECT_SOURCE_DIR}/utils/crypto_helpers.cpp
    ${PROJECT_SOURCE_DIR}/utils/hex.cpp
    ${PROJECT_SOURCE_DIR}/utils/str.cpp
    ${PROJECT_SOURCE_DIR}/utils/unpack.cpp
)

# ------------------------------------------------------------------------------
# ARK C++ Library Test Source

set(ARK_TEST_SOURCE
    ${COMMON_TEST_SOURCE}
    ${CRYPTO_TEST_SOURCE}
    ${IDENTITIES_TEST_SOURCE}
    ${MANAGERS_TEST_SOURCE}
    ${NETWORKS_TEST_SOURCE}
    ${TRANSACTIONS_TEST_SOURCE}
    ${UTILS_TEST_SOURCE}
)

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
# Coverage
# ------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include("${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake")

    setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_NAME}_tests coverage)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()  #CMAKE_BUILD_TYPE STREQUAL "Coverage"

# ------------------------------------------------------------------------------
