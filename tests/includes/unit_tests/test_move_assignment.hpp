/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_move_assignment.hpp
/// @brief Definition of move assignment tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MATRIX_MOVE_ASSIGNMENT_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MATRIX_MOVE_ASSIGNMENT_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test move assignment of vectors
class vector_move_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_move_assignment_test() : unit_test("vector_move_assignment", "Test moving during assign")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test move assignment of matrices
class matrix_move_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_move_assignment_test() : unit_test("matrix_move_assignment", "Test moving during assign")
    {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
