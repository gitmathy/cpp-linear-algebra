/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/multiplication.hpp
/// @brief Definition and declaration of matrix-matrix multiplication
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_MULTIPLICATION_HPP
#define LA_ALGORITHM_MULTIPLICATION_HPP

#include "la/data_structure/matrix.hpp"
#include "la/data_structure/sparse_matrix.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/block_helper.hpp"
#include "la/util/constants.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <atomic>
#include <vector>

namespace la {
namespace algorithm {

/// @brief Multiplying dense matrices
///
/// All of the implementations are making use of std::executions to parallel executions via
/// for_each. Moreover, the memory access is optimized w.r.t. alignments and also with blocking
/// strategies.
/// @tparam T The value type of the matrix elements (must be a primary type)
template <typename T>
class matrix_multiplication
{
public:
    /// @brief Multiplying two matrices A and B of different storage types
    /// @param A left matrix
    /// @param B right matrix
    /// @return A*B
    static matrix<T> multiply(const matrix<T> &A, const matrix<T> &B);
};

/// @brief Multiplying a a transposed sparse matrix with a vector
/// @tparam T Type of the element in the matrix and vector
template <typename T>
class transpose_matrix_multiplication
{
public:
    /// @brief Multiply the transposed of A with x yielding y, i.e., A^T*x=y
    static void multiply(const sparse_matrix<T> &A, const vector<T> &x, vector<T> &y,
                         const bool y_is_zero = false);
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// ROW_WISE RESULT
//----------------

template <typename T>
matrix<T> matrix_multiplication<T>::multiply(const matrix<T> &A, const matrix<T> &B)
{
    SHAPE_ASSERT(A.cols() == B.rows(), "matrix_multiplication: invalid dimension");
    LOG_INFO("Matrix multiplication on dense matrix.");
    LOG_DEBUG("Input (" << A.rows() << " x " << A.cols() << ") times (" << B.rows() << " x "
                        << B.cols() << ')');
    // M: rows of A, K: shared dimension, N: columns of B
    const size_type M = A.rows(), K = A.cols(), N = B.cols();

    // Result matrix C is initialized to zero and stored in Row-Major format
    matrix<T> C(M, N, T(0));

    // Use __restrict to tell the compiler these pointers do not overlap (aliasing optimization)
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = la::util::BLOCK_SIZE;
    static_assert(la::util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // Parallelize over the row blocks of the result matrix C
    // execution::par_unseq allows both multi-threading and SIMD vectorization
    auto i_blocks = la::util::create_block_indices(0, M, block_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#else
    std::for_each(i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#endif
        // Block-based tiling to keep data within the L1/L2 CPU caches
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                // Calculate the boundaries for the current tile, handling edge
                // cases
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type j_limit = std::min(j_block + block_size, N);

                // Start of the micro-kernel (the actual computation)
                for (size_type i = i_block; i < i_limit; ++i) {
                    for (size_type k = k_block; k < k_limit; ++k) {

                        // Access A(i, k): Scalar is reused for the entire 'j'
                        // loop below
                        const T temp_a = a_ptr[i * K + k];

                        // Optimization: Pre-calculate pointers for the contiguous
                        // row segments C is Row-Major, so C(i, j) starts at i * N
                        T *__restrict c_row = &c_ptr[i * N];

                        // Note: Even though B is COLUMN_WISE in the type, the
                        // logic treats the k-dimension as contiguous (b_ptr[k *
                        // N]). This implies the algorithm assumes B is being read
                        // like a Row-Major matrix.
                        const T *__restrict b_row = &b_ptr[k * N];

                        // Innermost loop: Contiguous access for both C and B
                        // This is the primary target for Auto-Vectorization
                        // (SIMD)
                        for (size_type j = j_block; j < j_limit; ++j) {
                            c_row[j] += temp_a * b_row[j];
                        }
                    }
                }
            }
        }
    });

    return C;
}

template <typename T>
void transpose_matrix_multiplication<T>::multiply(const sparse_matrix<T> &A, const vector<T> &x,
                                                  vector<T> &y, const bool y_is_zero)
{
    SHAPE_ASSERT(x.rows() == A.rows(), "Vector and matrix dimension not aligned");
    LOG_DEBUG("Transposed matrix times vector");
    const size_type num_rows = A.rows();
    const size_type num_cols = A.cols();
    const size_type *__restrict row_ptr = A.begin_row_ptr();
    const size_type *__restrict col_indices = A.begin_col_idx();
    const T *__restrict values = A.begin();
    const T *__restrict x_data = x.vals();
    if (y.rows() != num_cols) {
        y.resize(num_cols, T(0));
    } else if (!y_is_zero) {
        y = T(0);
    }
    T *y_data = y.vals();
    std::vector<size_type> row_indices(num_rows);
    std::iota(row_indices.begin(), row_indices.end(), 0);

    std::for_each(
#ifdef PARALLEL
        execution::par_unseq,
#endif
        row_indices.begin(), row_indices.end(), [&](size_type i) {
            const T xi = x_data[i];

            for (size_type k = row_ptr[i]; k < row_ptr[i + 1]; ++k) {
                const size_type j = col_indices[k];
                const T val = values[k];

                // Create an atomic reference to the specific element in the output vector
                std::atomic_ref<T> target(y_data[j]);

                // Perform a thread-safe addition
                T current = target.load(std::memory_order_relaxed);
                T desired = current + (val * xi);
                while (!target.compare_exchange_weak(current, desired, std::memory_order_relaxed,
                                                     std::memory_order_relaxed)) {
                    desired = current + (val * xi);
                }
            }
        });
}

} // namespace algorithm
} // namespace la

#endif
