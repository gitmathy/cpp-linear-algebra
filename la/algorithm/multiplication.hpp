/// Part of the project "cpp-linear-algebra"
///
/// @file includes/algorithms/multiplication.hpp
/// @brief Definition and declaration of matrix-matrix multiplication
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_MULTIPLICATION_HPP
#define LA_ALGORITHM_MULTIPLICATION_HPP

#include "la/data_structure/matrix.hpp"
#include "la/util/constants.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <vector>

namespace la {
namespace algorithm {

/// @brief Helper function to create an index vector used for the execution policy
inline std::vector<size_type> create_block_indices(size_type total, size_type block_size)
{
    size_type num_blocks = (total + block_size - 1) / block_size;
    std::vector<size_type> indices(num_blocks);
    for (size_type i = 0; i < num_blocks; ++i) {
        indices[i] = i * block_size;
    }
    return indices;
}

/// @brief Multiplying matrices resulting in row wise storage
///
/// All of the implementations are making use of std::executions to parallel executions via
/// for_each. Moreover, the memory access is optimized w.r.t. alignments and also with blocking
/// strategies.
/// @tparam T The value type of the matrix elements (must be a primary type)
template <typename T>
class matrix_multiplication_row
{
private:
    /// @brief Multiply matrices row*col
    static matrix<T, ROW_WISE> mult_row_col(const matrix<T, ROW_WISE> &A,
                                            const matrix<T, COLUMN_WISE> &B);

    /// @brief Multiply matrices row*row
    static matrix<T, ROW_WISE> mult_row_row(const matrix<T, ROW_WISE> &A,
                                            const matrix<T, ROW_WISE> &B);

    /// @brief Multiply matrices col*row

    static matrix<T, ROW_WISE> mult_col_row(const matrix<T, COLUMN_WISE> &A,
                                            const matrix<T, ROW_WISE> &B);

    /// @brief Column * column yielding a row matrix (no transpose since this is a small matrix)
    static matrix<T, ROW_WISE> mult_col_col_small(const matrix<T, COLUMN_WISE> &A,
                                                  const matrix<T, COLUMN_WISE> &B);

    /// @brief Column * column yielding a row matrix (transpose blocks for better memory access)
    static matrix<T, ROW_WISE> mult_col_col_big(const matrix<T, COLUMN_WISE> &A,
                                                const matrix<T, COLUMN_WISE> &B);

public:
    /// @brief Multiplying two matrices A and B of different storage types
    /// @tparam StorageLeftT
    /// @tparam StorageRightT
    /// @param A left matrix
    /// @param B right matrix
    /// @return A*B in row wise storage format
    template <storage_type StorageLeftT, storage_type StorageRightT>
    static matrix<T, ROW_WISE> multiply(const matrix<T, StorageLeftT> &A,
                                        const matrix<T, StorageRightT> &B);
};

/// @brief Multiplying matrices resulting in column wise storage
///
/// All of the implementations are making use of std::executions to parallel executions via
/// for_each. Moreover, the memory access is optimized w.r.t. alignments and also with blocking
/// strategies.
/// @tparam T The value type of the matrix elements (must be a primary type)
template <typename T>
class matrix_multiplication_col
{
private:
    /// @brief Multiply matrices row*col
    static matrix<T, COLUMN_WISE> mult_row_col(const matrix<T, ROW_WISE> &A,
                                               const matrix<T, COLUMN_WISE> &B);

    /// @brief Multiply matrices row*row
    static matrix<T, COLUMN_WISE> mult_row_row(const matrix<T, ROW_WISE> &A,
                                               const matrix<T, ROW_WISE> &B);

    /// @brief Multiply matrices col*row

    static matrix<T, COLUMN_WISE> mult_col_row(const matrix<T, COLUMN_WISE> &A,
                                               const matrix<T, ROW_WISE> &B);

