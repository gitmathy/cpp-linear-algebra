
#include "pch.h"

#include "la/sparse"
#include <gtest/gtest.h>
#include <memory>
#include <utility>

namespace la {

/// @brief Test constructor for sparse matrix builder
TEST(sparse_matrix_builder, constructor)
{
    sparse_matrix_builder<int> a(3, 4);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 4);
    EXPECT_EQ(a.non_zeros(), 0);
}

/// @brief Test constructor for sparse matrix builder
TEST(sparse_matrix_builder, constructor_from_expr)
{
    sparse_matrix<int> A({{0, 1}, {2}}, {3, 4, 5}, 3);
    expressions::operant<sparse_matrix<int>> expr(A);
    sparse_matrix_builder<int> a_exp = expr;
    const sparse_matrix_builder<int> &a = a_exp;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 3);
    EXPECT_EQ(a(0, 1), 4);
    EXPECT_EQ(a(0, 2), 0);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 0);
    EXPECT_EQ(a(1, 2), 5);
}

/// @brief Test allocate
TEST(sparse_matrix_builder, allocate)
{
    sparse_matrix_builder<int> a(1, 1);
    a.allocate(2, 3);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 0);
}

// rows(), cols(), non_zeros() are tested in almost every test

/// @brief Testing read and write elements
TEST(sparse_matrix_builder, read_write_operator)
{
    sparse_matrix_builder<int> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    const sparse_matrix_builder<int> &a_const = a;
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a_const(0, 0), 2);
    EXPECT_EQ(a_const(0, 1), 3);
    EXPECT_EQ(a_const(0, 2), 0);
    EXPECT_EQ(a_const(1, 0), 0);
    EXPECT_EQ(a_const(1, 1), 0);
    EXPECT_EQ(a_const(1, 2), 4);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_THROW(a(0, 3) = 3, util::error);
    EXPECT_THROW(a(2, 0), util::error);
}

/// @brief Testing move
TEST(sparse_matrix_builder, move)
{
    sparse_matrix_builder<int> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    sparse_matrix<int> A;
    a.move(A);
    const sparse_matrix<int> &A_const = A;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(a.non_zeros(), 0);
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(A_const(0, 0), 2);
    EXPECT_EQ(A_const(0, 1), 3);
    EXPECT_EQ(A_const(0, 2), 0);
    EXPECT_EQ(A_const(1, 0), 0);
    EXPECT_EQ(A_const(1, 1), 0);
    EXPECT_EQ(A_const(1, 2), 4);
}

/// @brief Testing assemble
TEST(sparse_matrix_builder, assemble)
{
    sparse_matrix_builder<int> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    sparse_matrix<int> A = a.assemble();
    const sparse_matrix<int> A_const = A;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(A_const(0, 0), 2);
    EXPECT_EQ(A_const(0, 1), 3);
    EXPECT_EQ(A_const(0, 2), 0);
    EXPECT_EQ(A_const(1, 0), 0);
    EXPECT_EQ(A_const(1, 1), 0);
    EXPECT_EQ(A_const(1, 2), 4);
}

} // namespace la
