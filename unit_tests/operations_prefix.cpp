/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations_prefix.cpp
/// @brief Unit tests for add operations prefix
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

/// \brief Testing -vector
TEST(ops_prefix, vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = -a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), -1);
    EXPECT_EQ(z(1), -2);
    EXPECT_EQ(z(2), -3);
}

/// \brief Testing -static_vector
TEST(ops_prefix, static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = -a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), -1);
    EXPECT_EQ(z(1), -2);
    EXPECT_EQ(z(2), -3);
}

/// \brief Testing -matrix add
TEST(ops_prefix, matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = -a;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), -1);
    EXPECT_EQ(z(0, 1), -2);
    EXPECT_EQ(z(0, 2), -3);
    EXPECT_EQ(z(1, 0), -4);
    EXPECT_EQ(z(1, 1), -5);
    EXPECT_EQ(z(1, 2), -6);
}

} // namespace la