    /// @brief Column * column yielding a column matrix
    static matrix<T, COLUMN_WISE> mult_col_col(const matrix<T, COLUMN_WISE> &A,
                                               const matrix<T, COLUMN_WISE> &B);

public:
    /// @brief Multiplying two matrices A and B of different storage types
    /// @tparam StorageLeftT
    /// @tparam StorageRightT
    /// @param A left matrix
    /// @param B right matrix
    /// @return A*B in column wise storage format
    template <storage_type StorageLeftT, storage_type StorageRightT>
    static matrix<T, COLUMN_WISE> multiply(const matrix<T, StorageLeftT> &A,
                                           const matrix<T, StorageRightT> &B);
};

// ===============================================
// M A T R I X   M E M B E R
// ===============================================

} // end of namespace algorithm

template <typename T, storage_type StorageT>
template <typename MatTypeLeft, typename MatTypeRight>
matrix<T, StorageT> &matrix<T, StorageT>::operator=(
    const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult)
{
    matrix<T, StorageT> temp;
    if constexpr (StorageT == ROW_WISE) {
        temp = algorithm::matrix_multiplication_row<T>::multiply(mat_mult.left, mat_mult.right);
    } else {
        temp = algorithm::matrix_multiplication_col<T>::multiply(mat_mult.left, mat_mult.right);
    }
    *this = std::move(temp);
    return *this;
}

namespace algorithm {

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// ROW_WISE RESULT
//----------------

template <typename T>
template <storage_type StorageLeftT, storage_type StorageRightT>
matrix<T, ROW_WISE> matrix_multiplication_row<T>::multiply(const matrix<T, StorageLeftT> &A,
                                                           const matrix<T, StorageRightT> &B)
{
    if constexpr (StorageLeftT == ROW_WISE && StorageRightT == ROW_WISE) {
        return mult_row_row(A, B);
    }
    if constexpr (StorageLeftT == ROW_WISE && StorageRightT == COLUMN_WISE) {
        return mult_row_col(A, B);
    }
    if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == ROW_WISE) {
        return mult_col_row(A, B);
    }
    if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == COLUMN_WISE) {
        if (A.rows() * A.cols() > 512 * 512) {
            // bigger matrix
            return mult_col_col_big(A, B);
        } else {
            // smaller matrix A
            return mult_col_col_small(A, B);
        }
    }
}

