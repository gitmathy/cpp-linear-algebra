/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/triangular_matrix.cpp
/// @brief Unit tests for the dense triangular matrix class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include <gtest/gtest.h>
#include <memory>

namespace la {

/// @brief Test default constructor for lower triangular matrix
TEST(triangular_matrix, default_constructor_lower)
{
    triang_matrix<int, true> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(a.non_zeros(), 0);

    triang_matrix<double, true> b;
    EXPECT_EQ(b.rows(), 0);
    EXPECT_EQ(b.cols(), 0);
    EXPECT_EQ(b.non_zeros(), 0);
}

/// @brief Test default constructor for upper triangular matrix
TEST(triangular_matrix, default_constructor_upper)
{
    triang_matrix<int, false> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(a.non_zeros(), 0);

    triang_matrix<double, true> b;
    EXPECT_EQ(b.rows(), 0);
    EXPECT_EQ(b.cols(), 0);
    EXPECT_EQ(b.non_zeros(), 0);
}

/// @brief Test constructor lower square triangular matrix
TEST(triangular_matrix, constructor_square_lower)
{
    triang_matrix<double, true> a_build(2, 2, 1.0);
    const triang_matrix<double, true> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 0.);
    EXPECT_DOUBLE_EQ(a(1, 0), 1.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
    EXPECT_EQ(a.non_zeros(), 3);
}

/// @brief Test constructor lower "tall" triangular matrix
TEST(triangular_matrix, constructor_tall_lower)
{
    triang_matrix<double, true> a_build(3, 2, 1.0);
    const triang_matrix<double, true> &a = a_build;
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 5);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 0.);
    EXPECT_DOUBLE_EQ(a(1, 0), 1.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
    EXPECT_DOUBLE_EQ(a(2, 0), 1.);
    EXPECT_DOUBLE_EQ(a(2, 1), 1.);
}

/// @brief Test constructor lower "wide" triangular matrix
TEST(triangular_matrix, constructor_wide_lower)
{
    triang_matrix<double, true> a_build(2, 3, 1.0);
    const triang_matrix<double, true> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 0.);
    EXPECT_DOUBLE_EQ(a(0, 2), 0.);
    EXPECT_DOUBLE_EQ(a(1, 0), 1.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
    EXPECT_DOUBLE_EQ(a(1, 2), 0.);
    EXPECT_THROW(a(1, 3), util::boundary_error);
}

/// @brief Test constructor upper square triangular matrix
TEST(triangular_matrix, constructor_square_upper)
{
    triang_matrix<double, false> a_build(2, 2, 1.0);
    const triang_matrix<double, false> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 1.);
    EXPECT_DOUBLE_EQ(a(1, 0), 0.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
}

/// @brief Test constructor upper "tall" triangular matrix
TEST(triangular_matrix, constructor_tall_upper)
{
    triang_matrix<double, false> a_build(3, 2, 1.0);
    const triang_matrix<double, false> &a = a_build;
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 1.);
    EXPECT_DOUBLE_EQ(a(1, 0), 0.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
    EXPECT_DOUBLE_EQ(a(2, 0), 0.);
    EXPECT_DOUBLE_EQ(a(2, 1), 0.);
}

/// @brief Test constructor upper "wide" triangular matrix
TEST(triangular_matrix, constructor_wide_upper)
{
    triang_matrix<double, false> a_build(2, 3, 1.0);
    const triang_matrix<double, false> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 5);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.);
    EXPECT_DOUBLE_EQ(a(0, 1), 1.);
    EXPECT_DOUBLE_EQ(a(0, 2), 1.);
    EXPECT_DOUBLE_EQ(a(1, 0), 0.);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.);
    EXPECT_DOUBLE_EQ(a(1, 2), 1.);
    EXPECT_THROW(a(1, 3), util::boundary_error);
}

