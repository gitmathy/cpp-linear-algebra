/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/matrix.cpp
/// @brief Unit tests for the dense matrix class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include <gtest/gtest.h>
#include <memory>

namespace la {

/// @brief Test default constructor for dense matrix
TEST(matrix, default_constructor)
{
    matrix<int> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    matrix<double> b;
    EXPECT_EQ(b.rows(), 0);
    EXPECT_EQ(b.cols(), 0);
    EXPECT_THROW(a(0, 0), util::error);
    EXPECT_THROW(b(0, 0), util::error);
}

/// @brief Test constructor with size and default value for dense matrix
TEST(matrix, constructor_size_default)
{
    matrix<double> a(1, 2, 1.0);
    EXPECT_EQ(a.rows(), 1);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(a(0, 1), 1.0);
    EXPECT_THROW(a(1, 0), util::error);
}

/// @brief Test constructor from initializer list
TEST(matrix, constructor_initializer)
{
    matrix<int> a({{1}, {2}});
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 1);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(1, 0), 2);
    EXPECT_THROW(a(1, 1), util::error);
    EXPECT_THROW(matrix<int>({{1}, {1, 2}}), util::error);
}

/// @brief Test move constructor
TEST(matrix, move_constructor)
{
    matrix<int> a({{1, 2}, {2, 3}, {3, 4}});
    matrix<int> dst(std::move(a));
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(dst.rows(), 3);
    EXPECT_EQ(dst.cols(), 2);
    EXPECT_EQ(dst(0, 0), 1);
    EXPECT_EQ(dst(2, 1), 4);
}

/// @brief Test copy constructor
TEST(matrix, copy_constructor)
{
    matrix<int> a({{1, 2}, {2, 3}, {3, 4}});
    matrix<int> dst(a);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(dst.rows(), 3);
    EXPECT_EQ(dst.cols(), 2);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(2, 1), 4);
    EXPECT_EQ(dst(0, 0), 1);
    EXPECT_EQ(dst(2, 1), 4);
}

/// @brief Test constructor from expression
TEST(matrix, constructor_expression)
{
    matrix<float> source({{1.0f}, {2.0f}, {3.0f}});
    expressions::operant<matrix<float>> exp(source);
    matrix<float> dst(exp);
    EXPECT_EQ(dst.rows(), 3);
    EXPECT_EQ(dst.cols(), 1);
    EXPECT_FLOAT_EQ(dst(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(dst(1, 0), 2.0f);
    EXPECT_FLOAT_EQ(dst(2, 0), 3.0f);
}

/// @brief Test constructor from matrix-matrix multiplication
TEST(matrix, constructor_mat_mult)
{
    matrix<int> a({{2, 1}}), b({{1}, {1}});
    expressions::matrix_multiply_op<matrix<int>, matrix<int>> mult(a, b);
    matrix<int> dst(mult);
    EXPECT_EQ(dst.rows(), 1);
    EXPECT_EQ(dst.cols(), 1);
    EXPECT_FLOAT_EQ(dst(0, 0), 3);
}
/// @brief Test constructor from matrix-matrix multiplication with invalid dimension
TEST(matrix, constructor_mat_mult_invalid_dim)
{
    matrix<int> a({{2, 1}}), b({{1}, {1}, {1}});
    expressions::matrix_multiply_op<matrix<int>, matrix<int>> tmp(a, b);
    EXPECT_THROW(matrix<int> c(tmp), util::error);
}

/// @brief Test destructor
TEST(matrix, destructor)
{
    matrix<float> *a = new matrix<float>(10, 10, 0.0f);
    delete a;
}

/// @brief Testing allocate
TEST(matrix, allocate)
{
    matrix<long int> a({{3, 2}});
    a.allocate(3, 2);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 6);
}

/// @brief Testing resize
TEST(matrix, resize)
{
    matrix<long int> a({{3, 2}});
    a.resize(3, 2, 1);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 6);
    EXPECT_EQ(a(2, 1), 1);
}

