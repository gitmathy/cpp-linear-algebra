/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_unary_assignment.hpp
/// @brief Definition of unary assignment test
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_UNARY_ASSIGNMENT_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_UNARY_ASSIGNMENT_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub assignment of vectors
class vector_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_unary_assignment_test() : unit_test("vector_unary_assignment", "Testing b -= a") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub assignment of static_vectors
class static_vector_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_unary_assignment_test()
        : unit_test("static_vector_unary_assignment_test", "Testing b -= a")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub assignment of matrices
class matrix_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_unary_assignment_test() : unit_test("matrix_unary_assignment", "Testing B -= A") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