/// @brief Test initializer constructor lower square triangular matrix
TEST(triangular_matrix, constructor_initializer_square_lower)
{
    triang_matrix<int, true> a_build({{1}, {1, 2}});
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 1);
    EXPECT_EQ(a(1, 1), 2);
    EXPECT_THROW((triang_matrix<int, true>({{1, 2}, {1, 2}})), util::shape_error);
    EXPECT_THROW((triang_matrix<int, true>({{1, 2}, {1}})), util::shape_error);
}

/// @brief Test initializer constructor lower "tall" triangular matrix
TEST(triangular_matrix, constructor_initializer_tall_lower)
{
    triang_matrix<int, true> a_build({{1}, {1, 2}, {1, 2}});
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 5);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 1);
    EXPECT_EQ(a(1, 1), 2);
    EXPECT_EQ(a(2, 0), 1);
    EXPECT_EQ(a(2, 1), 2);
    EXPECT_THROW((triang_matrix<int, true>({{1}, {1, 2}, {1}})), util::shape_error);
}

/// @brief Test initializer constructor upper square triangular matrix
TEST(triangular_matrix, constructor_initializer_square_upper)
{
    triang_matrix<int, false> a_build({{1, 2}, {1}});
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 1);

    EXPECT_THROW((triang_matrix<int, false>({{1, 2}, {1, 2}})), util::shape_error);
    EXPECT_THROW((triang_matrix<int, false>({{1}, {1, 2}})), util::shape_error);
}

/// @brief Test initializer constructor upper "wide" triangular matrix
TEST(triangular_matrix, constructor_initializer_tall_upper)
{
    triang_matrix<int, false> a_build({{1, 2, 3}, {1, 2}});
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 5);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(0, 2), 3);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 1);
    EXPECT_EQ(a(1, 2), 2);
    EXPECT_THROW((triang_matrix<int, false>({{1, 2, 3}, {1, 2, 3}})), util::shape_error);
}

/// @brief Test copy constructor lower square triangular matrix
TEST(triangular_matrix, constructor_copy_square_lower)
{
    triang_matrix<int, true> a_build({{1}, {1, 2}});
    const triang_matrix<int, true> a(a_build);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 1);
    EXPECT_EQ(a(1, 1), 2);
}

/// @brief Test copy constructor upper square triangular matrix
TEST(triangular_matrix, constructor_copy_square_upper)
{
    triang_matrix<int, false> a_build({{1, 2}, {1}});
    const triang_matrix<int, false> a(a_build);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 1);
}

/// @brief Test move constructor lower square triangular matrix
TEST(triangular_matrix, constructor_move_square_lower)
{
    triang_matrix<int, true> a_build({{1}, {1, 2}});
    const triang_matrix<int, true> a(std::move(a_build));
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 1);
    EXPECT_EQ(a(1, 1), 2);
    EXPECT_EQ(a_build.rows(), 0);
    EXPECT_EQ(a_build.cols(), 0);
    EXPECT_EQ(a_build.non_zeros(), 0);
}

/// @brief Test move constructor upper square triangular matrix
TEST(triangular_matrix, constructor_move_square_upper)
{
    triang_matrix<int, false> a_build({{1, 2}, {1}});
    const triang_matrix<int, false> a(std::move(a_build));
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 1);
    EXPECT_EQ(a_build.rows(), 0);
    EXPECT_EQ(a_build.cols(), 0);
    EXPECT_EQ(a_build.non_zeros(), 0);
}

// rows, cols, non_zeros and get_idx is tested in nearly all other tests

/// @brief Test get_row_idx lower square triangular matrix
TEST(triangular_matrix, get_row_idx_square_lower)
{
    triang_matrix<int, true> a_build({{1}, {1, 2}});
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 1);
    EXPECT_EQ(a.row_idx_begin(2), 3);
}

/// @brief Test get_row_idx lower "tall" triangular matrix
TEST(triangular_matrix, get_row_idx_tall_lower)
{
    triang_matrix<int, true> a_build(4, 2);
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 1);
    EXPECT_EQ(a.row_idx_begin(2), 3);
    EXPECT_EQ(a.row_idx_begin(3), 5);
}