// rows and cols is tested in nearly all other tests, non_zeros is tested in some other tests

/// @brief Testing row idx begin
TEST(matrix, row_idx_begin)
{
    matrix<long int> a({{1, 2}, {3, 4}});
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 2);
    EXPECT_EQ(a.row_idx_begin(2), 4);
    EXPECT_THROW(a.row_idx_begin(3), util::error);
}

/// @brief Testing col idx
TEST(matrix, col_idx)
{
    matrix<long int> a({{1, 2}, {3, 4}});
    EXPECT_EQ(a.col_idx(0), 0);
    EXPECT_EQ(a.col_idx(1), 1);
    EXPECT_EQ(a.col_idx(2), 0);
    EXPECT_EQ(a.col_idx(3), 1);
    EXPECT_THROW(a.col_idx(4), util::error);
}

/// @brief Testing read and write elements
TEST(matrix, read_write)
{
    matrix<size_type> a(3, 2, 0);
    for (size_type i = 0; i < 3; ++i) {
        for (size_type j = 0; j < 2; ++j) {
            a(i, j) = i * 10 + j;
        }
    }
    for (size_type i = 0; i < 3; ++i) {
        for (size_type j = 0; j < 2; ++j) {
            EXPECT_EQ(a(i, j), i * 10 + j);
        }
    }
    for (size_type i = 0; i < 6; ++i) {
        EXPECT_EQ(a(i), (i / 2) * 10 + (i % 2));
    }
}

/// @brief Testing evaluate
TEST(matrix, evaluate)
{
    matrix<size_type> a(3, 2, 0);
    for (size_type i = 0; i < 3; ++i) {
        for (size_type j = 0; j < 2; ++j) {
            a(i, j) = i * 10 + j;
        }
    }
    for (size_type i = 0; i < 3; ++i) {
        for (size_type j = 0; j < 2; ++j) {
            EXPECT_EQ(a.evaluate(i, j), i * 10 + j);
        }
    }
    for (size_type i = 0; i < 6; ++i) {
        EXPECT_EQ(a.evaluate(i), (i / 2) * 10 + (i % 2));
    }
}

/// @brief Testing constant iterators
TEST(matrix, constant_iterators)
{
    const matrix<size_type> a({{0, 1}, {10, 11}});
    size_type i = 0;
    size_type const *val_ptr = a.vals();
    for (matrix<size_type>::citerator it = a.begin(); it != a.end(); ++it, ++i, ++val_ptr) {
        const size_type expected = (i / 2) * 10 + (i % 2);
        EXPECT_EQ(*val_ptr, expected);
        EXPECT_EQ(*it, expected);
    }
    matrix<size_type>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*row_it, 0);
    EXPECT_EQ(*(row_it + 1), 1);
    EXPECT_THROW(a.row_begin(3), util::error);
}

/// @brief Testing iterators
TEST(matrix, iterators)
{
    matrix<int> a(3, 2, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (matrix<int>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 3;
    }
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 3);
    EXPECT_EQ(a(2, 0), 2);
    EXPECT_EQ(a(2, 1), 2);
}

// Assign is already tested via the constructors (as they just call the assign)

/// @brief Testing += matrix
TEST(matrix, add_assign_matrix)
{
    matrix<size_type> a({{0, 1}, {2, 3}}), b({{4, 5}, {6, 7}});
    a += b;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), 4);
    EXPECT_EQ(a(0, 1), 6);
    EXPECT_EQ(a(1, 0), 8);
    EXPECT_EQ(a(1, 1), 10);
    EXPECT_THROW(a += matrix<size_type>(3, 3), util::error);
}

