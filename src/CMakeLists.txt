
cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-lib C CXX)

add_subdirectory(lib/bip39/src)

set(BCL_SRC
	bcl/Base58Check.cpp
	bcl/CurvePoint.cpp
	bcl/Ecdsa.cpp
	bcl/FieldInt.cpp
	bcl/Ripemd160.cpp
	bcl/Sha256Hash.cpp
	bcl/Sha256.cpp
	bcl/Sha512.cpp
	bcl/Uint256.cpp
	bcl/Utils.cpp
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
include_directories(${PROJECT_SOURCE_DIR}/lib/uECC)
include_directories(${PROJECT_SOURCE_DIR}/lib/ArduinoJson)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${cpp_crypto_build_include_dirs}
)

target_link_libraries(${PROJECT_NAME} PRIVATE bip39)

if (MSVC)
	target_link_libraries(${PROJECT_NAME} PUBLIC crypt32)
endif()
