/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/dense_solver.hpp
/// @brief Definition and declaration of solvers for dense linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_DENSE_SOLVER_HPP
#define LA_ALGORITHM_DENSE_SOLVER_HPP

#include "la/algorithm/util/solver.hpp"
#include "la/data_structure/triangular_matrix.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/block_helper.hpp"
#include "la/util/constants.hpp"
#include "la/util/error.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace la {
namespace algorithm {

/// @brief LU decomposition of a matrix
template <typename MatT, typename VecT>
class lu_decomposition : public util::dense_solver<MatT, VecT>
{
public:
    /// @brief Definition of value types
    typedef typename util::dense_solver<MatT, VecT>::value_type value_type;

protected:
    /// @brief Decomposed matrix
    MatT p_lu;

    /// @brief Permutation
    vector<size_type> p_p;

    /// @brief Keeping track of swaps for determinate
    size_type p_swap_count;

    /// @brief (Re)-Decompose a matrix
    /// @param A The matrix to be decomposed
    virtual void decompose();

public:
    /// @brief Decompose the matrix A
    explicit lu_decomposition(const MatT &A);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief Determine the determinate of the matrix
    value_type det() const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::dense_solver<MatT, VecT>::solve;
};

/// @brief Cholesky decomposition of a matrix
template <typename MatT, typename VecT>
class cholesky_decomposition : public util::dense_solver<MatT, VecT>
{
private:
    /// @brief Cholesky factor L
    triang_matrix<typename util::dense_solver<MatT, VecT>::value_type, true> p_l;