/// @brief Testing += expression
TEST(matrix, add_assign_expression)
{
    matrix<size_type> a({{0, 1}, {2, 3}});
    matrix<int> b_mat({{4, 5}, {6, 7}});
    expressions::operant<matrix<int>> b(b_mat);
    a += b;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), 4);
    EXPECT_EQ(a(0, 1), 6);
    EXPECT_EQ(a(1, 0), 8);
    EXPECT_EQ(a(1, 1), 10);
    a.resize(1, 1);
    EXPECT_THROW(a += b, util::error);
}

/// @brief Testing *= scalar
TEST(matrix, mult_assign_matrix)
{
    matrix<int> a({{0, 1}, {2, 3}});
    a *= 2;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), 0);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 4);
    EXPECT_EQ(a(1, 1), 6);
}

/// @brief Testing *= expression
TEST(matrix, mult_assign_expression)
{
    matrix<size_type> a({{0, 1}, {2, 3}});
    matrix<size_type> b_mat({{4, 5}, {6, 7}});
    expressions::operant<matrix<size_type>> b(b_mat);
    a *= b;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), 6);
    EXPECT_EQ(a(0, 1), 7);
    EXPECT_EQ(a(1, 0), 26);
    EXPECT_EQ(a(1, 1), 31);
    a.resize(1, 1);
    EXPECT_THROW(a *= b, util::error);
}

/// @brief Testing -= matrix
TEST(matrix, sub_assign_matrix)
{
    matrix<int> a({{0, 1}, {2, 3}}), b({{4, 5}, {6, 7}});
    a -= b;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), -4);
    EXPECT_EQ(a(0, 1), -4);
    EXPECT_EQ(a(1, 0), -4);
    EXPECT_EQ(a(1, 1), -4);
    EXPECT_THROW(a -= matrix<int>(3, 3), util::error);
}

/// @brief Testing -= expression
TEST(matrix, sub_assign_expression)
{
    matrix<int> a({{0, 1}, {2, 3}});
    matrix<int> b_mat({{4, 5}, {6, 7}});
    expressions::operant<matrix<int>> b(b_mat);
    a -= b;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_EQ(a(0, 0), -4);
    EXPECT_EQ(a(0, 1), -4);
    EXPECT_EQ(a(1, 0), -4);
    EXPECT_EQ(a(1, 1), -4);
    a.resize(1, 1);
    EXPECT_THROW(a -= b, util::error);
}

/// @brief Testing row_multiply
TEST(matrix, row_multiply)
{
    matrix<int> a({{4, 5}, {6, 7}});
    vector<int> x_vec({2, 3});
    expressions::operant<vector<int>> x(x_vec);

    EXPECT_EQ(a.row_multiply(x, 0), 23);
    EXPECT_EQ(a.row_multiply(x, 1), 33);
    EXPECT_THROW(a.row_multiply(x, 3), util::error);
    a.resize(3, 3);
    EXPECT_THROW(a.row_multiply(x, 0), util::error);
}

/// @brief Testing apply func
TEST(matrix, apply_func)
{
    matrix<double> a({{0, 1}, {2, 3}});
    a.apply_func([](auto x) { return x * x; });
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_DOUBLE_EQ(a(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(a(0, 1), 1.0);
    EXPECT_DOUBLE_EQ(a(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(a(1, 1), 9.0);
}

/// @brief Testing read and write to binary file
TEST(matrix, read_write_bin)
{
    const std::string filename = "tmp_read_bin_matrix.tst";
    matrix<double> a({{3.14, 2.718}, {0, 1}}), b;
    a.to_file(filename, true);
    b.from_file(filename, true);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 0), 0);
    EXPECT_DOUBLE_EQ(b(1, 1), 1);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write to text file
TEST(matrix, read_wite_txt)
{
    const std::string filename = "tmp_read_txt_matrix.tst";
    matrix<double> a({{3.14, 2.718}, {0, 1}}), b;
    a.to_file(filename, false);
    b.from_file(filename, false);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 0), 0);
    EXPECT_DOUBLE_EQ(b(1, 1), 1);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", false), util::error);
}

} // namespace la
