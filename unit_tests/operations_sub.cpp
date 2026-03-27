/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations_sub.cpp
/// @brief Unit tests for substract operations
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

/// \brief Testing vector add
TEST(ops_sub, vector_vector)
{
    const vector<int> a({4, 5, 6});
    const vector<int> b({1, 2, 3});
    const vector<int> z = a - b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 3);
    EXPECT_EQ(z(2), 3);
}

/// \brief Testing vector - operant
TEST(ops_sub, vector_operant)
{
    const vector<int> a({7, 8, 9});
    const vector<int> b({4, 5, 6});
    const vector<int> c({1, 2, 3});
    const vector<int> z = a - (b - c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 4);
    EXPECT_EQ(z(1), 5);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing operant - vector
TEST(ops_sub, operant_vector)
{
    const vector<int> a({7, 8, 9});
    const vector<int> b({4, 5, 6});
    const vector<int> c({1, 2, 3});
    const vector<int> z = (a - b) - c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 1);
    EXPECT_EQ(z(2), 0);
}

/// \brief Testing vector - scalar
TEST(ops_sub, vector_scalar)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = a - 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), -1);
    EXPECT_EQ(z(1), 0);
    EXPECT_EQ(z(2), 1);
}

/// \brief Testing scalar - vector
TEST(ops_sub, scalar_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = 2 - a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 1);
    EXPECT_EQ(z(1), 0);
    EXPECT_EQ(z(2), -1);
}

/// \brief Testing static_vector add
TEST(ops_sub, static_vector_vector)
{
    const static_vector<int, 3> a({4, 5, 6});
    const static_vector<int, 3> b({1, 2, 3});
    const static_vector<int, 3> z = a - b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 3);
    EXPECT_EQ(z(2), 3);
}

/// \brief Testing static_vector - operant
TEST(ops_sub, static_vector_operant)
{
    const static_vector<int, 3> a({7, 8, 9});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({1, 2, 3});
    const static_vector<int, 3> z = a - (b - c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 4);
    EXPECT_EQ(z(1), 5);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing operant - static_vector
TEST(ops_sub, operant_static_vector)
{
    const static_vector<int, 3> a({7, 8, 9});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({1, 2, 3});
    const static_vector<int, 3> z = (a - b) - c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 1);
    EXPECT_EQ(z(2), 0);
}

/// \brief Testing static_vector - scalar
TEST(ops_sub, static_vector_scalar)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = a - 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), -1);
    EXPECT_EQ(z(1), 0);
    EXPECT_EQ(z(2), 1);
}

/// \brief Testing scalar - vector
TEST(ops_sub, scalar_static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = 2 - a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 1);
    EXPECT_EQ(z(1), 0);
    EXPECT_EQ(z(2), -1);
}

/// \brief Testing operant - operant
TEST(ops_sub, operant_operant)
{
    const static_vector<int, 3> a({4, 5, 6});
    const static_vector<int, 3> b({1, 2, 3});
    const static_vector<int, 3> c({10, 11, 12});
    const static_vector<int, 3> d({7, 8, 9});
    const static_vector<int, 3> z = (a - b) - (c - d);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 0);
    EXPECT_EQ(z(1), 0);
    EXPECT_EQ(z(2), 0);
}

/// \brief Testing scalar - operant
TEST(ops_sub, scalar_operant)
{
    const static_vector<int, 3> a({4, 5, 6});
    const static_vector<int, 3> b({1, 2, 3});
    const static_vector<int, 3> z = 2 - (a - b);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), -1);
    EXPECT_EQ(z(1), -1);
    EXPECT_EQ(z(2), -1);
}

/// \brief Testing operant - scalar
TEST(ops_sub, operant_scalar)
{
    const static_vector<int, 3> a({4, 5, 6});
    const static_vector<int, 3> b({1, 2, 3});
    const static_vector<int, 3> z = (a - b) - 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 1);
    EXPECT_EQ(z(1), 1);
    EXPECT_EQ(z(2), 1);
}

/// \brief Testing matrix add
TEST(ops_sub, matrix_matrix)
{
    const matrix<int> a({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> b({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = a - b;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 1);
    EXPECT_EQ(z(0, 1), 1);
    EXPECT_EQ(z(0, 2), 1);
    EXPECT_EQ(z(1, 0), 1);
    EXPECT_EQ(z(1, 1), 1);
    EXPECT_EQ(z(1, 2), 1);
}

/// \brief Testing matrix - operant
TEST(ops_sub, matrix_operant)
{
    const matrix<int> a({{3, 4, 5}, {6, 7, 8}});
    const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> c({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = a - (b - c);
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 2);
    EXPECT_EQ(z(0, 1), 3);
    EXPECT_EQ(z(0, 2), 4);
    EXPECT_EQ(z(1, 0), 5);
    EXPECT_EQ(z(1, 1), 6);
    EXPECT_EQ(z(1, 2), 7);
}

/// \brief Testing operant - matrix
TEST(ops_sub, operant_matrix)
{
    const matrix<int> a({{3, 4, 5}, {6, 7, 8}});
    const matrix<int> b({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> c({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> z = (a - b) - c;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 0);
    EXPECT_EQ(z(0, 1), -1);
    EXPECT_EQ(z(0, 2), -2);
    EXPECT_EQ(z(1, 0), -3);
    EXPECT_EQ(z(1, 1), -4);
    EXPECT_EQ(z(1, 2), -5);
}

/// \brief Testing sparse matrix sub
TEST(ops_sub, sparse_matrix)
{
    const sparse_matrix<int> a({{1}, {1}, {1, 3, 4}}, {3, 4, 5, 6, 7}, 5);
    const sparse_matrix<int> b({{0, 1}, {2}, {1, 3}}, {3, 4, 5, 6, 7}, 5);
    sparse_matrix_builder<int> c = a - b;
    EXPECT_EQ(c.rows(), 3);
    EXPECT_EQ(c.cols(), 5);

    EXPECT_EQ(c(0, 0), -3);
    EXPECT_EQ(c(0, 1), -1);
    EXPECT_EQ(c(0, 2), 0);
    EXPECT_EQ(c(0, 3), 0);
    EXPECT_EQ(c(0, 4), 0);

    EXPECT_EQ(c(1, 0), 0);
    EXPECT_EQ(c(1, 1), 4);
    EXPECT_EQ(c(1, 2), -5);
    EXPECT_EQ(c(1, 3), 0);
    EXPECT_EQ(c(1, 4), 0);

    EXPECT_EQ(c(2, 0), 0);
    EXPECT_EQ(c(2, 1), -1);
    EXPECT_EQ(c(2, 2), 0);
    EXPECT_EQ(c(2, 3), -1);
    EXPECT_EQ(c(2, 4), 7);
}

} // namespace la