template <typename T>
matrix<T, ROW_WISE> matrix_multiplication_row<T>::mult_row_col(const matrix<T, ROW_WISE> &A,
                                                               const matrix<T, COLUMN_WISE> &B)
{
    // M: rows of A, K: shared dimension, N: columns of B
    const size_type M = A.rows(), K = A.cols(), N = B.cols();

    // Result matrix C is initialized to zero and stored in Row-Major format
    matrix<T, ROW_WISE> C(M, N, T(0));

    // Use __restrict to tell the compiler these pointers do not overlap (aliasing optimization)
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // Parallelize over the row blocks of the result matrix C
    // execution::par_unseq allows both multi-threading and SIMD vectorization
    auto i_blocks = create_block_indices(M, block_size);
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
matrix<T, ROW_WISE> matrix_multiplication_row<T>::mult_row_row(const matrix<T, ROW_WISE> &A,
                                                               const matrix<T, ROW_WISE> &B)
{
    // 1. DIMENSIONS & INITIALIZATION
    // M: Rows of A, K: Columns of A (and Rows of B), N: Columns of B
    const size_type M = A.rows(), K = A.cols(), N = B.cols();

    // Result matrix C is allocated and zero-initialized in Row-Major format.
    matrix<T, ROW_WISE> C(M, N, T(0));

    // Pointer Aliasing Optimization: __restrict tells the compiler these memory
    // regions don't overlap, enabling more aggressive SIMD vectorization.
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // 2. PARALLELIZATION
    // Parallelize over the row-blocks (i) of C.
    // execution::par_unseq enables both multi-threading and SIMD/Vectorization.
    auto i_blocks = create_block_indices(M, block_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#else
    std::for_each(i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#endif
        // 3. CACHE BLOCKING (TILING)
        // These loops split the large matrices into 'tiles' that fit into the
        // L1/L2 cache.
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                // Determine the current tile boundaries, ensuring we don't exceed
                // matrix dimensions.
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type j_limit = std::min(j_block + block_size, N);

                // 4. MICRO-KERNEL (The Computational Core)
                for (size_type i = i_block; i < i_limit; ++i) {
                    for (size_type k = k_block; k < k_limit; ++k) {

                        // Access A(i, k): This value is constant for the duration
                        // of the 'j' loop. Holding it in a register (temp_a)
                        // reduces memory traffic.
                        const T temp_a = a_ptr[i * K + k];

                        // Optimization: Pre-calculate the starting pointers for
                        // the current row segment. Both C and B are being
                        // accessed as Row-Major here (stride-1 in j).
                        T *__restrict c_row = &c_ptr[i * N];
                        const T *__restrict b_row = &b_ptr[k * N];

                        // 5. INNERMOST LOOP (AXPY Operation)
                        // This is the performance "hot spot".
                        // It updates a row-segment of C by adding a scaled
                        // row-segment of B. Memory Access: Contiguous Read (B)
                        // and Contiguous Read/Write (C). This pattern is ideal
                        // for CPU Hardware Prefetching and Auto-Vectorization.
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
matrix<T, ROW_WISE> matrix_multiplication_row<T>::mult_col_row(const matrix<T, COLUMN_WISE> &A,
                                                               const matrix<T, ROW_WISE> &B)
{
    // 1. SETUP & ALIASING OPTIMIZATION
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0));

    // __restrict informs the compiler that A, B, and C pointers point to
    // unique memory locations, enabling more aggressive optimization.
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // 2. PARALLELIZATION
    // Parallelize over vertical blocks (rows i) of C.
    auto i_blocks = create_block_indices(M, block_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#else
    std::for_each(i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#endif
        // 3. CACHE BLOCKING (TILING)
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type j_limit = std::min(j_block + block_size, N);

                // 4. MICRO-KERNEL
                // We iterate over k (the shared dimension) outside the i-loop.
                for (size_type k = k_block; k < k_limit; ++k) {

                    // Optimization: Pre-locate the specific column k of A
                    // and the specific row k of B.
                    // A is COLUMN_WISE, so column k is contiguous.
                    const T *__restrict a_col_k = &a_ptr[k * M];
                    // B is ROW_WISE, so row k is contiguous.
                    const T *__restrict b_row_k = &b_ptr[k * N];

                    for (size_type i = i_block; i < i_limit; ++i) {

                        // val_a = A(i, k). Since i moves down the column k of A,
                        // this access is contiguous (stride-1).
                        const T val_a = a_col_k[i];

                        // Pre-locate the row segment in result matrix C.
                        T *__restrict c_row_i = &c_ptr[i * N];

                        // 5. INNERMOST LOOP (Vectorized Row Update)
                        // Memory: both c_row_i and b_row_k are accessed as
                        // j-segments. Since both C and B are ROW_WISE, this is
                        // unit-stride access. The compiler can easily transform
                        // this into SIMD (AVX) instructions.
                        for (size_type j = j_block; j < j_limit; ++j) {
                            c_row_i[j] += val_a * b_row_k[j];
                        }
                    }
                }
            }
        }
    });
    return C;
}

template <typename T>
matrix<T, ROW_WISE>
matrix_multiplication_row<T>::mult_col_col_small(const matrix<T, COLUMN_WISE> &A,
                                                 const matrix<T, COLUMN_WISE> &B)
{
    // 1. SETUP
    const size_type M = A.rows();
    const size_type K = A.cols(); // Shared dimension
    const size_type N = B.cols();

    // Result C is Row-Major. Each dot product result is stored in one cell C(i, j).
    matrix<T, ROW_WISE> C(M, N, T(0));

    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // 2. SIX-LEVEL NESTED LOOP (Tiling + Computation)
    // The first three loops handle the "Blocks" or "Tiles".
    for (size_type i_block = 0; i_block < M; i_block += block_size) {
        for (size_type j_block = 0; j_block < N; j_block += block_size) {
            for (size_type k_block = 0; k_block < K; k_block += block_size) {

                // 3. MICRO-KERNEL (The internal block loops)
                for (size_type i = i_block; i < std::min(i_block + block_size, M); ++i) {

                    // Optimization: Pre-locate row i of the result matrix C (Row-Major)
                    T *__restrict c_row_i = &c_ptr[i * N];

                    for (size_type j = j_block; j < std::min(j_block + block_size, N); ++j) {

                        // Local accumulation register for the dot product
                        T sum = 0;

                        // Optimization: Pre-locate column j of matrix B (Column-Major)
                        // B(k, j) is contiguous over the index k.
                        const T *__restrict b_col_j = &b_ptr[j * K];

                        // 4. INNERMOST LOOP (Dot Product)
                        // This loop calculates a partial sum for C(i, j) across the k-block.
                        // Memory Pattern:
                        // - A(k, i) is at [k * M + i]. Since i is fixed, this is unit-stride
                        // over k.
                        // - B(k, j) is at b_col_j[k]. This is also unit-stride over k.
                        for (size_type k = k_block; k < std::min(k_block + block_size, K); ++k) {
                            sum += a_ptr[k * M + i] * b_col_j[k];
                        }

                        // 5. SELECTIVE UPDATE
                        // If this is the first k_block, we overwrite (initialize) C(i, j).
                        // Otherwise, we accumulate into C(i, j).
                        if (k_block == 0) {
                            c_row_i[j] = sum;
                        } else {
                            c_row_i[j] += sum;
                        }
                    }
                }
            }
        }
    }
    return C;
}

template <typename T>
matrix<T, ROW_WISE> matrix_multiplication_row<T>::mult_col_col_big(const matrix<T, COLUMN_WISE> &A,
                                                                   const matrix<T, COLUMN_WISE> &B)
{
    // 1. SETUP & ALIASING
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0)); // Output is Row-Major
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;
    static_assert(util::BLOCK_SIZE <= 256, "util::BLOCK_SIZE too large for stack buffer");

    // 2. PARALLELIZATION
    // Parallelize over the rows (i) of C.
    auto i_blocks = create_block_indices(M, block_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#else
    std::for_each(i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
#endif
        // 3. L1 CACHE BUFFERING (The "Secret Sauce")
        // This buffer lives on the thread's stack (very fast).
        // It is used to store a contiguous segment of Row i from Matrix A.
        // Since A is Column-Major, Row i is normally strided.
        // Collecting it into a buffer makes the inner dot-product unit-stride.
        T a_buffer[util::BLOCK_SIZE];

        for (size_type j_block = 0; j_block < N; j_block += block_size) {
            for (size_type k_block = 0; k_block < K; k_block += block_size) {

                // Determine current tile boundaries
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type j_limit = std::min(j_block + block_size, N);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type k_len = k_limit - k_block;

                // 4. MICRO-KERNEL START
                for (size_type i = i_block; i < i_limit; ++i) {

                    // --- STEP A: PACKING ---
                    // Gather elements of A(i, k) for the current k-block.
                    // A is Col-Major, so we jump by M to get the next k.
                    // After this loop, a_buffer contains a contiguous segment of
                    // Row i.
                    for (size_type k = 0; k < k_len; ++k) {
                        a_buffer[k] = a_ptr[(k_block + k) * M + i];
                    }

                    // Optimization: Locate Row i in Row-Major C
                    T *__restrict c_row = &c_ptr[i * N];

                    for (size_type j = j_block; j < j_limit; ++j) {
                        // --- STEP B: CONTIGUOUS DOT PRODUCT ---
                        // B is Col-Major, so Column j is already contiguous over
                        // k.
                        const T *__restrict b_col_j = &b_ptr[j * K + k_block];
                        T sum = 0;

                        // BOTH a_buffer and b_col_j are now unit-stride
                        // (stride-1). This allows the compiler to use FMA (Fused
                        // Multiply-Add) and AVX vector instructions perfectly.
                        for (size_type k_sub = 0; k_sub < k_len; ++k_sub) {
                            sum += a_buffer[k_sub] * b_col_j[k_sub];
                        }

                        // --- STEP C: SELECTIVE ACCUMULATION ---
                        if (k_block == 0)
                            c_row[j] = sum;
                        else
                            c_row[j] += sum;
                    }
                }
            }
        }
    });
    return C;
}

