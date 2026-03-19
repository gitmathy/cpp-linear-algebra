cmake_minimum_required(VERSION 3.14)
project(unit_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -DLA_CHECK=7 -DLA_DEBUG_LEVEL=4)

# Include the main project's headers
include_directories(../)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: CMAKE_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>
FetchContent_MakeAvailable(googletest)

# Create the test executable
add_executable(
    run_unit_tests
    pch.cpp
    vector.cpp
    matrix.cpp
    sparse_matrix.cpp
    solver.cpp
    sparse_matrix_builder.cpp
    operations.cpp
)

# Link against Google Test
target_link_libraries(
    run_unit_tests
    GTest::gtest_main
)

# Enable testing
include(GoogleTest)
gtest_discover_tests(run_unit_tests)
