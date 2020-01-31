
# ------------------------------------------------------------------------------
# ArduinoJson: https://github.com/bblanchon/ArduinoJson
# ------------------------------------------------------------------------------

# Copy the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/ArduinoJson.txt.in
               ${EXTERNAL_LIBRARY_DIR}/arduinojson/CMakeLists.txt)

# Configure the Cmake build
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/arduinojson)

if(result)
    message(FATAL_ERROR "ArduinoJson: CMake Configuration Failed: ${result}")
endif()

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/arduinojson)

if(result)
    message(FATAL_ERROR "ArduinoJson: Clone and Build Step Failed: ${result}")
endif()

set(ARDUINO_JSON_SOURCE_DIR
    ${EXTERNAL_LIBRARY_DIR}/arduinojson/src/src
    CACHE INTERNAL "ArduinoJson: Source Folder Path")

include_directories(${ARDUINO_JSON_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# BCL: https://github.com/sleepdefic1t/bcl
# ------------------------------------------------------------------------------

# Copy the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/BCL.txt.in
               ${EXTERNAL_LIBRARY_DIR}/bcl/CMakeLists.txt)

# Configure the Cmake build
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bcl)

if(result)
    message(FATAL_ERROR "BCL: CMake Configuration Failed: ${result}")
endif()

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bcl)

if(result)
    message(FATAL_ERROR "BIP66: Clone and Build Step Failed: ${result}")
endif()

set(BCL_SOURCE
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Base58Check.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/CurvePoint.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Ecdsa.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/FieldInt.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Ripemd160.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Sha256.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Sha256Hash.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Uint256.cpp
    ${EXTERNAL_LIBRARY_DIR}/bcl/src/src/Utils.cpp
    CACHE INTERNAL "BCL: Source Files"
)

include_directories(${EXTERNAL_LIBRARY_DIR}/bcl/src/src)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# BIP66: https://github.com/sleepdefic1t/BIP66
# ------------------------------------------------------------------------------

# Copy the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/BIP66.txt.in
               ${EXTERNAL_LIBRARY_DIR}/bip66/CMakeLists.txt)

# Configure the Cmake build
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bip66)

if(result)
    message(FATAL_ERROR "BIP66: CMake Configuration Failed: ${result}")
endif()

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bip66)

if(result)
    message(FATAL_ERROR "BIP66: Clone and Build Step Failed: ${result}")
endif()
                 
set(BIP66_SOURCE
    ${EXTERNAL_LIBRARY_DIR}/bip66/src/src/bip66.cpp
    CACHE INTERNAL "BIP66: Source Files")

include_directories(${EXTERNAL_LIBRARY_DIR}/bip66/src/)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# uECC: https://github.com/kmackay/micro-ecc
# ------------------------------------------------------------------------------

# Copy the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/uECC.txt.in
               ${EXTERNAL_LIBRARY_DIR}/uecc/CMakeLists.txt)

# Configure the Cmake build
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/uecc)

if(result)
    message(FATAL_ERROR "uECC: CMake Configuration Failed: ${result}")
endif()

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/uecc)

if(result)
    message(FATAL_ERROR "uECC: Clone and Build Step Failed: ${result}")
endif()

set(UECC_SOURCE_DIR
    ${EXTERNAL_LIBRARY_DIR}/uecc/src
    CACHE INTERNAL "uECC: Source Folder Path")

set(UECC_SOURCE
    ${EXTERNAL_LIBRARY_DIR}/uecc/src/uECC.c
    CACHE INTERNAL "uECC: Source Files")

include_directories(${UECC_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# External Linkage
# ------------------------------------------------------------------------------

set(EXTERNAL_LIBRARY_SOURCE
    ${BCL_SOURCE}
    ${BIP66_SOURCE}
    ${UECC_SOURCE}
    CACHE INTERNAL "External Lib Binary Files")

# ------------------------------------------------------------------------------
