/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations.cpp
/// @brief Unit tests for operations
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/data_structure/expressions/iterator.hpp"
#include "la/dense"
#include "la/operation/multiplication.hpp"
#include "la/sparse"
#include <gtest/gtest.h>

namespace la {

/// @brief Testing column index iterator
TEST(ops, const_col_idx_iterator)
{
    sparse_matrix<int> a({{0, 1}, {2}, {1, 3}}, {3, 4, 5, 6, 7}, 5);
    sparse_matrix<int> b({{1}, {1}, {1, 3, 4}}, {3, 4, 5, 6, 7}, 5);

    la::expressions::const_col_idx_iterator<sparse_matrix<int>> iter_row0(a, b, 0);
    la::expressions::const_col_idx_iterator<sparse_matrix<int>> iter_row1(a, b, 1);
    la::expressions::const_col_idx_iterator<sparse_matrix<int>> iter_row2(a, b, 2);

    // Test row 0
    EXPECT_EQ(*iter_row0, 0);
    ++iter_row0;
    EXPECT_EQ(*iter_row0, 1);
    iter_row0++;
    EXPECT_EQ(iter_row0, iter_row0.end());
    EXPECT_THROW(iter_row0++, util::error);
    EXPECT_EQ(*iter_row1, 1);
    EXPECT_EQ(*(++iter_row1), 2);
    EXPECT_TRUE(++iter_row1 == iter_row1.end());
    EXPECT_THROW(*iter_row1, util::error);

    // Test row 2
    EXPECT_EQ(*(iter_row2++), 1);
    EXPECT_EQ(*(iter_row2++), 3);
    EXPECT_EQ(*(iter_row2++), 4);
    EXPECT_EQ(iter_row2, iter_row2.end());
}

/// \brief Testing sparse matrix add
TEST(ops, sparse_matrix_add)
{
    const sparse_matrix<int> a({{0, 1}, {2}, {1, 3}}, {3, 4, 5, 6, 7}, 5);
    const sparse_matrix<int> b({{1}, {1}, {1, 3, 4}}, {3, 4, 5, 6, 7}, 5);
    sparse_matrix_builder<int> c = a + b;
    EXPECT_EQ(c.rows(), 3);
    EXPECT_EQ(c.cols(), 5);

    EXPECT_EQ(c(0, 0), 3);
    EXPECT_EQ(c(0, 1), 7);
    EXPECT_EQ(c(0, 2), 0);
    EXPECT_EQ(c(0, 3), 0);
    EXPECT_EQ(c(0, 4), 0);

    EXPECT_EQ(c(1, 0), 0);
    EXPECT_EQ(c(1, 1), 4);
    EXPECT_EQ(c(1, 2), 5);
    EXPECT_EQ(c(1, 3), 0);
    EXPECT_EQ(c(1, 4), 0);

    EXPECT_EQ(c(2, 0), 0);
    EXPECT_EQ(c(2, 1), 11);
    EXPECT_EQ(c(2, 2), 0);
    EXPECT_EQ(c(2, 3), 13);
    EXPECT_EQ(c(2, 4), 7);
}

/// \brief Testing sparse matrix transposed multiply
TEST(ops, sparse_matrix_transpose_multiply)
{
    const sparse_matrix<int> a({{1, 3}, {}, {1, 2, 3}}, {2, 1, 1, 1, 4}, 4);
    const vector<int> x({1, 2, 3});
    const vector<int> y = transp_mult(a, x);
    EXPECT_EQ(y.rows(), 4);
    EXPECT_EQ(y(0), 0);
    EXPECT_EQ(y(1), 5);
    EXPECT_EQ(y(2), 3);
    EXPECT_EQ(y(3), 13);
}

} // namespace la
