/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/expressions.cpp
/// @brief Unit tests for expressions
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

} // namespace la
