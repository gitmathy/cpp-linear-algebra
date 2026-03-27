/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations_mult.cpp
/// @brief Unit tests for multiply operations
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
TEST(ops_mul, vector_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> z = a * b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 4);
    EXPECT_EQ(z(1), 10);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing vector * operant
TEST(ops_mul, vector_operant)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({7, 8, 9});
    const vector<int> z = a * (b * c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 28);
    EXPECT_EQ(z(1), 80);
    EXPECT_EQ(z(2), 162);
}

/// \brief Testing operant * vector
TEST(ops_mul, operant_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({7, 8, 9});
    const vector<int> z = (a * b) * c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 28);
    EXPECT_EQ(z(1), 80);
    EXPECT_EQ(z(2), 162);
}

/// \brief Testing vector * scalar
TEST(ops_mul, vector_scalar)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = a * 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing scalar * vector
TEST(ops_mul, scalar_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> z = 2 * a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing static_vector
TEST(ops_mul, static_vector_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = a * b;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 4);
    EXPECT_EQ(z(1), 10);
    EXPECT_EQ(z(2), 18);
}

/// \brief Testing static_vector * operant
TEST(ops_mul, static_vector_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> z = a * (b * c);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 28);
    EXPECT_EQ(z(1), 80);
    EXPECT_EQ(z(2), 162);
}

/// \brief Testing operant * static_vector
TEST(ops_mul, operant_static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> z = (a * b) * c;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 28);
    EXPECT_EQ(z(1), 80);
    EXPECT_EQ(z(2), 162);
}

/// \brief Testing static_vector * scalar
TEST(ops_mul, static_vector_scalar)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = a * 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing scalar * vector
TEST(ops_mul, scalar_static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> z = 2 * a;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 2);
    EXPECT_EQ(z(1), 4);
    EXPECT_EQ(z(2), 6);
}

/// \brief Testing operant * operant
TEST(ops_mul, operant_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> c({7, 8, 9});
    const static_vector<int, 3> d({10, 11, 12});
    const static_vector<int, 3> z = (a * b) * (c * d);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 280);
    EXPECT_EQ(z(1), 880);
    EXPECT_EQ(z(2), 1944);
}

/// \brief Testing scalar * operant
TEST(ops_mul, scalar_operant)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = 2 * (a * b);
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 8);
    EXPECT_EQ(z(1), 20);
    EXPECT_EQ(z(2), 36);
}

/// \brief Testing operant * scalar
TEST(ops_mul, operant_scalar)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});
    const static_vector<int, 3> z = (a * b) * 2;
    EXPECT_EQ(z.rows(), 3);

    EXPECT_EQ(z(0), 8);
    EXPECT_EQ(z(1), 20);
    EXPECT_EQ(z(2), 36);
}

/// \brief Testing matrix
TEST(ops_mul, matrix_matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> b({{2, 3}, {4, 5}, {6, 7}});
    const matrix<int> z = a * b;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 2);

    EXPECT_EQ(z(0, 0), 28);
    EXPECT_EQ(z(0, 1), 34);
    EXPECT_EQ(z(1, 0), 64);
    EXPECT_EQ(z(1, 1), 79);
}

// /// \brief Testing matrix * operant
// TEST(ops_mul, matrix_operant)
// {
//     const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
//     const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
//     const matrix<int> c({{2, 2}, {2, 2}});
//     const matrix<int> z = a * (b * c);
//     EXPECT_EQ(z.rows(), 2);
//     EXPECT_EQ(z.cols(), 2);

//     EXPECT_EQ(z(0, 0), 180);
//     EXPECT_EQ(z(0, 1), 180);
//     EXPECT_EQ(z(1, 0), 414);
//     EXPECT_EQ(z(1, 1), 414);
// }

// /// \brief Testing operant * matrix
// TEST(ops_mul, operant_matrix)
// {
//     const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
//     const matrix<int> b({{2, 3, 4}, {5, 6, 7}});
//     const matrix<int> c({{3, 4, 5}, {6, 7, 8}});
//     const matrix<int> z = (a * b) * c;
//     EXPECT_EQ(z.rows(), 2);
//     EXPECT_EQ(z.cols(), 3);

//     EXPECT_EQ(z(0, 0), 180);
//     EXPECT_EQ(z(0, 1), 180);
//     EXPECT_EQ(z(1, 0), 414);
//     EXPECT_EQ(z(1, 1), 414);
// }

/// \brief Testing matrix * scalar
TEST(ops_mul, matrix_scalar)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = a * 2;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);

    EXPECT_EQ(z(0, 0), 2);
    EXPECT_EQ(z(0, 1), 4);
    EXPECT_EQ(z(0, 2), 6);
    EXPECT_EQ(z(1, 0), 8);
    EXPECT_EQ(z(1, 1), 10);
    EXPECT_EQ(z(1, 2), 12);
}

/// \brief Testing scalar * matrix
TEST(ops_mul, scalar_matrix)
{
    const matrix<int> a({{1, 2, 3}, {4, 5, 6}});
    const matrix<int> z = 2 * a;
    EXPECT_EQ(z.rows(), 2);
    EXPECT_EQ(z.cols(), 3);
    EXPECT_EQ(z(0, 0), 2);
    EXPECT_EQ(z(0, 1), 4);
    EXPECT_EQ(z(0, 2), 6);
    EXPECT_EQ(z(1, 0), 8);
    EXPECT_EQ(z(1, 1), 10);
    EXPECT_EQ(z(1, 2), 12);
}

/// \brief Testing sparse matrix transposed multiply
TEST(ops_mul, sparse_matrix_transpose_multiply)
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
