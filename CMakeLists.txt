cmake_minimum_required(VERSION 3.22)
project(linear_algebra CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiler to match the Makefile, if available
find_program(GCC12_COMPILER g++-12)
if(GCC12_COMPILER)
    set(CMAKE_CXX_COMPILER ${GCC12_COMPILER})
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast")
elseif(MSVC)
    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ot /Oi /GL /Gw /W4 /permissive-")
else()
    message(WARNING "g++-12 not found. Using default C++ compiler.")
endif()

# Set compiler flags

# Include the root directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Find the TBB library (required for linking)
find_package(TBB REQUIRED)

# --- Common Source Files ---
file(GLOB COMMON_SRCS "tests/src/*.cpp")

# --- Unit Test Target ---
file(GLOB UNIT_TEST_SRCS "tests/src/unit_tests/*.cpp")
add_executable(unit_tests tests/unit_tests.cpp ${COMMON_SRCS} ${UNIT_TEST_SRCS})
target_link_libraries(unit_tests PRIVATE TBB::tbb)
set_target_properties(unit_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit/archives"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit/libs"
)

# --- Performance Test Target ---
file(GLOB PERF_TEST_SRCS "tests/src/performance_tests/*.cpp")
add_executable(performance_test tests/performance_test.cpp ${COMMON_SRCS} ${PERF_TEST_SRCS})
target_compile_definitions(performance_test PRIVATE PARALLEL)
target_link_libraries(performance_test PRIVATE TBB::tbb)
set_target_properties(performance_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/perf"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/perf/archives"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/perf/libs"
)

# --- Debug Target ---
add_executable(debug_test test.cpp)
target_link_libraries(debug_test PRIVATE TBB::tbb)
set_target_properties(debug_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/debug"
)

message(STATUS "CMake project configured. You can now open this directory in Visual Studio.")
message(STATUS "Build configurations:")
message(STATUS "  - To build unit tests: Select the 'unit_tests' target and 'Debug' configuration.")
message(STATUS "  - To build debug test: Select the 'debug_test' target and 'Debug' configuration.")
message(STATUS "  - To build performance tests: Select the 'performance_test' target and 'Release' configuration.")
