
#include "pch.h"

#include "la/sparse"
#include <gtest/gtest.h>
#include <memory>

namespace la {

/// @brief Test default constructor for sparse matrix
TEST(sparse_matrix, default_constructor)
{
    sparse_matrix<int> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    sparse_matrix<double> b;
    EXPECT_EQ(b.rows(), 0);
    EXPECT_EQ(b.cols(), 0);
    EXPECT_THROW(a(0, 0), util::error);
    EXPECT_THROW(b(0, 0), util::error);
}

/// @brief Test constructor from initializer list
TEST(sparse_matrix, initializer_constructor)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a(0, 0), 3);
    EXPECT_EQ(a(0, 1), 4);
    EXPECT_EQ(a(1, 2), 5);
    EXPECT_THROW(a(2, 0), util::error);
    EXPECT_THROW(a(0, 3), util::error);
}

/// @brief Test move constructor
TEST(sparse_matrix, move_constructor)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    sparse_matrix<int> dst(std::move(a));
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_EQ(dst.rows(), 2);
    EXPECT_EQ(dst.cols(), 3);
    EXPECT_EQ(dst(0, 0), 3);
    EXPECT_EQ(dst(0, 1), 4);
    EXPECT_EQ(dst(1, 2), 5);
}

/// @brief Test copy constructor
TEST(sparse_matrix, copy_constructor)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    const sparse_matrix<int> dst(a);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a(0, 0), 3);
    EXPECT_EQ(a(0, 1), 4);
    EXPECT_EQ(a(1, 2), 5);
    EXPECT_EQ(dst.rows(), 2);
    EXPECT_EQ(dst.cols(), 3);
    EXPECT_EQ(dst(0, 0), 3);
    EXPECT_EQ(dst(0, 1), 4);
    EXPECT_EQ(dst(1, 2), 5);
    EXPECT_EQ(dst(0, 2), 0);
    EXPECT_EQ(dst(1, 0), 0);
    EXPECT_EQ(dst(1, 1), 0);
}

/// @brief Test sparse builder move constructor
TEST(sparse_matrix, move_builder_constructor)
{
    sparse_matrix_builder<int> a_build(2, 3);
    a_build(0, 0) = 3;
    a_build(0, 1) = 4;
    a_build(1, 2) = 5;
    sparse_matrix<int> a(std::move(a_build));
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a(0, 0), 3);
    EXPECT_EQ(a(0, 1), 4);
    EXPECT_EQ(a(1, 2), 5);
}

/// @brief Test sparse matrix destructor
TEST(sparse_matrix, destructor)
{
    sparse_matrix<int> *a = new sparse_matrix<int>({{0, 1}, {2}}, {3, 4, 5}, 3);
    delete a;
}

/// @brief Test allocate
TEST(sparse_matrix, allocated)
{
    sparse_matrix<float> a;
    a.allocate(5, 4, 10);
    EXPECT_EQ(a.rows(), 5);
    EXPECT_EQ(a.cols(), 4);
    EXPECT_EQ(a.non_zeros(), 10);
    a.allocate(2, 3, 4);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_EQ(a.non_zeros(), 4);
    EXPECT_THROW(a.allocate(1, 1, 100), util::error);
}

// rows(), cols(), non_zeros() are tested in almost every test

/// @brief Test row_idx_begin
TEST(sparse_matrix, row_idx_begin)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    EXPECT_EQ(a.row_idx_begin(0), 0);
    EXPECT_EQ(a.row_idx_begin(1), 2);
    EXPECT_EQ(a.row_idx_begin(2), 3);
    EXPECT_THROW(a.row_idx_begin(3), util::error);
}

/// @brief Test col_idx
TEST(sparse_matrix, col_idx)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    EXPECT_EQ(a.col_idx(0), 0);
    EXPECT_EQ(a.col_idx(1), 1);
    EXPECT_EQ(a.col_idx(2), 2);
    EXPECT_THROW(a.col_idx(4), util::error);
}

/// @brief Test row_idx
TEST(sparse_matrix, row_idx)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    EXPECT_EQ(a.row_idx(0), 0);
    EXPECT_EQ(a.row_idx(1), 0);
    EXPECT_EQ(a.row_idx(2), 1);
    EXPECT_THROW(a.row_idx(3), util::error);
}

/// @brief Testing read and write elements
TEST(sparse_matrix, read_write_operator)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    const sparse_matrix<int> a_const(a);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    EXPECT_EQ(a(0, 0), 2);
    EXPECT_EQ(a(0, 1), 3);
    EXPECT_EQ(a(1, 2), 4);
    EXPECT_EQ(a(0), 2);
    EXPECT_EQ(a(1), 3);
    EXPECT_EQ(a(2), 4);
    EXPECT_EQ(a_const(0), 3);
    EXPECT_EQ(a_const(1), 4);
    EXPECT_EQ(a_const(2), 5);
    EXPECT_THROW(a(0, 2) = 3, util::error);
    EXPECT_THROW(a(0, 3), util::error);
    EXPECT_THROW(a(3), util::error);
    EXPECT_THROW(a_const(0, 3), util::error);
    EXPECT_THROW(a_const(3), util::error);
}

