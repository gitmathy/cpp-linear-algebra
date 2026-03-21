
#include "pch.h"

#include "la/sparse"
#include <gtest/gtest.h>
#include <memory>
#include <utility>

namespace la {

/// @brief Test constructor for triplet sparse matrix
TEST(triplet_sparse_matrix, constructor_overwrite)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(3, 4);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 4);
}

/// @brief Test constructor for triplet sparse matrix
TEST(triplet_sparse_matrix, constructor_sum)
{
    triplet_sparse_matrix<int, util::SUM> a(3, 4);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 4);
}

/// @brief Test allocate
TEST(triplet_sparse_matrix, allocate_overwrite)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(3, 4);
    a.allocate(2, 3);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
}

/// @brief Test allocate
TEST(triplet_sparse_matrix, allocate_sum)
{
    triplet_sparse_matrix<int, util::SUM> a(3, 4);
    a.allocate(2, 3);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 3);
}

// rows(), cols() are tested in almost every test

/// @brief Testing read and write elements
TEST(triplet_sparse_matrix, read_write_operator_overwrite)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 3;
    a(1, 2) = 4;
    a(1, 1) = 1;
    a(0, 0) = 3;
    a(1, 2) = 5;
    const triplet_sparse_matrix<int, util::OVERWRITE> &a_const(a);
    EXPECT_EQ(a_const(0, 0), 3);
    EXPECT_EQ(a_const(0, 1), 3);
    EXPECT_EQ(a_const(0, 2), 0);
    EXPECT_EQ(a_const(1, 0), 0);
    EXPECT_EQ(a_const(1, 1), 1);
    EXPECT_EQ(a_const(1, 2), 5);
    EXPECT_THROW(a(0, 3) = 3, util::boundary_error);
    EXPECT_THROW(a(2, 0), util::boundary_error);
}

/// @brief Testing assemble
TEST(triplet_sparse_matrix, assemble_overwrite_0)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 1;
    a(1, 2) = 4;
    a(0, 1) = 3;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(A(0, 0), 2);
    EXPECT_EQ(A(0, 1), 3);
    EXPECT_EQ(A(0, 2), 0);
    EXPECT_EQ(A(1, 0), 0);
    EXPECT_EQ(A(1, 1), 0);
    EXPECT_EQ(A(1, 2), 4);
}

/// @brief Two rows with same non-zeros
TEST(triplet_sparse_matrix, assemble_overwrite_1)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(2, 3);
    a(0, 0) = 2;
    a(1, 0) = 2;
    a(0, 0) = 1;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 2);
    EXPECT_EQ(A(0, 0), 1);
    EXPECT_EQ(A(0, 1), 0);
    EXPECT_EQ(A(0, 2), 0);
    EXPECT_EQ(A(1, 0), 2);
    EXPECT_EQ(A(1, 1), 0);
    EXPECT_EQ(A(1, 2), 0);
}

/// @brief Empty rows
TEST(triplet_sparse_matrix, assemble_overwrite_2)
{
    triplet_sparse_matrix<int, util::OVERWRITE> a(6, 3);
    a(2, 0) = 1;
    a(3, 2) = 1;
    a(2, 0) = 2;
    a(3, 2) = 3;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 6);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 2);
    EXPECT_EQ(A(2, 0), 2);
    EXPECT_EQ(A(2, 1), 0);
    EXPECT_EQ(A(2, 2), 0);
    EXPECT_EQ(A(3, 0), 0);
    EXPECT_EQ(A(3, 1), 0);
    EXPECT_EQ(A(3, 2), 3);

    // Check empty rows
    for (size_type j = 0; j < 3; ++j) {
        EXPECT_EQ(A(0, j), 0);
        EXPECT_EQ(A(1, 0), 0);
        EXPECT_EQ(A(4, 1), 0);
        EXPECT_EQ(A(5, 1), 0);
    }
    LOG_DEBUG("Finalizing empty rows");
}

/// @brief Empty matrix
TEST(triplet_sparse_matrix, assemble_overwrite_3)
{
    LOG_DEBUG("Testing empty matrix");
    triplet_sparse_matrix<int, util::OVERWRITE> a(2, 3);
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 0);
    for (size_type i = 0; i < 2; ++i) {
        for (size_type j = 0; j < 3; ++j) {
            EXPECT_EQ(A(i, j), 0);
        }
    }
}

