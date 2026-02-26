/// Part of the project "cpp-linear-algebra"
///
/// @file includes/algorithms/multiplication.hpp
/// @brief Definition and declaration of matrix-matrix multiplication
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHMS_MULTIPLICATION_H
#define LA_ALGORITHMS_MULTIPLICATION_H

#include "includes/matrix.hpp"
#include "includes/settings.hpp"
#include <algorithm>
#include <vector>

namespace la {
namespace algorithm {

const size_type BLOCK_SIZE = size_type(64);

template <typename T>
class matrix_multiplication_row
{
private:
    static matrix<T, ROW_WISE> mult_row_col(const matrix<T, ROW_WISE> &A,
                                            const matrix<T, COLUMN_WISE> &B);

    static matrix<T, ROW_WISE> mult_row_row(const matrix<T, ROW_WISE> &A,
                                            const matrix<T, ROW_WISE> &B);

    static matrix<T, ROW_WISE> mult_col_row(const matrix<T, COLUMN_WISE> &A,
                                            const matrix<T, ROW_WISE> &B);

    /// @brief Column * column yielding a row matrix (no transpose since this is a small matrix)
    static matrix<T, ROW_WISE> mult_col_col_small(const matrix<T, COLUMN_WISE> &A,
                                                  const matrix<T, COLUMN_WISE> &B);

    /// @brief Column * column yielding a row matrix (transpose blocks for better memory acces)
    static matrix<T, ROW_WISE> mult_col_col_big(const matrix<T, COLUMN_WISE> &A,
                                                const matrix<T, COLUMN_WISE> &B);

    static std::vector<size_type> create_block_indices(size_type total, size_type block_size)
    {
        size_type num_blocks = (total + block_size - 1) / block_size;
        std::vector<size_type> indices(num_blocks);
        for (size_type i = 0; i < num_blocks; ++i) {
            indices[i] = i * block_size;
        }
        return indices;
    }

public:
    template <storage_type StorageLeftT, storage_type StorageRightT>
    static matrix<T, ROW_WISE> multiply(const matrix<T, StorageLeftT> &A,
                                        const matrix<T, StorageRightT> &B);
};

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

// This is the best case
template <typename T>
matrix<T, ROW_WISE> matrix_multiplication_row<T>::mult_row_col(const matrix<T, ROW_WISE> &A,
                                                               const matrix<T, COLUMN_WISE> &B)
{
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0));
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();
    const size_type block_size = BLOCK_SIZE;

    auto i_blocks = create_block_indices(M, block_size);

    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type j_limit = std::min(j_block + block_size, N);

                for (size_type i = i_block; i < i_limit; ++i) {
                    for (size_type k = k_block; k < k_limit; ++k) {
                        const T temp_a = a_ptr[i * K + k]; // T statt double
                        T *__restrict c_row = &c_ptr[i * N];
                        const T *__restrict b_row = &b_ptr[k * N];

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
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0));
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();
    const size_type block_size = BLOCK_SIZE;

    auto i_blocks = create_block_indices(M, block_size);

    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type j_limit = std::min(j_block + block_size, N);

                for (size_type i = i_block; i < i_limit; ++i) {
                    for (size_type k = k_block; k < k_limit; ++k) {
                        const T temp_a = a_ptr[i * K + k]; // T statt double
                        T *__restrict c_row = &c_ptr[i * N];
                        const T *__restrict b_row = &b_ptr[k * N];

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
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0));
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();
    const size_type block_size = BLOCK_SIZE;

    auto i_blocks = create_block_indices(M, block_size);

    std::for_each(execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
        for (size_type k_block = 0; k_block < K; k_block += block_size) {
            for (size_type j_block = 0; j_block < N; j_block += block_size) {

                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type i_limit = std::min(i_block + block_size, M);
                const size_type j_limit = std::min(j_block + block_size, N);

                for (size_type k = k_block; k < k_limit; ++k) {
                    const T *__restrict a_col_k = &a_ptr[k * M];
                    const T *__restrict b_row_k = &b_ptr[k * N];

                    for (size_type i = i_block; i < i_limit; ++i) {
                        const T val_a = a_col_k[i];
                        T *__restrict c_row_i = &c_ptr[i * N];
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
    const size_type M = A.rows();
    const size_type K = A.cols(); // A ist Column-Major
    const size_type N = B.cols(); // B ist Column-Major
    matrix<T, ROW_WISE> C(M, N, T(0));
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();
    const size_type block_size = BLOCK_SIZE;
    for (size_type i_block = 0; i_block < M; i_block += block_size) {
        for (size_type j_block = 0; j_block < N; j_block += block_size) {
            for (size_type k_block = 0; k_block < K; k_block += block_size) {
                for (size_type i = i_block; i < std::min(i_block + block_size, M); ++i) {
                    T *__restrict c_row_i = &c_ptr[i * N];
                    for (size_type j = j_block; j < std::min(j_block + block_size, N); ++j) {
                        T sum = 0;
                        const T *__restrict b_col_j = &b_ptr[j * K];
                        for (size_type k = k_block; k < std::min(k_block + block_size, K); ++k) {
                            sum += a_ptr[k * M + i] * b_col_j[k];
                        }
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
    const size_type M = A.rows(), K = A.cols(), N = B.cols();
    matrix<T, ROW_WISE> C(M, N, T(0));
    const T *__restrict a_ptr = A.vals();
    const T *__restrict b_ptr = B.vals();
    T *__restrict c_ptr = C.vals();

    // Die Blockgröße sollte so gewählt sein, dass der a_buffer sicher in den L1-Cache passt.
    // 64 * sizeof(double) = 512 Byte -> passt locker in 32KB L1.
    const size_type block_size = BLOCK_SIZE;

    auto i_blocks = create_block_indices(M, block_size);

    std::for_each(
        std::execution::par_unseq, i_blocks.begin(), i_blocks.end(), [&](size_type i_block) {
            // Lokaler Buffer auf dem Stack des jeweiligen Threads
            T a_buffer[BLOCK_SIZE];

            for (size_type k_block = 0; k_block < K; k_block += block_size) {
                const size_type k_limit = std::min(k_block + block_size, K);
                const size_type i_limit = std::min(i_block + block_size, M);

                for (size_type i = i_block; i < i_limit; ++i) {

                    // SCHRITT 1: "On-the-fly" Teil-Transposition
                    // Wir kopieren den gestreuten Zeilen-Ausschnitt von A in den linearen Buffer.
                    // A ist Col-Major -> Zugriff: k * M + i
                    for (size_type k = k_block; k < k_limit; ++k) {
                        a_buffer[k - k_block] = a_ptr[k * M + i];
                    }

                    T *__restrict c_row = &c_ptr[i * N];

                    // SCHRITT 2: Berechne die Spalten von B gegen den Buffer
                    for (size_type j = 0; j < N; ++j) { // Hier kann man auch j-Tiling nutzen
                        const T *__restrict b_col_j = &b_ptr[j * K + k_block];
                        T sum = 0;

                        // Dieser Loop ist jetzt PERFEKT linear (beide Quellen + SIMD-fähig)
                        for (size_type k_sub = 0; k_sub < (k_limit - k_block); ++k_sub) {
                            sum += a_buffer[k_sub] * b_col_j[k_sub];
                        }

                        if (k_block == 0)
                            c_row[j] = sum;
                        else
                            c_row[j] += sum;
                    }
                }
            }
        });

    return C;
}

} // namespace algorithm
} // namespace la

#endif
