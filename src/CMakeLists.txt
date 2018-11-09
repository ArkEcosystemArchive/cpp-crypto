
cmake_minimum_required(VERSION 3.2.2)

project(Ark-Cpp-Crypto-lib)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_INCLUDE_DIR}
)

set(BCL_SRC
	${PROJECT_INCLUDE_DIR}/bcl/Base58Check.cpp
	${PROJECT_INCLUDE_DIR}/bcl/CurvePoint.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Ecdsa.cpp
	${PROJECT_INCLUDE_DIR}/bcl/FieldInt.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Ripemd160.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Sha256Hash.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Sha256.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Sha512.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Uint256.cpp
	${PROJECT_INCLUDE_DIR}/bcl/Utils.cpp
)

set(uECC_SRC
	${PROJECT_INCLUDE_DIR}/uECC/uECC.c
)

set(COMMON_SRC
	${PROJECT_SOURCE_DIR}/configuration/fee.cpp
	${PROJECT_SOURCE_DIR}/configuration/network.cpp
  ${PROJECT_SOURCE_DIR}/helpers/helpers.cpp
  ${PROJECT_SOURCE_DIR}/helpers/encoding/der.cpp
	${PROJECT_SOURCE_DIR}/identities/address.cpp
	${PROJECT_SOURCE_DIR}/identities/privatekey.cpp
	${PROJECT_SOURCE_DIR}/identities/publickey.cpp
	${PROJECT_SOURCE_DIR}/identities/wif.cpp
	${PROJECT_SOURCE_DIR}/networks/abstractnetwork.cpp
  ${PROJECT_SOURCE_DIR}/transactions/builder.cpp
  ${PROJECT_SOURCE_DIR}/transactions/deserializer.cpp
  ${PROJECT_SOURCE_DIR}/transactions/serializer.cpp
  ${PROJECT_SOURCE_DIR}/transactions/transaction.cpp
  ${PROJECT_SOURCE_DIR}/utils/message.cpp
  ${PROJECT_SOURCE_DIR}/utils/slot.cpp
)

add_library(Ark-Cpp-Crypto-lib
	STATIC
	${BCL_SRC}
	${uECC_SRC}
	${COMMON_SRC}
)

if (MSVC)
	target_link_libraries(Ark-Cpp-Crypto-lib PUBLIC crypt32)
endif()
