
cmake_minimum_required(VERSION 3.2.2)

project(CPP_CRYPTO_EXAMPLE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

if (MSVC)
	add_definitions(
		-D_CRT_SECURE_NO_WARNINGS
		-D_SCL_SECURE_NO_WARNINGS
		-DNOMINMAX
	)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# clone submodules - Uncomment when used outside of the Ark cpp-crypto source tree
#execute_process(
#	COMMAND git submodule update --init --recursive
#	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#)

add_subdirectory(lib/cpp-crypto/src)

set(SRC_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ARK_CPP_CRYPTO_LIB)

