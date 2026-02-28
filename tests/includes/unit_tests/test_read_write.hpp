/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_read_write.hpp
/// @brief Definition of read write test
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_READ_WRITE_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_READ_WRITE_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test writing and reading vectors
class vector_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_read_write_test() : unit_test("vector_read_write", "Test reading and writing to files")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test writing and reading matrices
class matrix_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_read_write_test() : unit_test("matrix_read_write", "Test reading and writing to files")
    {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