// COLUMN_WISE RESULT
//-------------------

template <typename T>
template <storage_type StorageLeftT, storage_type StorageRightT>
matrix<T, COLUMN_WISE> matrix_multiplication_col<T>::multiply(const matrix<T, StorageLeftT> &A,
                                                              const matrix<T, StorageRightT> &B)
{
    if constexpr (StorageLeftT == ROW_WISE && StorageRightT == ROW_WISE) {
        return mult_row_row(A, B);
    }
    if constexpr (StorageLeftT == ROW_WISE && StorageRightT == COLUMN_WISE) {
        return mult_row_col(A, B);
    }
    if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == ROW_WISE) {
        return mult_col_row(A, B);
    }
    if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == COLUMN_WISE) {
        return mult_col_col(A, B);
    }
}

template <typename T>
matrix<T, COLUMN_WISE> matrix_multiplication_col<T>::mult_row_col(const matrix<T, ROW_WISE> &A,
                                                                  const matrix<T, COLUMN_WISE> &B)
{
    // 1. SETUP & ALIASING
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    // Result C is Column-Major. Each column will be calculated independently.
    matrix<T, COLUMN_WISE> C(M, N, T(0));

    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    // 2. PARALLELIZATION (Outer Dimension)
    // Parallelizing over 'j' (columns of C) is ideal for Column-Major storage.
    // Each thread works on a contiguous, independent vertical slice of memory.
    auto j_blocks = create_block_indices(N, util::BLOCK_SIZE);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#else
    std::for_each(j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#endif
        // 3. CACHE BLOCKING (TILING)
        for (size_type i_block = 0; i_block < M; i_block += util::BLOCK_SIZE) {
            for (size_type k_block = 0; k_block < K; k_block += util::BLOCK_SIZE) {

                const size_type j_limit = std::min(j_block + util::BLOCK_SIZE, N);
                const size_type i_limit = std::min(i_block + util::BLOCK_SIZE, M);
                const size_type k_limit = std::min(k_block + util::BLOCK_SIZE, K);

                // 4. MICRO-KERNEL START
                for (size_type j = j_block; j < j_limit; ++j) {

                    // Optimization: Pre-locate the specific column j in C and B.
                    // Both C and B are COLUMN_WISE, so column j is a contiguous
                    // array.
                    T *__restrict c_col_j = &c_ptr[j * M];
                    const T *__restrict b_col_j = &b_ptr[j * K];

                    for (size_type i = i_block; i < i_limit; ++i) {
                        // Local accumulation register to minimize memory writes
                        // to C
                        T sum = 0;

                        // Optimization: Pre-locate row i of A.
                        // A is ROW_WISE, so row i is a contiguous array.
                        const T *__restrict a_row_i = &a_ptr[i * K];

                        // 5. INNERMOST LOOP (The Performance Core)
                        // This is a unit-stride DOT PRODUCT.
                        // Memory:
                        // - a_row_i[k] accesses memory linearly (stride-1).
                        // - b_col_j[k] accesses memory linearly (stride-1).
                        // This allows the CPU to use the maximum memory bandwidth
                        // and SIMD units.
                        for (size_type k = k_block; k < k_limit; ++k) {
                            sum += a_row_i[k] * b_col_j[k];
                        }

                        // Update the Column-Major result.
                        // Note: i is the inner loop dimension for j, matching C's
                        // layout.
                        c_col_j[i] += sum;
                    }
                }
            }
        }
    });
    return C;
}

