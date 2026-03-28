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

} // namespace la
