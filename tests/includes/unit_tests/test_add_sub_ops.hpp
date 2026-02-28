/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_add_sub_ops.hpp
/// @brief Definition of add and substract tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MATRIX_ADD_SUB_OPS_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MATRIX_ADD_SUB_OPS_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub of vectors
class vector_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_add_sub_ops_test() : unit_test("vector_add_sub_ops", "Testing - and +") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub of matrices
class matrix_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_add_sub_ops_test() : unit_test("matrix_add_sub_ops", "Testing - and +") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
