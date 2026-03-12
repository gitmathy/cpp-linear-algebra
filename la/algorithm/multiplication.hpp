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
#include "la/util/block_helper.hpp"
#include "la/util/constants.hpp"
#include "la/util/types.hpp"
#include <algorithm>
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

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// ROW_WISE RESULT
//----------------

template <typename T>
matrix<T> matrix_multiplication<T>::multiply(const matrix<T> &A, const matrix<T> &B)
{
    SHAPE_ASSERT(A.cols() == B.rows(), "matrix_multiplication: invalid dimension");
    LOG_INFO("Matrix multiplication.");
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

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // Parallelize over the row blocks of the result matrix C
    // execution::par_unseq allows both multi-threading and SIMD vectorization
    auto i_blocks = util::create_block_indices(0, M, block_size);
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

} // namespace algorithm
} // namespace la

#endif
