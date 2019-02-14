
cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-lib C CXX)

add_subdirectory(lib/bip39/src)

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
  configuration/fee.cpp
	configuration/network.cpp
  helpers/crypto.cpp
  helpers/encoding/der.cpp
	identities/address.cpp
  identities/mnemonic.cpp
	identities/privatekey.cpp
	identities/publickey.cpp
	identities/wif.cpp
	networks/abstractnetwork.cpp
  transactions/builder.cpp
  transactions/deserializer.cpp
  transactions/serializer.cpp
  transactions/transaction.cpp
  utils/message.cpp
  utils/slot.cpp
)

add_library(${PROJECT_NAME}
	STATIC
	${BCL_SRC}
	${uECC_SRC}
	${COMMON_SRC}
)

set(cpp_crypto_build_include_dirs
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/cpp-crypto
)
include_directories(${cpp_crypto_build_include_dirs})
include_directories(${PROJECT_SOURCE_DIR}/lib/ArduinoJson)
include_directories(${PROJECT_SOURCE_DIR}/lib/bcl)
include_directories(${PROJECT_SOURCE_DIR}/lib/bip39)
include_directories(${PROJECT_SOURCE_DIR}/lib/rfc6979)
include_directories(${PROJECT_SOURCE_DIR}/lib/uECC)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${cpp_crypto_build_include_dirs}
)

target_link_libraries(${PROJECT_NAME} PRIVATE bip39)

if (MSVC)
	target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()
