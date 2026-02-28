/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_construct.hpp
/// @brief Definition of constructor tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_CONSTRUCT_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_CONSTRUCT_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test construction of vectors
class vector_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    vector_construct_test() : unit_test("vector_construct", "Testing constructor") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test construction of matrices
class matrix_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    matrix_construct_test() : unit_test("matrix_construct", "Testing constructor") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