/// @brief Test get_row_idx lower "wide" triangular matrix
TEST(triangular_matrix, get_row_idx_wide_lower)
{
    triang_matrix<int, true> a_build(2, 3);
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 1);
    EXPECT_EQ(a.row_idx_begin(2), 3);
}

/// @brief Test move constructor upper square triangular matrix
TEST(triangular_matrix, get_row_idx_square_upper)
{
    triang_matrix<int, false> a_build({{1, 2}, {1}});
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 2);
    EXPECT_EQ(a.row_idx_begin(2), 3);
}

/// @brief Test get_row_idx upper "tall" triangular matrix
TEST(triangular_matrix, get_row_idx_tall_upper)
{
    triang_matrix<int, false> a_build(4, 2);
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 2);
    EXPECT_EQ(a.row_idx_begin(2), 3);
    EXPECT_EQ(a.row_idx_begin(3), 3);
}

/// @brief Test get_row_idx upper "wide" triangular matrix
TEST(triangular_matrix, get_row_idx_wide_upper)
{
    triang_matrix<int, false> a_build(2, 3);
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 3);
    EXPECT_EQ(a.row_idx_begin(2), 5);
}

// read element access via () is tested in nearly all tests

/// @brief Test write access operator for lower square triangular matrix
TEST(triangular_matrix, write_access_square_lower)
{
    triang_matrix<int, true> a_build(2, 2, 1);
    a_build(0, 0) = 2;
    a_build(1, 0) = 3;
    a_build(1, 1) = 4;
    EXPECT_THROW((a_build(0, 1) = 1), util::boundary_error);
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 4);
    EXPECT_THROW((a_build(2, 2) = 1), util::boundary_error);
}

/// @brief Test write access operator for lower "tall" triangular matrix
TEST(triangular_matrix, write_access_tall_lower)
{
    triang_matrix<int, true> a_build(3, 2, 1);
    a_build(0, 0) = 2;
    a_build(1, 0) = 3;
    a_build(1, 1) = 4;
    a_build(2, 0) = 5;
    a_build(2, 1) = 6;
    EXPECT_THROW((a_build(0, 1) = 1), util::boundary_error);
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 4);
    EXPECT_EQ(a(2, 0), 5);
    EXPECT_EQ(a(2, 1), 6);
}

/// @brief Test write access operator for lower "wide" triangular matrix
TEST(triangular_matrix, write_access_wide_lower)
{
    triang_matrix<int, true> a_build(2, 3, 1);
    a_build(0, 0) = 2;
    a_build(1, 0) = 3;
    a_build(1, 1) = 4;
    EXPECT_THROW((a_build(0, 1) = 1), util::boundary_error);
    EXPECT_THROW((a_build(0, 2) = 1), util::boundary_error);
    EXPECT_THROW((a_build(1, 2) = 1), util::boundary_error);
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 4);
}

/// @brief Test write access operator for upper square triangular matrix
TEST(triangular_matrix, write_access_square_upper)
{
    triang_matrix<int, false> a_build(2, 2, 1);
    a_build(0, 0) = 2;
    a_build(0, 1) = 3;
    a_build(1, 1) = 4;
    EXPECT_THROW((a_build(1, 0) = 1), util::boundary_error);
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 3);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 4);
    EXPECT_THROW((a_build(2, 2) = 1), util::boundary_error);
}

/// @brief Test write access operator for upper "tall" triangular matrix
TEST(triangular_matrix, write_access_tall_upper)
{
    triang_matrix<int, false> a_build(3, 2, 1);
    a_build(0, 0) = 2;
    a_build(0, 1) = 3;
    a_build(1, 1) = 4;
    EXPECT_THROW((a_build(1, 0) = 1), util::boundary_error);
    EXPECT_THROW((a_build(2, 0) = 1), util::boundary_error);
    EXPECT_THROW((a_build(2, 1) = 1), util::boundary_error);
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 3);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 4);
    EXPECT_EQ(a(2, 0), 0);
    EXPECT_EQ(a(2, 1), 0);
}