    /// @brief (Re)-Decompose a matrix
    /// @param A The matrix to be decomposed
    void decompose();

public:
    /// @brief Decompose the matrix A
    explicit cholesky_decomposition(const MatT &A);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::dense_solver<MatT, VecT>::solve;
};

/// @brief LU decomposition for small matrices
template <typename MatT, typename VecT>
class small_lu_decomposition : public lu_decomposition<MatT, VecT>
{
private:
    /// @brief (Re)-Decompose a matrix
    /// @param A The matrix to be decomposed
    void decompose() override;

public:
    /// @brief Decompose the matrix A
    explicit small_lu_decomposition(const MatT &A);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::dense_solver<MatT, VecT>::solve;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename MatT, typename VecT>
lu_decomposition<MatT, VecT>::lu_decomposition(const MatT &A)
    : util::dense_solver<MatT, VecT>(A), p_lu(0, 0), p_p(0), p_swap_count(0)
{
    LOG_DEBUG("Setting up LU solver class");
    decompose();
}

template <typename MatT, typename VecT>
void lu_decomposition<MatT, VecT>::decompose()
{
    LOG_DEBUG("Decompose (" << this->p_A.rows() << " x " << this->p_A.cols() << ") matrix");
    typedef typename util::dense_solver<MatT, VecT>::value_type T;
    const size_type M = this->p_A.rows();
    const size_type N = this->p_A.cols();
    const size_type min_dim = std::min(M, N);
    const size_type block_size = la::util::BLOCK_SIZE;

    // Initialize LU decomposition
    p_lu = this->p_A;
    T *__restrict lu_ptr = p_lu.vals();
    p_p.allocate(min_dim);
    for (size_type i = 0; i < min_dim; ++i) {
        p_p(i) = i;
    }
    p_swap_count = 0;

    for (size_type k_block = 0; k_block < min_dim; k_block += block_size) {
        const size_type b_limit = std::min(k_block + block_size, min_dim);
        const size_type panel_width = b_limit - k_block;
        // --- 1. PANEL FACTORIZATION (Sequential) ---
        for (size_type k = k_block; k < b_limit; ++k) {
            // Find pivot in column k (Strided access in Row-Major)
            size_type i_pivot = k;
            T max_val = std::abs(lu_ptr[k * N + k]);
            for (size_type i = k + 1; i < M; ++i) {
                T val = std::abs(lu_ptr[i * N + k]);
                if (val > max_val) {
                    max_val = val;
                    i_pivot = i;
                }
            }
            if (max_val < la::util::EPS) {
                la::util::error_factory("Irregular matrix in lu decomposition", __FUNCTION_NAME__,
                                        la::util::NON_ZERO);
            }
            p_p(k) = i_pivot;
            if (i_pivot != k) {
                // Contiguous swap (Fast in Row-Major)
                T *row_k = &lu_ptr[k * N];
                T *row_p = &lu_ptr[i_pivot * N];
                for (size_type j = 0; j < N; ++j) {
                    std::swap(row_k[j], row_p[j]);
                }
                ++p_swap_count;
            }
            // Compute L multipliers (Column k)
            T diag_inv = T(1) / lu_ptr[k * N + k];
            for (size_type i = k + 1; i < M; ++i) {
                lu_ptr[i * N + k] *= diag_inv;
            }
            // Internal panel update (Update only the columns within the current block)
            for (size_type i = k + 1; i < M; ++i) {
                T l_val = lu_ptr[i * N + k];
                for (size_type j = k + 1; j < b_limit; ++j) {
                    lu_ptr[i * N + j] -= l_val * lu_ptr[k * N + j];
                }
            }
        }

        // --- 2. TRAILING MATRIX UPDATE (Parallel) ---
        if (b_limit < N) {
            // STEP A: TRSM (Solve L * U_top = A_top)
            // Parallelize over rows of the top block
            auto i_top_indices = la::util::create_range_indices(k_block, b_limit);
#ifdef PARALLEL
            std::for_each(std::execution::par_unseq, i_top_indices.begin(), i_top_indices.end(),
#else
            std::for_each(i_top_indices.begin(), i_top_indices.end(),
#endif
                          [&](size_type i) {
                              for (size_type j = b_limit; j < N; ++j) {
                                  // Dot product of L-row i and U-col j (accumulated)
                                  for (size_type k = k_block; k < i; ++k) {
                                      lu_ptr[i * N + j] -= lu_ptr[i * N + k] * lu_ptr[k * N + j];
                                  }
                              }
                          });

            // STEP B: GEMM (Schur Complement Update)
            auto i_blocks = la::util::create_block_indices(b_limit, M, block_size);
#ifdef PARALLEL
            std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(),
#else
            std::for_each(i_blocks.begin(), i_blocks.end(),
#endif
                          [&](size_type i_blk_start) {
                              // Stack-based buffer for performance
                              T u_buffer[la::util::BLOCK_SIZE];
                              const size_type i_blk_end = std::min(i_blk_start + block_size, M);

                              // We iterate by columns of the trailing matrix to pack them once
                              for (size_type j = b_limit; j < N; ++j) {

                                  // PACKING: Grab the strided Column j into a contiguous buffer
                                  for (size_type k = 0; k < panel_width; ++k) {
                                      u_buffer[k] = lu_ptr[(k_block + k) * N + j];
                                  }

                                  for (size_type i = i_blk_start; i < i_blk_end; ++i) {
                                      const T *__restrict l_row_i = &lu_ptr[i * N + k_block];
                                      T sum = 0;

                                      // Micro-kernel: Dot product (Now both are unit-stride)
                                      for (size_type k_sub = 0; k_sub < panel_width; ++k_sub) {
                                          sum += l_row_i[k_sub] * u_buffer[k_sub];
                                      }
                                      lu_ptr[i * N + j] -= sum;
                                  }
                              }
                          });
        }
    }
}

template <typename MatT, typename VecT>
bool lu_decomposition<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    LOG_DEBUG("Solving linear equation system by LU decomposition");
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for LU solve");

    typedef typename util::dense_solver<MatT, VecT>::value_type T;
    const size_type N = p_lu.rows();
    // Initialize x
    x = b;
    // Get raw pointers for the LU decomposition and vectors
    const T *__restrict lu_ptr = p_lu.vals();
    T *__restrict x_ptr = x.vals();
    const size_type *__restrict p_ptr = p_p.vals();
    // 1. PERMUTE (P * b)
    for (size_type i = 0; i < N; ++i) {
        if (p_ptr[i] != i) {
            std::swap(x_ptr[i], x_ptr[p_ptr[i]]);
        }
    }
    // 1. forward substitution (L * y = Pb)
    for (size_type i = 0; i < N; ++i) {
        T sum = 0;
        const T *__restrict row_i = &lu_ptr[i * N];
        // Dot product: row of L * partial x
        for (size_type j = 0; j < i; ++j) {
            sum += row_i[j] * x_ptr[j];
        }
        x_ptr[i] -= sum;
    }
    // 2. backward substitution (U * x = y)
    for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
        T sum = 0;
        const T *__restrict row_i = &lu_ptr[i * N];
        // Dot product: row of U * partial x
        for (size_type j = i + 1; j < N; ++j) {
            sum += row_i[j] * x_ptr[j];
        }
        // Final value: (y_i - sum) / U(i,i)
        x_ptr[i] = (x_ptr[i] - sum) / row_i[i];
    }
    return true;
}

template <typename MatT, typename VecT>
typename lu_decomposition<MatT, VecT>::value_type lu_decomposition<MatT, VecT>::det() const
{
    LOG_DEBUG("Computing the determinate of the matrix");
    typedef typename util::dense_solver<MatT, VecT>::value_type T;
    const size_type N = p_lu.rows();
    T det = T(1.0);

    // 1. Multiply the diagonal elements of U
    for (size_type i = 0; i < N; ++i) {
        det *= p_lu(i, i);
    }
    // If swaps is odd, determinant is negative
    return (p_swap_count % 2 == 0) ? det : -det;
}

// Cholesky
// --------

template <typename MatT, typename VecT>
cholesky_decomposition<MatT, VecT>::cholesky_decomposition(const MatT &A)
    : util::dense_solver<MatT, VecT>(A), p_l(0, 0)
{
    LOG_DEBUG("Setting up Cholesky solver class");
    decompose();
}

template <typename MatT, typename VecT>
void cholesky_decomposition<MatT, VecT>::decompose()
{
    LOG_DEBUG("Decompose (" << this->p_A.rows() << " x " << this->p_A.cols()
                            << ") matrix into lower triangular storage");
    typedef typename util::dense_solver<MatT, VecT>::value_type T;
    const size_type N = this->p_A.rows();
    const size_type block_size = la::util::BLOCK_SIZE;

    // 1. Initialize p_l with only the lower triangle of A
    // Assuming p_l is pre-allocated to size N*(N+1)/2
    p_l.allocate(N, N);
    T *__restrict l_ptr = p_l.vals();
    size_type l_idx = 0;
    for (size_type i = 0; i < N; ++i) {
        for (size_type j = 0; j <= i; ++j, ++l_idx) {
            l_ptr[l_idx] = this->p_A(i, j);
        }
    }

    for (size_type k_block = 0; k_block < N; k_block += block_size) {
        const size_type b_limit = std::min(k_block + block_size, N);

        // --- 1. PANEL FACTORIZATION ---
        for (size_type k = k_block; k < b_limit; ++k) {
            const T diag_val = l_ptr[p_l.get_idx(k, k)];
            if (diag_val <= la::util::EPS) {
                la::util::error_factory("Matrix not positive definite", __FUNCTION_NAME__,
                                        la::util::NON_ZERO);
            }

            const T sqrt_diag = std::sqrt(diag_val);
            l_ptr[p_l.get_idx(k, k)] = sqrt_diag;
            T inv_sqrt = T(1) / sqrt_diag;

            // Scale column k below diagonal
            for (size_type i = k + 1; i < N; ++i) {
                l_ptr[p_l.get_idx(i, k)] *= inv_sqrt;
            }

            // Internal panel update
            for (size_type j = k + 1; j < b_limit; ++j) {
                for (size_type i = j; i < N; ++i) {
                    l_ptr[p_l.get_idx(i, j)] -= l_ptr[p_l.get_idx(i, k)] * l_ptr[p_l.get_idx(j, k)];
                }
            }
        }

        // --- 2. TRAILING MATRIX UPDATE ---
        if (b_limit < N) {
            auto i_blocks = la::util::create_block_indices(b_limit, N, block_size);
#ifdef PARALLEL
            std::for_each(std::execution::par_unseq, i_blocks.begin(), i_blocks.end(),
#else
            std::for_each(i_blocks.begin(), i_blocks.end(),
#endif
                          [&](size_type i_blk_start) {
                              const size_type i_blk_end = std::min(i_blk_start + block_size, N);
                              for (size_type i = i_blk_start; i < i_blk_end; ++i) {
                                  for (size_type j = b_limit; j <= i; ++j) {
                                      T sum = 0;
                                      for (size_type k = k_block; k < b_limit; ++k) {
                                          sum +=
                                              l_ptr[p_l.get_idx(i, k)] * l_ptr[p_l.get_idx(j, k)];
                                      }
                                      l_ptr[p_l.get_idx(i, j)] -= sum;
                                  }
                              }
                          });
        }
    }
}

template <typename MatT, typename VecT>
bool cholesky_decomposition<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    LOG_DEBUG("Solving linear equation system by Cholesky (Triangular Storage)");
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for solve");

    const size_type N = p_l.rows();
    typedef typename util::dense_solver<MatT, VecT>::value_type T;
    const T *__restrict l_ptr = p_l.vals();

    x = b; // Use x as the buffer for y
    T *__restrict x_ptr = x.vals();

    // --- 1. FORWARD SUBSTITUTION (Solve Ly = b) ---
    // Accessing L row by row: Very cache-friendly
    for (size_type i = 0; i < N; ++i) {
        T sum = 0;
        for (size_type j = 0; j < i; ++j) {
            sum += l_ptr[p_l.get_idx(i, j)] * x_ptr[j];
        }
        x_ptr[i] = (x_ptr[i] - sum) / l_ptr[p_l.get_idx(i, i)];
    }

    // --- 2. BACKWARD SUBSTITUTION (Solve L^T x = y) ---
    // L^T is upper triangular. The element (L^T)_ij is L_ji.
    // Here we iterate backwards through x, but access L column-wise.
    for (size_type i = N; i-- > 0;) {
        T sum = 0;
        for (size_type j = i + 1; j < N; ++j) {
            // Accessing L_ji where j > i
            sum += l_ptr[p_l.get_idx(j, i)] * x_ptr[j];
        }
        x_ptr[i] = (x_ptr[i] - sum) / l_ptr[p_l.get_idx(i, i)];
    }

    return true;
}

// Small LU decomposition
// ----------------------

template <typename MatT, typename VecT>
small_lu_decomposition<MatT, VecT>::small_lu_decomposition(const MatT &A)
    : lu_decomposition<MatT, VecT>(A)
{
    decompose();
}

template <typename MatT, typename VecT>
void small_lu_decomposition<MatT, VecT>::decompose()
{
    LOG_DEBUG("Decompose (" << this->p_A.rows() << " x " << this->p_A.cols() << ") matrix");
    const size_type M = this->p_A.rows();
    const size_type N = this->p_A.cols();

    SHAPE_ASSERT(M == N, "small lu only implemented for square matrices");
    if (M > 8 || N > 8) {
        LOG_WARNING("Usage of solver for small systems for a big system");
    }
    MatT &LU = this->p_lu;
    vector<size_type> &P = this->p_p;
    size_type &swap_count = this->p_swap_count;
    // Initialize LU decomposition
    LU = this->p_A;
    P.allocate(N);
    for (size_type i = 0; i < N; ++i) {
        P(i) = i;
    }
    swap_count = 0;

    for (size_type i = 0; i < N; ++i) {
        size_type max_row = i;
        for (size_type k = i + 1; k < N; ++k) {
            if (std::abs(LU(k, i)) > std::abs(LU(max_row, i))) {
                max_row = k;
            }
        }

        if (std::abs(LU(max_row, i)) < la::util::EPS) {
            la::util::error_factory("Irregular matrix in lu decomposition", __FUNCTION_NAME__,
                                    la::util::NON_ZERO);
        }
        if (i != max_row) {
            for (size_type j = 0; j < N; ++j) {
                std::swap(LU(i, j), LU(max_row, j));
            }
            std::swap(P(i), P(max_row));
            ++swap_count;
        }

        for (size_type j = i + 1; j < N; ++j) {
            LU(j, i) /= LU(i, i);
            for (size_type k = i + 1; k < N; ++k) {
                LU(j, k) -= LU(j, i) * LU(i, k);
            }
        }
    }
}

template <typename MatT, typename VecT>
bool small_lu_decomposition<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    LOG_DEBUG("Solving linear equation system by LU decomposition for small systems");
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for small LU solve");
    typedef typename lu_decomposition<MatT, VecT>::value_type T;
    const MatT &LU = this->p_lu;
    const vector<size_type> &P = this->p_p;
    size_type N = LU.rows();

    // Forward substitution: Ly = Pb (y is stored in x temporarily)
    for (size_type i = 0; i < N; ++i) {
        T sum = 0;
        for (size_type k = 0; k < i; ++k) {
            sum += LU(i, k) * x(k);
        }
        x(i) = b(P(i)) - sum;
    }

    // Backward substitution: Ux = y
    for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
        T sum = 0;
        for (size_type k = i + 1; k < N; ++k) {
            sum += LU(i, k) * x(k);
        }
        x(i) = (x(i) - sum) / LU(i, i);
    }
    return true;
}

} // namespace algorithm
} // namespace la
#endif