/// @brief Testing evaluate
TEST(sparse_matrix, evaluate)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    const sparse_matrix<int> a_const(a);
    EXPECT_EQ(a_const.evaluate(0), 3);
    EXPECT_EQ(a_const.evaluate(1), 4);
    EXPECT_EQ(a_const.evaluate(2), 5);
    EXPECT_THROW(a_const.evaluate(0, 3), util::error);
    EXPECT_THROW(a_const.evaluate(3), util::error);
}

/// @brief Testing value iterators
TEST(sparse_matrix, value_iterators)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);

    for (sparse_matrix<int>::iterator it = a.begin(); it != a.end(); ++it) {
        *(it) = 6 + std::distance(a.begin(), it);
    }
    int i = 6;
    for (sparse_matrix<int>::citerator it = a.begin(); it != a.end(); ++it, ++i) {
        EXPECT_EQ(*it, i);
    }
}

/// @brief Testing row iterators
TEST(sparse_matrix, row_value_iterators)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    for (size_type i = 0; i < a.rows(); ++i) {
        for (sparse_matrix<int>::iterator it = a.row_begin(i); it != a.row_end(i); ++it) {
            *it = 7 + i;
        }
    }
    for (size_type i = 0; i < a.rows(); ++i) {
        for (sparse_matrix<int>::citerator it = a.row_begin(i); it != a.row_end(i); ++it) {
            EXPECT_EQ(*it, 7 + i);
        }
    }
    for (size_type nz = 0; nz < a.non_zeros(); ++nz) {
        EXPECT_EQ(a.row_idx(nz) + 7, a(nz));
    }
}

/// @brief Testing row ptr iterators
TEST(sparse_matrix, row_ptr_iterators)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    sparse_matrix<int>::cidx_iterator it = a.begin_row_ptr();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*(it + 1), 2);
    EXPECT_EQ(*(it + 2), 3);
    EXPECT_EQ(it + 3, a.end_row_ptr());
}

/// @brief Testing column iterators
TEST(sparse_matrix, col_iterators)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    sparse_matrix<int>::cidx_iterator it = a.begin_col_idx();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*(it + 1), 1);
    EXPECT_EQ(*(it + 2), 2);
    EXPECT_EQ(it + 3, a.end_col_idx());

    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*(it + 1), 1);
    EXPECT_EQ(*(it + 2), 2);
    EXPECT_EQ(it + 3, a.end_col_idx());
}

/// @brief Testing column index iterators
TEST(sparse_matrix, col_idx_iterators)
{
    sparse_matrix<int> a({{0, 1}, {2}}, {3, 4, 5}, 3);
    EXPECT_EQ(*(a.begin_col_idx(0)), 0);
    EXPECT_EQ(*(a.begin_col_idx(0) + 1), 1);
    EXPECT_EQ(a.begin_col_idx(0) + 2, a.end_col_idx(0));
    EXPECT_EQ(*(a.begin_col_idx(1)), 2);
    EXPECT_EQ(a.begin_col_idx(1) + 1, a.end_col_idx(1));
    EXPECT_THROW(a.begin_col_idx(3), util::error);
}

// Assign is already tested via the constructors (as they just call the assign)

/// @brief Testing read and write to binary file
TEST(sparse_matrix, read_write_bin)
{
    const std::string filename = "tmp_read_bin_matrix.tst";
    sparse_matrix<double> a({{0, 1}, {2}}, {3., 4., 5.}, 3), b;
    a.to_file(filename, true);
    b.from_file(filename, true);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 3);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.);
    EXPECT_DOUBLE_EQ(b(0, 1), 4.);
    EXPECT_DOUBLE_EQ(b(1, 2), 5.);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write to text file
TEST(sparse_matrix, read_wite_txt)
{
    const std::string filename = "tmp_read_txt_matrix.tst";
    sparse_matrix<double> a({{0, 1}, {2}}, {3., 4., 5.}, 3), b;
    a.to_file(filename, false);
    b.from_file(filename, false);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 3);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.);
    EXPECT_DOUBLE_EQ(b(0, 1), 4.);
    EXPECT_DOUBLE_EQ(b(1, 2), 5.);
    util::delete_file(filename);
    EXPECT_THROW(a.to_file("/no_exist/dummy", false), util::error);
}

} // namespace la