template <typename T>
matrix<T, COLUMN_WISE> matrix_multiplication_col<T>::mult_row_row(const matrix<T, ROW_WISE> &A,
                                                                  const matrix<T, ROW_WISE> &B)
{
    // 1. DIMENSIONS & STORAGE INITIALIZATION
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    // Result C is Column-Major: contiguous over i, strided over j.
    matrix<T, COLUMN_WISE> C(M, N, T(0));

    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    const size_type block_size = util::BLOCK_SIZE;

    // 2. PARALLELIZATION (Outer Dimension)
    // Parallelizing over j (columns of C) ensures each thread works on
    // a separate, contiguous memory block in Column-Major storage.
    auto j_blocks = create_block_indices(N, block_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#else
    std::for_each(j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#endif
        // 3. L1 CACHE BUFFER (The "Packing" Buffer)
        // This stack-allocated buffer stores a contiguous segment of B's column.
        // This turns a strided read (from Row-Major B) into a unit-stride read
        // for the dot-product.
        T b_buffer[util::BLOCK_SIZE];

        for (size_type i_block = 0; i_block < M; i_block += block_size) {
            for (size_type k_block = 0; k_block < K; k_block += block_size) {

                const size_type j_limit = std::min(j_block + block_size, N);
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type k_len = k_limit - k_block;

                // 4. MICRO-KERNEL
                for (size_type j = j_block; j < j_limit; ++j) {

                    // --- STEP A: PACKING ---
                    // B is Row-Major, so B(k, j) is at [k * N + j].
                    // Moving from k to k+1 jumps N elements. We gather these into
                    // b_buffer.
                    for (size_type k = 0; k < k_len; ++k) {
                        b_buffer[k] = b_ptr[(k_block + k) * N + j];
                    }

                    // Pre-locate column j in the Column-Major result matrix C.
                    T *__restrict c_col_j = &c_ptr[j * M];

                    for (size_type i = i_block; i < i_limit; ++i) {
                        // Accumulation register to minimize memory write-back
                        // traffic.
                        T sum = 0;

                        // A is Row-Major, so Row i is contiguous over k.
                        const T *__restrict a_row_i = &a_ptr[i * K + k_block];

                        // --- STEP B: VECTORIZED DOT PRODUCT ---
                        // Both a_row_i and b_buffer are now contiguous in memory
                        // (stride-1). This allows the CPU's SIMD units to perform
                        // 4-8 multiplications per cycle.
                        for (size_type k = 0; k < k_len; ++k) {
                            sum += a_row_i[k] * b_buffer[k];
                        }

                        // Update C(i, j). In Column-Major, this is C_col_j[i].
                        c_col_j[i] += sum;
                    }
                }
            }
        }
    });
    return C;
}

