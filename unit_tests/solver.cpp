/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/solver.cpp
/// @brief Unit tests for solvers
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include <gtest/gtest.h>

namespace la {
namespace algorithm {

/// @brief Test default constructor for dense matrix
TEST(solver, lu_decomposition)
{
    matrix<double> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});
    la::algorithm::lu_decomposition<matrix<double>, vector<double>> lu(A);
    const vector<double> x = lu.solve(b);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 2.2);
    EXPECT_DOUBLE_EQ(x(1), 1.4);
    EXPECT_DOUBLE_EQ(x(2), 1.2);
    EXPECT_THROW(lu.solve(vector<double>(4)), util::error);
}

TEST(solver, lu_decomposition_w_x)
{
    matrix<double> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});
    vector<double> x(3);
    la::algorithm::lu_decomposition<matrix<double>, vector<double>> lu(A);
    lu.solve(b, x);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 2.2);
    EXPECT_DOUBLE_EQ(x(1), 1.4);
    EXPECT_DOUBLE_EQ(x(2), 1.2);
    vector<double> x_wrong(4);
    EXPECT_THROW(lu.solve(b, x_wrong), util::error);
}

} // namespace algorithm
} // namespace la