/// @brief Test write access operator for upper "wide" triangular matrix
TEST(triangular_matrix, write_access_wide_upper)
{
    triang_matrix<int, false> a_build(2, 3, 1);
    a_build(0, 0) = 2;
    a_build(0, 1) = 3;
    a_build(0, 2) = 4;
    a_build(1, 1) = 5;
    a_build(1, 2) = 6;
    EXPECT_THROW((a_build(1, 0) = 1), util::boundary_error);
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 3);
    EXPECT_EQ(a(0, 2), 4);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 5);
    EXPECT_EQ(a(1, 2), 6);
}

/// @brief Testing constant iterators for lower square triangular matrix
TEST(triangular_matrix, constant_iterators_square_lower)
{
    const triang_matrix<size_type, true> a({{0}, {1, 2}});
    size_type i = 0;
    size_type const *val_ptr = a.vals();
    for (triang_matrix<size_type, true>::citerator it = a.begin(); it != a.end();
         ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*it, i);
        EXPECT_EQ(*val_ptr, i);
    }
    triang_matrix<size_type, true>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 0);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(1));
    EXPECT_THROW(a.row_begin(2), util::boundary_error);
}

/// @brief Testing constant iterators for lower "tall" triangular matrix
TEST(triangular_matrix, constant_iterators_tall_lower)
{
    const triang_matrix<size_type, true> a({{0}, {1, 2}, {3, 4}});
    size_type i = 0;
    size_type const *val_ptr = a.vals();
    for (triang_matrix<size_type, true>::citerator it = a.begin(); it != a.end();
         ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*it, i);
        EXPECT_EQ(*val_ptr, i);
    }
    triang_matrix<size_type, true>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 0);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(1));
    row_it = a.row_begin(2);
    EXPECT_EQ(*(row_it++), 3);
    EXPECT_EQ(*(row_it++), 4);
    EXPECT_EQ(row_it, a.row_end(2));
    EXPECT_THROW(a.row_begin(3), util::boundary_error);
}

/// @brief Testing constant iterators for lower "wide" triangular matrix
TEST(triangular_matrix, constant_iterators_wide_lower)
{
    const triang_matrix<size_type, true> a(2, 3, 2);
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());
    triang_matrix<size_type, true>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(1));
    EXPECT_THROW(a.row_begin(2), util::boundary_error);
}

/// @brief Testing constant iterators for upper square triangular matrix
TEST(triangular_matrix, constant_iterators_square_upper)
{
    const triang_matrix<size_type, false> a({{0, 1}, {2}});
    size_type i = 0;
    size_type const *val_ptr = a.vals();
    for (triang_matrix<size_type, false>::citerator it = a.begin(); it != a.end();
         ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*it, i);
        EXPECT_EQ(*val_ptr, i);
    }
    triang_matrix<size_type, false>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 0);
    EXPECT_EQ(*(row_it++), 1);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(1));
    EXPECT_THROW(a.row_begin(2), util::boundary_error);
}

/// @brief Testing constant iterators for upper "tall" triangular matrix
TEST(triangular_matrix, constant_iterators_tall_upper)
{
    const triang_matrix<size_type, false> a(3, 2, 2);
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());
    triang_matrix<size_type, false>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(1));
    row_it = a.row_begin(2);
    EXPECT_EQ(row_it, a.row_end(2));
    EXPECT_THROW(a.row_begin(3), util::boundary_error);
}

/// @brief Testing constant iterators for upper "wide" triangular matrix
TEST(triangular_matrix, constant_iterators_wide_upper)
{
    const triang_matrix<size_type, false> a({{0, 1, 2}, {3, 4}});
    size_type i = 0;
    size_type const *val_ptr = a.vals();
    for (triang_matrix<size_type, false>::citerator it = a.begin(); it != a.end();
         ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*it, i);
        EXPECT_EQ(*val_ptr, i);
    }
    triang_matrix<size_type, false>::citerator row_it = a.row_begin(0);
    EXPECT_EQ(*(row_it++), 0);
    EXPECT_EQ(*(row_it++), 1);
    EXPECT_EQ(*(row_it++), 2);
    EXPECT_EQ(row_it, a.row_end(0));
    row_it = a.row_begin(1);
    EXPECT_EQ(*(row_it++), 3);
    EXPECT_EQ(*(row_it++), 4);
    EXPECT_EQ(row_it, a.row_end(1));
    EXPECT_THROW(a.row_begin(2), util::boundary_error);
}