template <typename T>
matrix<T, COLUMN_WISE> matrix_multiplication_col<T>::mult_col_col(const matrix<T, COLUMN_WISE> &A,
                                                                  const matrix<T, COLUMN_WISE> &B)
{
    // 1. SETUP & ALIASING
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    // Result C is Column-Major: contiguous over i, strided over j.
    matrix<T, COLUMN_WISE> C(M, N, T(0));

    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    // 2. PARALLELIZATION
    // Parallelizing over j (columns of C) ensures that threads never write to the
    // same memory addresses, eliminating the need for atomics or mutexes.
    auto j_blocks = create_block_indices(N, util::BLOCK_SIZE);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#else
    std::for_each(j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#endif
        // 3. L1 CACHE BUFFER (Temporal Locality)
        // b_buffer holds a small segment of column j from Matrix B.
        // Even though B is already Column-Major, buffering these K-elements
        // ensures they stay in L1 cache during the entire i-block iteration.
        T b_buffer[util::BLOCK_SIZE];

        for (size_type k_block = 0; k_block < K; k_block += util::BLOCK_SIZE) {
            for (size_type i_block = 0; i_block < M; i_block += util::BLOCK_SIZE) {

                const size_type j_limit = std::min(j_block + util::BLOCK_SIZE, N);
                const size_type k_limit = std::min(k_block + util::BLOCK_SIZE, K);
                const size_type i_limit = std::min(i_block + util::BLOCK_SIZE, M);
                const size_type k_len = k_limit - k_block;

                // 4. MICRO-KERNEL
                for (size_type j = j_block; j < j_limit; ++j) {

                    // --- STEP A: BUFFERING B ---
                    // B is Column-Major, so B(k, j) is contiguous over k.
                    // We pull a k-segment into a buffer to reuse it across the
                    // i-block.
                    for (size_type k = 0; k < k_len; ++k)
                        b_buffer[k] = b_ptr[j * K + (k_block + k)];

                    // Locate the current column j in the result matrix C.
                    T *__restrict c_col = &c_ptr[j * M];

                    // --- STEP B: AXPY OPERATION (Rank-1 Update) ---
                    for (size_type k = 0; k < k_len; ++k) {
                        // val_b is the scalar multiplier for the entire column
                        // segment of A.
                        const T val_b = b_buffer[k];
                        // A is Column-Major, so column k is contiguous over i.
                        const T *__restrict a_col = &a_ptr[(k_block + k) * M];

                        // 5. INNERMOST LOOP (The Hot Spot)
                        // Both C (destination) and A (source) are accessed
                        // linearly (stride-1). This is the "Gold Standard" for
                        // performance:
                        // 1. Easy for the CPU to prefetch.
                        // 2. Ideal for the compiler to use FMA and AVX SIMD
                        // instructions.
                        for (size_type i = i_block; i < i_limit; ++i) {
                            c_col[i] += a_col[i] * val_b;
                        }
                    }
                }
            }
        }
    });
    return C;
}

