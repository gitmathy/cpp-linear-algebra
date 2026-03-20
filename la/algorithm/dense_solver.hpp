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
#include "la/data_structure/util/concepts.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/block_helper.hpp"
#include "la/util/constants.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <cstddef>

namespace la {
namespace algorithm {

/// @brief LU decomposition of a matrix
/// @tparam T value type of every element
template <typename MatT, typename VecT>
class lu_decomposition : public util::dense_solver<MatT, VecT>
{
private:
    /// @brief Decomposed matrix
    MatT p_lu;

    /// @brief Permutation
    vector<size_type> p_p;

    /// @brief (Re)-Decompose a matrix
    /// @param A The matrix to be decomposed
    void decompose();

public:
    /// @brief Decompose the matrix A
    explicit lu_decomposition(const MatT &A);

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
    : util::dense_solver<MatT, VecT>(A), p_lu(0, 0), p_p(0)
{
    LOG_DEBUG("Setting up LU solver class");
    decompose();
}

template <typename MatT, typename VecT>
void lu_decomposition<MatT, VecT>::decompose()
{
    LOG_INFO("Decompose matrix");
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
                la::util::error_factory("Irregular matrix in lu decomposition",
                                              __FUNCTION_NAME__, la::util::NON_ZERO);
            }
            p_p(k) = i_pivot;
            if (i_pivot != k) {
                // Contiguous swap (Fast in Row-Major)
                T *row_k = &lu_ptr[k * N];
                T *row_p = &lu_ptr[i_pivot * N];
                for (size_type j = 0; j < N; ++j) {
                    std::swap(row_k[j], row_p[j]);
                }
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
                              // Safe Dynamic Allocation per thread/block
                              std::vector<T> u_buffer(panel_width);
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

} // namespace algorithm
} // namespace la
#endif
