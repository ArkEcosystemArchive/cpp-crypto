
# ------------------------------------------------------------------------------
# ArduinoJson: https://github.com/bblanchon/ArduinoJson
# ------------------------------------------------------------------------------

# Set the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/ArduinoJson.txt.in
               ${EXTERNAL_LIBRARY_DIR}/arduinojson/CMakeLists.txt)

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/arduinojson)

if(result)
    message(FATAL_ERROR "ArduinoJson: CMake Failed: ${result}")
endif()

# Build the Cloned Repo
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/arduinojson)

if(result)
    message(FATAL_ERROR "ArduinoJson: Build Failed: ${result}")
endif()

set(ARDUINO_JSON_SOURCE_DIR
    ${EXTERNAL_LIBRARY_DIR}/arduinojson/src/src
    CACHE INTERNAL "ArduinoJson: Source Folder Path")

include_directories(${ARDUINO_JSON_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# BIP66: https://github.com/sleepdefic1t/BIP66
# ------------------------------------------------------------------------------

# Set the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/BIP66.txt.in
               ${EXTERNAL_LIBRARY_DIR}/bip66/CMakeLists.txt)

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bip66)

if(result)
    message(FATAL_ERROR "BIP66: CMake Failed: ${result}")
endif()

# Build the Cloned Repo
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/bip66)

if(result)
    message(FATAL_ERROR "BIP66: Build Failed: ${result}")
endif()

add_subdirectory("${EXTERNAL_LIBRARY_DIR}/bip66/src/src"
                 "${EXTERNAL_LIBRARY_DIR}/bip66/build"
                 EXCLUDE_FROM_ALL)
                 
set(BIP66_SOURCE
    ${EXTERNAL_LIBRARY_DIR}/bip66/src/src/bip66.cpp
    CACHE INTERNAL "BIP66: Source Files")

include_directories(${BIP66_SOURCE_DIR})

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# uECC: https://github.com/kmackay/micro-ecc
# ------------------------------------------------------------------------------

# Set the configuration
configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/uECC.txt.in
               ${EXTERNAL_LIBRARY_DIR}/uecc/CMakeLists.txt)

# Execute Git Clone and run Cmake
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/uecc)

if(result)
    message(FATAL_ERROR "uECC: CMake Failed: ${result}")
endif()

# Build the Cloned Repo
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/uecc)

if(result)
    message(FATAL_ERROR "uECC: Build Failed: ${result}")
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
    ${BIP66_SOURCE}
    ${UECC_SOURCE}
    CACHE INTERNAL "External Lib Binary Files")

# ------------------------------------------------------------------------------