template <typename T>
matrix<T, COLUMN_WISE> matrix_multiplication_col<T>::mult_col_row(const matrix<T, COLUMN_WISE> &A,
                                                                  const matrix<T, ROW_WISE> &B)
{
    // 1. DIMENSIONS & ALIASING OPTIMIZATION
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    // Result C is Column-Major: contiguous over i, strided over j.
    matrix<T, COLUMN_WISE> C(M, N, T(0));

    // __restrict informs the compiler that A, B, and C pointers point to
    // unique memory locations, enabling more aggressive SIMD optimization.
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    // 2. PARALLELIZATION
    // Parallelizing over j (columns of C) ensures that threads own distinct
    // memory segments, preventing "False Sharing" and race conditions.
    auto j_blocks = create_block_indices(N, util::BLOCK_SIZE);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#else
    std::for_each(j_blocks.begin(), j_blocks.end(), [&](size_type j_block) {
#endif
        // 3. CACHE BLOCKING (TILING)
        // These loops break the computation into tiles that fit into L1/L2 cache.
        for (size_type k_block = 0; k_block < K; k_block += util::BLOCK_SIZE) {
            for (size_type i_block = 0; i_block < M; i_block += util::BLOCK_SIZE) {

                const size_type j_limit = std::min(j_block + util::BLOCK_SIZE, N);
                const size_type k_limit = std::min(k_block + util::BLOCK_SIZE, K);
                const size_type i_limit = std::min(i_block + util::BLOCK_SIZE, M);

                // 4. MICRO-KERNEL START
                for (size_type j = j_block; j < j_limit; ++j) {

                    // Optimization: Locate the current target column j in the
                    // result matrix C.
                    T *__restrict c_col = &c_ptr[j * M];

                    for (size_type k = k_block; k < k_limit; ++k) {

                        // B is Row-Major, so B(k, j) is at [k * N + j].
                        // This scalar remains constant for the entire innermost
                        // 'i' loop.
                        const T val_b = b_ptr[k * N + j];

                        // A is Column-Major, so column k is a contiguous array
                        // over 'i'.
                        const T *__restrict a_col = &a_ptr[k * M];

                        // 5. INNERMOST LOOP (AXPY Operation)
                        // Both C (destination) and A (source) are accessed with
                        // unit-stride (stride-1). This is the ideal pattern for:
                        // - SIMD (AVX/AVX-512) vectorization.
                        // - CPU Hardware Prefetching.
                        // - Maximum memory bandwidth utilization.
                        for (size_type i = i_block; i < i_limit; ++i) {
                            c_col[i] += a_col[i] * val_b;
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
