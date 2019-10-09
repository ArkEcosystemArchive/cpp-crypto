
# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------

option(BUILD_GMOCK OFF FORCE)
option(PACKAGE_TESTS OFF FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

configure_file(${CMAKE_SOURCE_DIR}/cmake/extern/GTest.txt.in
               ${EXTERNAL_LIBRARY_DIR}/googletest/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/googletest )

if(result)
    message(FATAL_ERROR "CMake step for GTest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${EXTERNAL_LIBRARY_DIR}/googletest )

if(result)
    message(FATAL_ERROR "Build step for GTest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("${EXTERNAL_LIBRARY_DIR}/googletest/src"
                 "${EXTERNAL_LIBRARY_DIR}/googletest/build"
                 EXCLUDE_FROM_ALL)

# ------------------------------------------------------------------------------