/// @brief Testing assemble
TEST(triplet_sparse_matrix, assemble_sum_0)
{
    triplet_sparse_matrix<int, util::SUM> a(2, 3);
    a(0, 0) = 2;
    a(0, 1) = 1;
    a(1, 2) = 4;
    a(0, 1) = 3;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 3);
    EXPECT_EQ(A(0, 0), 2);
    EXPECT_EQ(A(0, 1), 4);
    EXPECT_EQ(A(0, 2), 0);
    EXPECT_EQ(A(1, 0), 0);
    EXPECT_EQ(A(1, 1), 0);
    EXPECT_EQ(A(1, 2), 4);
}

/// @brief Two rows with same non-zeros
TEST(triplet_sparse_matrix, assemble_sum_1)
{
    triplet_sparse_matrix<int, util::SUM> a(2, 3);
    a(0, 0) = 2;
    a(1, 0) = 2;
    a(0, 0) = 1;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 2);
    EXPECT_EQ(A(0, 0), 3);
    EXPECT_EQ(A(0, 1), 0);
    EXPECT_EQ(A(0, 2), 0);
    EXPECT_EQ(A(1, 0), 2);
    EXPECT_EQ(A(1, 1), 0);
    EXPECT_EQ(A(1, 2), 0);
}

/// @brief Empty rows
TEST(triplet_sparse_matrix, assemble_sum_2)
{
    triplet_sparse_matrix<int, util::SUM> a(6, 3);
    a(2, 0) = 1;
    a(3, 2) = 1;
    a(2, 0) = 2;
    a(3, 2) = 3;
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 6);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 2);
    EXPECT_EQ(A(2, 0), 3);
    EXPECT_EQ(A(2, 1), 0);
    EXPECT_EQ(A(2, 2), 0);
    EXPECT_EQ(A(3, 0), 0);
    EXPECT_EQ(A(3, 1), 0);
    EXPECT_EQ(A(3, 2), 4);

    // Check empty rows
    for (size_type j = 0; j < 3; ++j) {
        EXPECT_EQ(A(0, j), 0);
        EXPECT_EQ(A(1, 0), 0);
        EXPECT_EQ(A(4, 1), 0);
        EXPECT_EQ(A(5, 1), 0);
    }
    LOG_DEBUG("Finalizing empty rows");
}

/// @brief Empty matrix
TEST(triplet_sparse_matrix, assemble_sum_3)
{
    LOG_DEBUG("Testing empty matrix");
    triplet_sparse_matrix<int, util::SUM> a(2, 3);
    sparse_matrix<int> A_assemble = a.assemble();
    const sparse_matrix<int> &A = A_assemble;
    EXPECT_EQ(A.rows(), 2);
    EXPECT_EQ(A.cols(), 3);
    EXPECT_EQ(A.non_zeros(), 0);
    for (size_type i = 0; i < 2; ++i) {
        for (size_type j = 0; j < 3; ++j) {
            EXPECT_EQ(A(i, j), 0);
        }
    }
}

// /// @brief Testing move
// TEST(sparse_matrix_builder, move)
// {
//     sparse_matrix_builder<int> a(2, 3);
//     a(0, 0) = 2;
//     a(0, 1) = 3;
//     a(1, 2) = 4;
//     sparse_matrix<int> A;
//     a.move(A);
//     EXPECT_EQ(a.rows(), 0);
//     EXPECT_EQ(a.cols(), 0);
//     EXPECT_EQ(a.non_zeros(), 0);
//     EXPECT_EQ(A.rows(), 2);
//     EXPECT_EQ(A.cols(), 3);
//     EXPECT_EQ(A.non_zeros(), 3);
//     EXPECT_EQ(std::as_const(A)(0, 0), 2);
//     EXPECT_EQ(std::as_const(A)(0, 1), 3);
//     EXPECT_EQ(std::as_const(A)(0, 2), 0);
//     EXPECT_EQ(std::as_const(A)(1, 0), 0);
//     EXPECT_EQ(std::as_const(A)(1, 1), 0);
//     EXPECT_EQ(std::as_const(A)(1, 2), 4);
// }

} // namespace la
