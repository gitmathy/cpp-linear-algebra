/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/performance_tests/decompose.hpp
/// @brief Definition of decomposition performance tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_PERFORMANCE_TESTS_DECOMPOSE_HPP
#define LA_TEST_INCLUDES_PERFORMANCE_TESTS_DECOMPOSE_HPP

#include "la/dense"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief LU decomposition of A
class lu_decompose : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    void run_single_test() override
    {
        la::algorithm::lu_decomposition<matrix<double>, vector<double>> decomposition(p_A);
    }

public:
    /// @brief Set me up
    lu_decompose(const size_type runs, const size_type n)
        : performance_test("lu_decompose", "Testing LU-decompose A", runs), p_size(n)
    {}

    /// @brief Setup the test
    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

/// @brief Solve x= A^-1 * b
class decompose_solve_lu : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    void run_single_test() override
    {
        la::algorithm::lu_decomposition<matrix<double>, vector<double>> decomposition(p_A);
        decomposition.solve(p_b_vec);
    }

public:
    /// @brief Set me up
    decompose_solve_lu(const size_type runs, const size_type n)
        : performance_test("decompose_solve_lu", "Testing A^1*b", runs), p_size(n)
    {}

    /// @brief Setup the test
    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

} // namespace test
} // namespace la
#endif
