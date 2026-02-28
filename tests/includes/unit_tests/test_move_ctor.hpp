/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_move_ctor.hpp
/// @brief Definition of move constructor tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MATRIX_MOVE_CTOR_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MATRIX_MOVE_CTOR_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test move constructor of vectors
class vector_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_move_ctor_test() : unit_test("vector_move_ctor", "Test move in constructor") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test move constructor of matrices
class matrix_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_move_ctor_test() : unit_test("matrix_move_ctor", "Test move in constructor") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