/// @brief Testing iterator for lower square triangular matrix
TEST(triangular_matrix, iterators_square_lower)
{
    triang_matrix<int, true> a(2, 2, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, true>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 3;
    }
    const triang_matrix<int, true> &b = a;
    EXPECT_EQ(b(0, 0), 2);
    EXPECT_EQ(b(0, 1), 0);
    EXPECT_EQ(b(1, 0), 3);
    EXPECT_EQ(b(1, 1), 3);
}

/// @brief Testing iterator for lower "tall" triangular matrix
TEST(triangular_matrix, iterators_tall_lower)
{
    triang_matrix<int, true> a(3, 2, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, true>::iterator it = a.row_begin(0); it != a.row_end(0); ++it) {
        *it = 3;
    }
    for (triang_matrix<int, true>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 4;
    }
    for (triang_matrix<int, true>::iterator it = a.row_begin(2); it != a.row_end(2); ++it) {
        *it = 5;
    }
    const triang_matrix<int, true> &b = a;
    EXPECT_EQ(b(0, 0), 3);
    EXPECT_EQ(b(0, 1), 0);
    EXPECT_EQ(b(1, 0), 4);
    EXPECT_EQ(b(1, 1), 4);
    EXPECT_EQ(b(2, 0), 5);
    EXPECT_EQ(b(2, 1), 5);
}

/// @brief Testing iterator for lower "wide" triangular matrix
TEST(triangular_matrix, iterators_wide_lower)
{
    triang_matrix<int, true> a(2, 3, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, true>::iterator it = a.row_begin(0); it != a.row_end(0); ++it) {
        *it = 3;
    }
    for (triang_matrix<int, true>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 4;
    }
    const triang_matrix<int, true> &b = a;
    EXPECT_EQ(b(0, 0), 3);
    EXPECT_EQ(b(0, 1), 0);
    EXPECT_EQ(b(0, 2), 0);
    EXPECT_EQ(b(1, 0), 4);
    EXPECT_EQ(b(1, 1), 4);
    EXPECT_EQ(b(1, 2), 0);
}

/// @brief Testing iterator for upper square triangular matrix
TEST(triangular_matrix, iterators_square_upper)
{
    triang_matrix<int, false> a(2, 2, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, false>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 3;
    }
    const triang_matrix<int, false> &b = a;
    EXPECT_EQ(b(0, 0), 2);
    EXPECT_EQ(b(0, 1), 2);
    EXPECT_EQ(b(1, 0), 0);
    EXPECT_EQ(b(1, 1), 3);
}

/// @brief Testing iterator for upper "tall" triangular matrix
TEST(triangular_matrix, iterators_tall_upper)
{
    triang_matrix<int, false> a(3, 2, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, false>::iterator it = a.row_begin(0); it != a.row_end(0); ++it) {
        *it = 3;
    }
    for (triang_matrix<int, false>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 4;
    }
    for (triang_matrix<int, false>::iterator it = a.row_begin(2); it != a.row_end(2); ++it) {
        *it = 5;
    }
    const triang_matrix<int, false> &b = a;
    EXPECT_EQ(b(0, 0), 3);
    EXPECT_EQ(b(0, 1), 3);
    EXPECT_EQ(b(1, 0), 0);
    EXPECT_EQ(b(1, 1), 4);
    EXPECT_EQ(b(2, 0), 0);
    EXPECT_EQ(b(2, 1), 0);
}

