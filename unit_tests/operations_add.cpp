/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations_add.cpp
/// @brief Unit tests for add operations
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
TEST(ops_add, vector_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> z = a + b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 5);
    EXPECT_EQ(z(1), 7);
    EXPECT_EQ(z(2), 9);
}

/// \brief Testing vector + operant
TEST(ops_add, vector_operant)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({7, 8, 9});
    const vector<int> z = a + (b + c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 12);
    EXPECT_EQ(z(1), 15);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing operant + vector
TEST(ops_add, operant_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({7, 8, 9});
    const vector<int> z = (a + b) + c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 12);
    EXPECT_EQ(z(1), 15);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing vector + scalar
TEST(ops_add, vector_scalar)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = a + 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 5);
}

/// \brief Testing scalar + vector
TEST(ops_add, scalar_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = 2 + a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 5);
}

/// \brief Testing static_vector add
TEST(ops_add, static_vector_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = a + b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 5);
    EXPECT_EQ(z(1), 7);
    EXPECT_EQ(z(2), 9);
}

/// \brief Testing static_vector + operant
TEST(ops_add, static_vector_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> z = a + (b + c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 12);
    EXPECT_EQ(z(1), 15);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing operant + static_vector
TEST(ops_add, operant_static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> z = (a + b) + c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 12);
    EXPECT_EQ(z(1), 15);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing static_vector + scalar
TEST(ops_add, static_vector_scalar)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = a + 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 5);
}

/// \brief Testing scalar + vector
TEST(ops_add, scalar_static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = 2 + a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 3);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 5);
}

/// \brief Testing operant + operant
TEST(ops_add, operant_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> d({10, 11, 12});
    const static_vector<int, 3> z = (a + b) + (c + d);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 22);
    EXPECT_EQ(z(1), 26);
    EXPECT_EQ(z(2), 30);
}

/// \brief Testing scalar + operant
TEST(ops_add, scalar_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = 2 + (a + b);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 7);
    EXPECT_EQ(z(1), 9);
    EXPECT_EQ(z(2), 11);
}

/// \brief Testing operant + scalar
TEST(ops_add, operant_scalar)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = (a + b) + 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 7);
    EXPECT_EQ(z(1), 9);
    EXPECT_EQ(z(2), 11);
}

/// \brief Testing matrix add
TEST(ops_add, matrix_matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> z = a + b;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 3);
    EXPECT_EQ(z(0, 1), 5);
    EXPECT_EQ(z(0, 2), 7);
    EXPECT_EQ(z(1, 0), 9);
    EXPECT_EQ(z(1, 1), 11);
    EXPECT_EQ(z(1, 2), 13);
}

/// \brief Testing matrix + operant
TEST(ops_add, matrix_operant)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> c({{3, 4, 5}, {6, 7, 8}});
    const matrix<int> z = a + (b + c);
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 6);
    EXPECT_EQ(z(0, 1), 9);
    EXPECT_EQ(z(0, 2), 12);
    EXPECT_EQ(z(1, 0), 15);
    EXPECT_EQ(z(1, 1), 18);
    EXPECT_EQ(z(1, 2), 21);
}

/// \brief Testing operant + matrix
TEST(ops_add, operant_matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
    const matrix<int> c({{3, 4, 5}, {6, 7, 8}});
    const matrix<int> z = (a + b) + c;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 6);
    EXPECT_EQ(z(0, 1), 9);
    EXPECT_EQ(z(0, 2), 12);
    EXPECT_EQ(z(1, 0), 15);
    EXPECT_EQ(z(1, 1), 18);
    EXPECT_EQ(z(1, 2), 21);
}

/// \brief Testing matrix + scalar
TEST(ops_add, matrix_scalar)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = a + 2;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 3);
    EXPECT_EQ(z(0, 1), 4);
    EXPECT_EQ(z(0, 2), 5);
    EXPECT_EQ(z(1, 0), 6);
    EXPECT_EQ(z(1, 1), 7);
    EXPECT_EQ(z(1, 2), 8);
}

/// \brief Testing scalar + matrix
TEST(ops_add, scalar_matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = 2 + a;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);
    EXPECT_EQ(z(0, 0), 3);
    EXPECT_EQ(z(0, 1), 4);
    EXPECT_EQ(z(0, 2), 5);
    EXPECT_EQ(z(1, 0), 6);
    EXPECT_EQ(z(1, 1), 7);
    EXPECT_EQ(z(1, 2), 8);
}

/// \brief Testing sparse matrix add
TEST(ops_add, sparse_matrix_add)
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

} // namespace la
