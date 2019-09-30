
cmake_minimum_required(VERSION 3.2.2)

project(ARK_CPP_CRYPTO_LIB C CXX)

# ------------------------------------------------------------------------------
# External Dependencies
# ------------------------------------------------------------------------------

set(BIP66_SRC
    ${PROJECT_SOURCE_DIR}/../extern/BIP66/src/bip66.cpp
)

set(uECC_SRC
    ../extern/uecc/uECC.c
)

include_directories(${PROJECT_SOURCE_DIR}/../extern/arduinojson/src)
include_directories(${PROJECT_SOURCE_DIR}/../extern/uecc)
include_directories(${PROJECT_SOURCE_DIR}/../extern/bip66/src)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Internal Libraries
# ------------------------------------------------------------------------------

set(BCL_SRC
    lib/bcl/Base58Check.cpp
    lib/bcl/CurvePoint.cpp
    lib/bcl/Ecdsa.cpp
    lib/bcl/FieldInt.cpp
    lib/bcl/Ripemd160.cpp
    lib/bcl/Sha256Hash.cpp
    lib/bcl/Sha256.cpp
    lib/bcl/Sha512.cpp
    lib/bcl/Uint256.cpp
    lib/bcl/Utils.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib/bcl)
include_directories(${PROJECT_SOURCE_DIR}/lib/rfc6979)

# ------------------------------------------------------------------------------

set(LIB_SRC
    ${BCL_SRC}
    ${uECC_SRC}
    ${BIP66_SRC}
)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# ARK Sources
# ------------------------------------------------------------------------------

set(ARK_SRC
    common/configuration.cpp
    common/network.cpp
    crypto/curve.cpp
    crypto/hash.cpp
    crypto/message.cpp
    crypto/slot.cpp
    identities/address.cpp
    identities/keys.cpp
    identities/privatekey.cpp
    identities/publickey.cpp
    identities/wif.cpp
    managers/fee_manager.cpp
    managers/network_manager.cpp
    transactions/builder.cpp
    transactions/deserializer.cpp
    transactions/serializer.cpp
    transactions/transaction.cpp
    utils/base58.cpp
)

# ------------------------------------------------------------------------------

add_library(${PROJECT_NAME} STATIC
    ${LIB_SRC}
    ${ARK_SRC}
)

# ------------------------------------------------------------------------------

set(CPP_CRYPTO_BUILD_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/cpp-crypto
    ${PROJECT_SOURCE_DIR}/lib/
)

include_directories(${CPP_CRYPTO_BUILD_INCLUDE_DIRS})

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CPP_CRYPTO_BUILD_INCLUDE_DIRS}
)

if (MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()
