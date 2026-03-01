/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/lu_decomposition.hpp
/// @brief Definition and declaration decomposition algorithms
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_LU_DECOMPOSITION_HPP
#define LA_ALGORITHM_LU_DECOMPOSITION_HPP

#include "la/data_structure/matrix.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/block_helper.hpp"
#include "la/util/constants.hpp"
#include "la/util/error.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <ranges>

namespace la {
namespace algorithm {

template <typename T, storage_type StorageT>
class lu_decomposition
{
private:
    /// @brief Decomposed matrix
    matrix<T, StorageT> p_lu;

    /// @brief Permutation
    vector<size_type> p_p;

    /// @brief Decompose a column-wise stored matrix yielding a column decomposed stored lu matrix
    void decompose_col_col(const matrix<T, COLUMN_WISE> &A);

    /// @brief Decompose a row-wise stored matrix yielding a row decomposed stored lu matrix
    void decompose_row_row(const matrix<T, ROW_WISE> &A);

    /// @brief Solve a linear equation system with a single rhs, if lu is column wise stored
    /// @param x The solution to A^-1*rhs
    /// @param rhs The right hand side of the linear equation system
    void solve_col(vector<T> &x, const vector<T> &rhs) const;

    /// @brief Solve a linear equation system with a single rhs, if lu is row wise stored
    /// @param x The solution to A^-1*rhs
    /// @param rhs The right hand side of the linear equation system
    void solve_row(vector<T> &x, const vector<T> &rhs) const;

public:
    /// @brief Decompose the matrix A
    /// @tparam MatStorageT Storage type of matrix A
    /// @param A to be decomposed
    template <storage_type MatStorageT>
    explicit lu_decomposition(const matrix<T, MatStorageT> &A);

    /// @brief (Re)-Decompose a matrix
    /// @param A The matrix to be decomposed
    template <storage_type MatStorageT>
    void decompose(const matrix<T, MatStorageT> &A);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    void solve(vector<T> &x, const vector<T> &rhs) const;