/// @brief Testing iterator for upper "wide" triangular matrix
TEST(triangular_matrix, iterators_wide_upper)
{
    triang_matrix<int, false> a(2, 3, 1);
    for (matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(a.begin(), a.end(), [](auto b) { return b != 2; }), a.end());

    for (triang_matrix<int, false>::iterator it = a.row_begin(0); it != a.row_end(0); ++it) {
        *it = 3;
    }
    for (triang_matrix<int, false>::iterator it = a.row_begin(1); it != a.row_end(1); ++it) {
        *it = 4;
    }
    const triang_matrix<int, false> &b = a;
    EXPECT_EQ(b(0, 0), 3);
    EXPECT_EQ(b(0, 1), 3);
    EXPECT_EQ(b(0, 2), 3);
    EXPECT_EQ(b(1, 0), 0);
    EXPECT_EQ(b(1, 1), 4);
    EXPECT_EQ(b(1, 2), 4);
}

/// @brief Testing apply for lower square triangular matrix
TEST(triangular_matrix, apply_square_lower)
{
    triang_matrix<int, true> a_build(2, 2, 2);
    a_build.apply_func([](const int &x) { return x * x; });
    const triang_matrix<int, true> &a = a_build;
    EXPECT_EQ(a(0, 0), 4);
    EXPECT_EQ(a(0, 1), 0);
    EXPECT_EQ(a(1, 0), 4);
    EXPECT_EQ(a(1, 1), 4);
}

/// @brief Testing apply for upper square triangular matrix
TEST(triangular_matrix, apply_square_upper)
{
    triang_matrix<int, false> a_build(2, 2, 2);
    a_build.apply_func([](const int &x) { return x * x; });
    const triang_matrix<int, false> &a = a_build;
    EXPECT_EQ(a(0, 0), 4);
    EXPECT_EQ(a(0, 1), 4);
    EXPECT_EQ(a(1, 0), 0);
    EXPECT_EQ(a(1, 1), 4);
}

/// @brief Testing read and write of lower square triangular to binary file
TEST(triangular_matrix, read_write_bin_square_lower)
{
    const std::string filename = "tmp_read_bin_triangular_lower_matrix.tst";
    triang_matrix<double, true> a({{3.14}, {2.718, 1.618}}), b_build;
    a.to_file(filename, true);
    b_build.from_file(filename, true);
    const triang_matrix<double, true> &b = b_build;
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 0);
    EXPECT_DOUBLE_EQ(b(1, 0), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 1), 1.618);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write of upper square triangular to binary file
TEST(triangular_matrix, read_write_bin_square_upper)
{
    const std::string filename = "tmp_read_bin_triangular_upper_matrix.tst";
    triang_matrix<double, false> a({{3.14, 2.718}, {1.618}}), b_build;
    a.to_file(filename, true);
    b_build.from_file(filename, true);
    const triang_matrix<double, false> &b = b_build;
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 0), 0);
    EXPECT_DOUBLE_EQ(b(1, 1), 1.618);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write of lower square triangular to text file
TEST(triangular_matrix, read_write_txt_square_lower)
{
    const std::string filename = "tmp_read_txt_triangular_lower_matrix.tst";
    triang_matrix<double, true> a({{3.14}, {2.718, 1.618}}), b_build;
    a.to_file(filename, false);
    b_build.from_file(filename, false);
    const triang_matrix<double, true> &b = b_build;
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 0);
    EXPECT_DOUBLE_EQ(b(1, 0), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 1), 1.618);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write of upper square triangular to text file
TEST(triangular_matrix, read_write_txt_square_upper)
{
    const std::string filename = "tmp_read_txt_triangular_upper_matrix.tst";
    triang_matrix<double, false> a({{3.14, 2.718}, {1.618}}), b_build;
    a.to_file(filename, false);
    b_build.from_file(filename, false);
    const triang_matrix<double, false> &b = b_build;
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.14);
    EXPECT_DOUBLE_EQ(b(0, 1), 2.718);
    EXPECT_DOUBLE_EQ(b(1, 0), 0);
    EXPECT_DOUBLE_EQ(b(1, 1), 1.618);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

} // namespace la
