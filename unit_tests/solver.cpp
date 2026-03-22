/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/solver.cpp
/// @brief Unit tests for solvers
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include "la/sparse"
#include <gtest/gtest.h>

namespace la {

/// @brief Test lu decomposition
TEST(solver, lu_decomposition)
{
    matrix<double> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});
    algorithm::lu_decomposition<matrix<double>, vector<double>> lu(A);
    const vector<double> x = lu.solve(b);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 2.2);
    EXPECT_DOUBLE_EQ(x(1), 1.4);
    EXPECT_DOUBLE_EQ(x(2), 1.2);
    EXPECT_THROW(lu.solve(vector<double>(4)), util::error);
}

/// @brief Test lu decomposition with given memory for solution
TEST(solver, lu_decomposition_w_x)
{
    matrix<double> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});
    vector<double> x(3);
    algorithm::lu_decomposition<matrix<double>, vector<double>> lu(A);
    lu.solve(b, x);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 2.2);
    EXPECT_DOUBLE_EQ(x(1), 1.4);
    EXPECT_DOUBLE_EQ(x(2), 1.2);
    vector<double> x_wrong(4);
    EXPECT_THROW(lu.solve(b, x_wrong), util::error);
}

/// @brief Test error thrown for irregular matrix
TEST(solver, lu_decomposition_irregular)
{
    matrix<double> A({{0, 0}, {1, 1}});
    typedef algorithm::lu_decomposition<matrix<double>, vector<double>> solver_type;
    EXPECT_THROW(solver_type lu(A), util::non_zero_error);
}

/// @brief Test un-preconditioned CG solver
TEST(solver, cg_un_pred)
{
    // Arange
    const size_type n = 100;
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
            A_build(i, i - 1) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    algorithm::cg_solver<sparse_matrix<double>, vector<double>> cg(A, 1e-5, n);
    // Act
    // Assert
    const vector<double> x = cg.solve(b);
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_TRUE(cg.solved());
    ASSERT_LE(cg.iter(), n);
    ASSERT_LE(cg.res(), 1e-5);
    ASSERT_LE(error_norm, 1e-4);
}

/// @brief Test un-preconditioned CG solver
TEST(solver, cg_un_pred_with_x)
{
    // Arange
    const size_type n = 100;
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
            A_build(i, i - 1) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    algorithm::cg_solver<sparse_matrix<double>, vector<double>> cg(A, 1e-5, n);
    vector<double> x(n);
    // Act
    const bool result = cg.solve(b, x);
    // Assert
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_EQ(cg.solved(), result);
    ASSERT_TRUE(cg.solved());
    ASSERT_LE(cg.iter(), n);
    ASSERT_LE(cg.res(), 1e-5);
    ASSERT_LE(error_norm, 1e-4);
    std::cout << "Solved by CG in " << cg.iter() << " steps" << std::endl;
}

/// @brief Test un-preconditioned CG solver
TEST(solver, cg_un_pred_fail)
{
    // Arange
    const size_type n = 100;
    // setup a matrix which is not s.p.d.
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    algorithm::cg_solver<sparse_matrix<double>, vector<double>> cg(A, 1e-5, n);
    // Act
    // Assert
    const vector<double> x = cg.solve(b);
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_FALSE(cg.solved());
    ASSERT_EQ(cg.iter(), n);
    ASSERT_GE(cg.res(), 1e-5);
    ASSERT_GE(error_norm, 1e-4);
}

/// @brief Test Jacobi preconditioned CG solver
TEST(solver, pcg_jacobi)
{
    // Arange
    const size_type n = 100;
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
            A_build(i, i - 1) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    pcg_jacobi pcg(A, 1e-10, n, 1.0);
    // Act
    const vector<double> x = pcg.solve(b);
    // Assert
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_TRUE(pcg.solved());
    ASSERT_LE(pcg.iter(), n);
    ASSERT_LE(pcg.res(), 1e-5);
    ASSERT_LE(error_norm, 1e-4);
}

/// @brief Test symmetric gauss-seidel preconditioned CG solver
TEST(solver, pcg_sgs)
{
    // Arange
    const size_type n = 100;
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
            A_build(i, i - 1) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    pcg_sgs pcg(A, 1e-10, n, 1.0);
    // Act
    const vector<double> x = pcg.solve(b);
    // Assert
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_TRUE(pcg.solved());
    ASSERT_LE(pcg.iter(), n);
    ASSERT_LE(pcg.res(), 1e-5);
    ASSERT_LE(error_norm, 1e-4);
}

TEST(solver, pgmres_ilu)
{
    // Arange
    const size_type n = 100;
    sparse_matrix_builder<double> A_build(n, n);
    for (size_type i = 0; i < n; ++i) {
        A_build(i, i) = 2;
        if (i > 0) {
            A_build(i - 1, i) = -1;
        }
    }
    sparse_matrix<double> A;
    A_build.move(A);
    const vector<double> b(n, 2.0);
    pgmres_ilu pgmres(A, 1e-10, n, n / 4, 1.0);
    // Act
    const vector<double> x = pgmres.solve(b);
    // Assert
    const vector<double> error = A * x - b;
    const double error_norm = norm<2>(error);
    ASSERT_TRUE(pgmres.solved());
    ASSERT_LE(pgmres.iter(), n);
    ASSERT_LE(pgmres.res(), 1e-5);
    ASSERT_LE(error_norm, 1e-4);
}

/// @brief Test identity preconditioner
TEST(solver, identity_pc_1)
{
    sparse_matrix<double> A({{0, 1}, {0, 1, 2}, {1, 2}}, {4., 1., 1., 4., 1., 1., 4.}, 3);
    const vector<double> b({1., 2., 3.});
    algorithm::identity_pc<sparse_matrix<double>, vector<double>> pc(A);
    const vector<double> x = pc.solve(b);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 1.0);
    EXPECT_DOUBLE_EQ(x(1), 2.0);
    EXPECT_DOUBLE_EQ(x(2), 3.0);
}

/// @brief Test identity preconditioner
TEST(solver, identity_pc_2)
{
    sparse_matrix<double> A({{0, 1}, {0, 1, 2}, {1, 2}}, {4., 1., 1., 4., 1., 1., 4.}, 3);
    const vector<double> b({1., 2., 3.});
    algorithm::identity_pc<sparse_matrix<double>, vector<double>> pc(A);
    vector<double> x(3);
    pc.solve(b, x);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_DOUBLE_EQ(x(0), 1.0);
    EXPECT_DOUBLE_EQ(x(1), 2.0);
    EXPECT_DOUBLE_EQ(x(2), 3.0);
}

/// @brief Test ilu preconditioner
TEST(solver, ilu)
{
    sparse_matrix<double> A({{0, 1}, {0, 1, 2}, {1, 2}}, {4., 1., 1., 4., 1., 1., 4.}, 3);
    const vector<double> b({1., 2., 3.});
    algorithm::ilu_pc<sparse_matrix<double>, vector<double>> ilu(A);
    const vector<double> x = ilu.solve(b);
    EXPECT_EQ(x.rows(), 3);
    EXPECT_NEAR(x(0), 0.1786, 1e-4);
    EXPECT_NEAR(x(1), 0.2857, 1e-4);
    EXPECT_NEAR(x(2), 0.6786, 1e-4);
}

} // namespace la
