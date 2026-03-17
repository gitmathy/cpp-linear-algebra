
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

// rows(), cols(), non_zeros() are tested in almost every test

/// @brief Testing read and write elements
TEST(sparse_matrix_builder, read_write_operator)
{
    sparse_matrix_builder<int> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(std::as_const(a)(0, 0), 2);
    EXPECT_EQ(std::as_const(a)(0, 1), 3);
    EXPECT_EQ(std::as_const(a)(0, 2), 0);
    EXPECT_EQ(std::as_const(a)(1, 0), 0);
    EXPECT_EQ(std::as_const(a)(1, 1), 0);
    EXPECT_EQ(std::as_const(a)(1, 2), 4);
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
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(a.non_zeros(), 0);
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(std::as_const(A)(0, 0), 2);
    EXPECT_EQ(std::as_const(A)(0, 1), 3);
    EXPECT_EQ(std::as_const(A)(0, 2), 0);
    EXPECT_EQ(std::as_const(A)(1, 0), 0);
    EXPECT_EQ(std::as_const(A)(1, 1), 0);
    EXPECT_EQ(std::as_const(A)(1, 2), 4);
}

/// @brief Testing assemble
TEST(sparse_matrix_builder, assemble)
{
    sparse_matrix_builder<int> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    sparse_matrix<int> A = a.assemble();
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 3);
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(std::as_const(A)(0, 0), 2);
    EXPECT_EQ(std::as_const(A)(0, 1), 3);
    EXPECT_EQ(std::as_const(A)(0, 2), 0);
    EXPECT_EQ(std::as_const(A)(1, 0), 0);
    EXPECT_EQ(std::as_const(A)(1, 1), 0);
    EXPECT_EQ(std::as_const(A)(1, 2), 4);
}

// /// @brief Testing value iterators
// TEST(sparse_matrix, value_iterators)
// {
//     sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);

//     for (sparse_matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
//         *(it) = int(6 + std::distance(a.begin(), it));
//     }
//     int i = 6;
//     for (sparse_matrix<int>::citerator it = a.begin(); it != a.end(); ++it, ++i) {
//         EXPECT_EQ(*it, i);
//     }
// }

// /// @brief Testing row iterators
// TEST(sparse_matrix, row_value_iterators)
// {
//     sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
//     for (size_type i = 0; i < a.rows(); ++i) {
//         for (sparse_matrix<int>::iterator it = a.row_begin(i); it != a.row_end(i); ++it) {
//             *it = int(7 + i);
//         }
//     }
//     for (size_type i = 0; i < a.rows(); ++i) {
//         for (sparse_matrix<int>::citerator it = a.row_begin(i); it != a.row_end(i); ++it) {
//             EXPECT_EQ(*it, 7 + i);
//         }
//     }
//     for (size_type nz = 0; nz < a.non_zeros(); ++nz) {
//         EXPECT_EQ(a.row_idx(nz) + 7, a(nz));
//     }
// }

// /// @brief Testing row ptr iterators
// TEST(sparse_matrix, row_ptr_iterators)
// {
//     sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
//     sparse_matrix<int>::cidx_iterator it = a.begin_row_ptr();
//     EXPECT_EQ(*it, 0);
//     EXPECT_EQ(*(it + 1), 2);
//     EXPECT_EQ(*(it + 2), 3);
//     EXPECT_EQ(it + 3, a.end_row_ptr());
// }

// /// @brief Testing column iterators
// TEST(sparse_matrix, col_iterators)
// {
//     sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
//     sparse_matrix<int>::cidx_iterator it = a.begin_col_idx();
//     EXPECT_EQ(*it, 0);
//     EXPECT_EQ(*(it + 1), 1);
//     EXPECT_EQ(*(it + 2), 2);
//     EXPECT_EQ(it + 3, a.end_col_idx());

//     EXPECT_EQ(*it, 0);
//     EXPECT_EQ(*(it + 1), 1);
//     EXPECT_EQ(*(it + 2), 2);
//     EXPECT_EQ(it + 3, a.end_col_idx());
// }

// /// @brief Testing column index iterators
// TEST(sparse_matrix, col_idx_iterators)
// {
//     sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
//     EXPECT_EQ(*(a.begin_col_idx(0)), 0);
//     EXPECT_EQ(*(a.begin_col_idx(0) + 1), 1);
//     EXPECT_EQ(a.begin_col_idx(0) + 2, a.end_col_idx(0));
//     EXPECT_EQ(*(a.begin_col_idx(1)), 2);
//     EXPECT_EQ(a.begin_col_idx(1) + 1, a.end_col_idx(1));
//     EXPECT_THROW(a.begin_col_idx(3), util::error);
// }

// // Assign is already tested via the constructors (as they just call the assign)

// /// @brief Testing read and write to binary file
// TEST(sparse_matrix, read_write_bin)
// {
//     const std::string filename = "tmp_read_bin_matrix.tst";
//     sparse_matrix<double> a({{0, 1}, {2}}, {3., 4., 5.}, 3), b;
//     a.to_file(filename, true);
//     b.from_file(filename, true);
//     EXPECT_EQ(b.rows(), 2);
//     EXPECT_EQ(b.cols(), 3);
//     EXPECT_DOUBLE_EQ(b(0, 0), 3.);
//     EXPECT_DOUBLE_EQ(b(0, 1), 4.);
//     EXPECT_DOUBLE_EQ(b(1, 2), 5.);
//     util::delete_file(filename);
//     EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
// }

// /// @brief Testing read and write to text file
// TEST(sparse_matrix, read_wite_txt)
// {
//     const std::string filename = "tmp_read_txt_matrix.tst";
//     sparse_matrix<double> a({{0, 1}, {2}}, {3., 4., 5.}, 3), b;
//     a.to_file(filename, false);
//     b.from_file(filename, false);
//     EXPECT_EQ(b.rows(), 2);
//     EXPECT_EQ(b.cols(), 3);
//     EXPECT_DOUBLE_EQ(b(0, 0), 3.);
//     EXPECT_DOUBLE_EQ(b(0, 1), 4.);
//     EXPECT_DOUBLE_EQ(b(1, 2), 5.);
//     util::delete_file(filename);
//     EXPECT_THROW(a.to_file("/no_exist/dummy", false), util::error);
// }

} // namespace la
