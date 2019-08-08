
cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-lib C CXX)

set(BIP66_SRC
    ${PROJECT_SOURCE_DIR}/lib/BIP66/src/bip66.cpp
)

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

set(uECC_SRC
    lib/uECC/uECC.c
)

set(COMMON_SRC
    common/configuration.cpp
    common/network.cpp
    crypto/curve.cpp
    crypto/hash.cpp
    defaults/static_fees.cpp
    helpers/crypto.cpp
    identities/address.cpp
    identities/keys.cpp
    identities/privatekey.cpp
    identities/publickey.cpp
    identities/wif.cpp
    managers/fee_manager.cpp
    managers/network_manager.cpp
    networks/devnet.cpp
    networks/mainnet.cpp
    networks/testnet.cpp
    transactions/builder.cpp
    transactions/deserializer.cpp
    transactions/serializer.cpp
    transactions/transaction.cpp
    utils/message.cpp
    utils/slot.cpp
    utils/base58.cpp

)

add_library(${PROJECT_NAME} STATIC
    ${BCL_SRC}
    ${uECC_SRC}
    ${BIP66_SRC}
    ${COMMON_SRC}
)

set(cpp_crypto_build_include_dirs
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/cpp-crypto
)

include_directories(${cpp_crypto_build_include_dirs})
include_directories(${PROJECT_SOURCE_DIR}/lib/)
include_directories(${PROJECT_SOURCE_DIR}/lib/ArduinoJson)
include_directories(${PROJECT_SOURCE_DIR}/lib/bcl)
include_directories(${PROJECT_SOURCE_DIR}/lib/rfc6979)
include_directories(${PROJECT_SOURCE_DIR}/lib/uECC)
include_directories(${PROJECT_SOURCE_DIR}/lib/BIP66/src)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${cpp_crypto_build_include_dirs}
)

if (MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()
