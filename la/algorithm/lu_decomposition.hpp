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
#include "la/util/constants.hpp"
#include "la/util/error.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <ranges>

namespace la {
namespace algorithm {

template <typename T, storage_type StorageT = ROW_WISE>
class lu_decomposition
{
private:
    /// @brief Decomposed matrix
    matrix<T, StorageT> p_lu;

    /// @brief Permutation
    vector<size_type> p_p;

    /// @brief Decompose a column-wise stored matrix yielding a decomposed stored lu matrix
    void decompose_col_col();

public:
    /// @brief Decompose the matrix A
    /// @tparam MatStorageT Storage type of matrix A
    /// @param A to be decomposed
    template <storage_type MatStorageT>
    explicit lu_decomposition(const matrix<T, MatStorageT> &A);

    /// @brief Decompose the matrix p_a and determine permutation
    void decompose();
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T, storage_type StorageT>
template <storage_type MatStorageT>
lu_decomposition<T, StorageT>::lu_decomposition(const matrix<T, MatStorageT> &A)
    : p_lu(0, 0), p_p(0)
{
    decompose();
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::decompose()
{}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::decompose_col_col()
{
    const size_type M = A.rows();
    const size_type N = A.cols();
    const size_type min_dim = std::min(M, N);
    const size_type block_size = util::BLOCK_SIZE;

    // Initialize lu decomposition matrix
    static_assert(p_lu::storage_type == COLUMN_WISE,
                  "Wrong algorithm for lu decomposition: LU not column wise");
    p_lu = A;
    std::vector<size_type> p_p(min_dim);
    for (size_type i = 0; i < min_dim; ++i)
        p_p[i] = i;

    T *__restrict lu_ptr = p_lu.vals();

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

            p_p[k] = i_pivot;
            if (i_pivot != k) {
                // Swap rows across the entire matrix width
                for (size_type j = 0; j < N; ++j) {
                    std::swap(lu_ptr[j * M + k], lu_ptr[j * M + i_pivot]);
                }
            }

            // Compute L multipliers
            T diag = lu_ptr[k * M + k];
            if (diag != T(0)) {
                for (size_type i = k + 1; i < M; ++i) {
                    lu_ptr[k * M + i] /= diag;
                }
            }

            // Internal panel update (Rank-1)
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
            auto j_indices = create_range_indices(b_limit, N);
            std::for_each(
                std::execution::par_unseq, j_indices.begin(), j_indices.end(), [&](size_type j) {
                    for (size_type k = k_block; k < b_limit; ++k) {
                        for (size_type prev_k = k_block; prev_k < k; ++prev_k) {
                            lu_ptr[j * M + k] -= lu_ptr[(prev_k)*M + k] * lu_ptr[j * M + prev_k];
                        }
                    }
                });

            // STEP B: UPDATE SCHUR COMPLEMENT (GEMM)
            // LU[i, j] -= L[i, k] * U[k, j]
            auto i_blocks = create_block_indices(b_limit, M, block_size);
            std::for_each(std::execution::par_unseq, i_blocks.begin(), i_blocks.end(),
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
    return {LU, P, 0};
}

} // namespace algorithm
} // namespace la

#endif
