/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_dense_algorithm.hpp
/// @brief Declaration of testing dense algorithms
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_DENSE_ALGORITHM_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_DENSE_ALGORITHM_HPP

#include "tests/includes/unit_test.hpp"
#include "tests/includes/unit_tests/unit_test_collection.hpp"

namespace la {
namespace test {

/// @brief Add all dense tests to the test_collection
void add_all_dense_algorithm(unit_test_collection &collection);

/// @brief Test lu decompositions
class lu_decomposition_test : public unit_test
{
public:
    /// @brief Constructing the test
    lu_decomposition_test() : unit_test("lu_decomposition", "Testing LU decomposition") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Matrix-matrix multiplication
class mat_mat_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    mat_mat_mult_test() : unit_test("mat_mat_mult", "Testing A*B and A*alpha") {}
    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