    /// @brief Solve the system with rhs
    /// @param rhs right hand side
    /// @return A^-1*rhs
    vector<T> solve(const vector<T> &rhs) const;
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T, storage_type StorageT>
template <storage_type MatStorageT>
lu_decomposition<T, StorageT>::lu_decomposition(const matrix<T, MatStorageT> &A)
    : p_lu(0, 0), p_p(0)
{
    decompose(A);
}

template <typename T, storage_type StorageT>
template <storage_type MatStorageT>
void lu_decomposition<T, StorageT>::decompose(const matrix<T, MatStorageT> &A)
{
    static_assert(MatStorageT == StorageT,
                  "LU decompose: matrix and decomposition must use same storage format");
    if constexpr (MatStorageT == COLUMN_WISE && StorageT == COLUMN_WISE) {
        decompose_col_col(A);
    }
    if constexpr (MatStorageT == ROW_WISE && StorageT == ROW_WISE) {
        decompose_row_row(A);
    }
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::solve(vector<T> &x, const vector<T> &rhs) const
{
    if constexpr (StorageT == COLUMN_WISE) {
        solve_col(x, rhs);
    }
    if constexpr (StorageT == ROW_WISE) {
        solve_row(x, rhs);
    }
}

template <typename T, storage_type StorageT>
vector<T> lu_decomposition<T, StorageT>::solve(const vector<T> &rhs) const
{
    vector<T> x(0);
    solve(x, rhs);
    return x;
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::decompose_col_col(const matrix<T, COLUMN_WISE> &A)
{
    const size_type M = A.rows();
    const size_type N = A.cols();
    const size_type min_dim = std::min(M, N);
    const size_type block_size = util::BLOCK_SIZE;

    // Initialize lu decomposition matrix
    p_lu = A;
    T *__restrict lu_ptr = p_lu.vals();
    p_p.allocate(min_dim);
    for (size_type i = 0; i < min_dim; ++i) {
        p_p(i) = i;
    }

    for (size_type k_block = 0; k_block < min_dim; k_block += block_size) {
        const size_type b_limit = std::min(k_block + block_size, min_dim);
        const size_type panel_width = b_limit - k_block;
        // --- 1. PANEL FACTORIZATION (Sequential L1-Cache Work) ---
        for (size_type k = k_block; k < b_limit; ++k) {
            // Partial Pivoting: Find max in current column
            size_type i_pivot = k;
            T max_val = std::abs(lu_ptr[k * M + k]);
            for (size_type i = k + 1; i < M; ++i) {
                T val = std::abs(lu_ptr[k * M + i]);
                if (val > max_val) {
                    max_val = val;
                    i_pivot = i;
                }
            }
            // Check if the matrix is not irregular
            if (max_val < util::EPS) {
                throw util::error("No LU decomposition for irregular matrices", "algorithm:lup");
            }
            // Swap rows across the entire matrix width
            p_p(k) = i_pivot;
            if (i_pivot != k) {
                for (size_type j = 0; j < N; ++j) {
                    std::swap(lu_ptr[j * M + k], lu_ptr[j * M + i_pivot]);
                }
            }
            // Compute L multipliers and update L part
            T diag = lu_ptr[k * M + k];
            if (diag != T(0)) {
                for (size_type i = k + 1; i < M; ++i) {
                    lu_ptr[k * M + i] /= diag;
                }
            }
            for (size_type j = k + 1; j < b_limit; ++j) {
                for (size_type i = k + 1; i < M; ++i) {
                    lu_ptr[j * M + i] -= lu_ptr[k * M + i] * lu_ptr[j * M + k];
                }
            }
        }

        // --- 2. TRAILING MATRIX UPDATE (Parallel Block Work) ---
        if (b_limit < N) {

            // STEP A: UPDATE U_TOP (TRSM)
            // Solve L_panel * U_top = A_top for columns j = b_limit to N
            auto j_indices = util::create_range_indices(b_limit, N);
#ifdef PARALLEL
            std::for_each(
                execution::par_unseq, j_indices.begin(), j_indices.end(), [&](size_type j) {
#else
            std::for_each(j_indices.begin(), j_indices.end(), [&](size_type j) {
#endif
                    for (size_type k = k_block; k < b_limit; ++k) {
                        for (size_type prev_k = k_block; prev_k < k; ++prev_k) {
                            lu_ptr[j * M + k] -= lu_ptr[(prev_k)*M + k] * lu_ptr[j * M + prev_k];
                        }
                    }
                });
            // STEP B: UPDATE SCHUR COMPLEMENT (GEMM)
            // LU[i, j] -= L[i, k] * U[k, j]
            auto i_blocks = util::create_block_indices(b_limit, M, block_size);
#ifdef PARALLEL
            std::for_each(std::execution::par_unseq, i_blocks.begin(), i_blocks.end(),
#else
            std::for_each(i_blocks.begin(), i_blocks.end(),
#endif
                          [&](size_type i_blk_start) {
                              T l_buffer[util::BLOCK_SIZE]; // Stack buffer for Row-Packing
                              const size_type i_blk_end = std::min(i_blk_start + block_size, M);
                              for (size_type i = i_blk_start; i < i_blk_end; ++i) {
                                  // PACKING: Row i of the Panel into contiguous buffer
                                  for (size_type k = 0; k < panel_width; ++k) {
                                      l_buffer[k] = lu_ptr[(k_block + k) * M + i];
                                  }
                                  // For every column in the trailing submatrix
                                  for (size_type j = b_limit; j < N; ++j) {
                                      // U_top is stored in lu_ptr[j*M + k_block...b_limit]
                                      const T *__restrict u_col_j = &lu_ptr[j * M + k_block];
                                      T sum = 0;

                                      // Contiguous Dot Product (Vectorizable)
                                      for (size_type k_sub = 0; k_sub < panel_width; ++k_sub) {
                                          sum += l_buffer[k_sub] * u_col_j[k_sub];
                                      }
                                      lu_ptr[j * M + i] -= sum;
                                  }
                              }
                          });
        }
    }
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::decompose_row_row(const matrix<T, ROW_WISE> &A)
{
    const size_type M = A.rows();
    const size_type N = A.cols();
    const size_type min_dim = std::min(M, N);
    const size_type block_size = util::BLOCK_SIZE;

    // Initialize LU decomposition
    p_lu = A;
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
            if (max_val < util::EPS) {
                throw util::error("Irregular matrix", "algorithm:lup");
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
            auto i_top_indices = util::create_range_indices(k_block, b_limit);
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
            auto i_blocks = util::create_block_indices(b_limit, M, block_size);
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

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::solve_col(vector<T> &x, const vector<T> &rhs) const
{
    const size_type N = p_lu.rows();

    // Initialize x
    x = rhs;
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
    for (size_type j = 0; j < N; ++j) {
        const T multiplier = x_ptr[j];
        // The column j of L starts at lu_ptr[j * N]
        // Elements of L are in the lower triangle (i > j)
        for (size_type i = j + 1; i < N; ++i) {
            x_ptr[i] -= lu_ptr[j * N + i] * multiplier;
        }
    }
    // 2. backward substitution (U * x = y)
    for (int j = static_cast<int>(N) - 1; j >= 0; --j) {
        x_ptr[j] /= lu_ptr[j * N + j]; // Divide by U(j,j)
        const T multiplier = x_ptr[j];
        for (int i = 0; i < j; ++i) {
            x_ptr[i] -= lu_ptr[j * N + i] * multiplier;
        }
    }
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::solve_row(vector<T> &x, const vector<T> &rhs) const
{
    const size_type N = p_lu.rows();

    // Initialize x
    x = rhs;
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
}

} // namespace algorithm
} // namespace la

#endif
