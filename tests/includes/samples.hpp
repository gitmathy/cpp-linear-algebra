/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/samples.hpp
/// @brief Definition of samples
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_SAMPLES_HPP
#define LA_TEST_INCLUDES_SAMPLES_HPP

#include "la/dense"
#include "la/sparse"
#include "tests/includes/log.hpp"
#include <deque>
#include <memory>
#include <random>
#include <sstream>

namespace la {
namespace test {

/// @brief Default size for vectors
const size_type VECTOR_SIZE = 100000000;

/// @brief Default size of matrix rows
const size_type MATRIX_ROWS = 1000;

/// @brief Default size of matrix columns
const size_type MATRIX_COLUMNS = 200000;

/// @brief Default maximum number of non-zeros per row in a sparse matrix
const size_type SPARSE_MAX_NNZ_ROW = 100;

/// @brief Default number of rows and columns of a sparse matrix
const size_type SPARSE_SIZE = 100000;

/// @brief Storing a set of vectors and matrices which can be used by the performance tests. This
/// helps to not allocate memory in every single performance test
template <typename T>
class sample_la_structures
{
private:
    /// @brief Set of vectors used for testing
    std::deque<vector<T>> p_vectors;

    /// @brief Set of dense matrices used for testing
    std::deque<matrix<T>> p_matrices;

    /// @brief Default sizes of vectors and matrices
    size_type p_vec_rows, p_mat_rows, p_mat_cols, p_sparse_size, p_sparse_max_nnz_row;

    /// @brief A single sparse matrix
    sparse_matrix<T> p_a_sparse;

public:
    /// @brief Allocate memory for all vectors and matrices and initialize them with random values
    sample_la_structures(size_type vec_n, size_type mat_m, size_type mat_n, size_type sparse_size,
                         size_type max_nnz_per_row, size_type samples = 3);

    /// @brief Delete the copy constructor as we do not want to have copies
    sample_la_structures(const sample_la_structures &) = delete;

    /// @brief Make sure, all matrices and vectors have the default size, if size is changed, assign
    /// random values
    void reset();

    /// @brief Adjust size of vectors and matrices for a given test (without changing the default
    /// size)
    void adjust(const size_type vec_n, const size_type mat_m, const size_type mat_n,
                const size_type sparse_size = 0, const size_type max_nnz_per_row = 0);

    /// @brief Get the default size of testing vectors
    inline size_type vec_rows() const { return p_vec_rows; }

    /// @brief Get the default number of rows of matrices
    inline size_type mat_rows() const { return p_mat_rows; }

    /// @brief Get the default number of columns of matrices
    inline size_type mat_cols() const { return p_mat_cols; }

    /// @brief Get number of available samples
    inline size_type size() const { return size_type(p_vectors.size()); }

    /// @brief Get i'th vector for reading
    inline const vector<T> &vec(size_type i) const { return p_vectors[i]; }
    /// @brief Get i'th vector for writing
    inline vector<T> &vec(size_type i) { return p_vectors[i]; }

    /// @brief Get i'th row-wise stored matrix for reading
    inline const matrix<T> &mat(size_type i) const { return p_matrices[i]; }
    /// @brief Get i'th row-wise stored matrix for writing
    inline matrix<T> &mat(size_type i) { return p_matrices[i]; }

    /// @brief Get sparse matrix for reading
    inline const sparse_matrix<T> &sparse_mat() const { return p_a_sparse; }
    /// @brief Get sparse matrix for writing
    inline sparse_matrix<T> &sparse_mat() { return p_a_sparse; }
};

// ===============================================
// H E L P E R   F U N C T I O N S
// ===============================================

/// @brief Get a random value
template <typename T>
inline double get_random()
{
    return T((std::rand() / (T)RAND_MAX) * 2 - 1);
}

/// @brief Initialize x with random values
template <typename la_struct>
inline void init(la_struct &x)
{
    for (auto it = x.begin(); it != x.end(); ++it) {
        *it = get_random<typename la_struct::value_type>();
    }
}

/// @brief Get a reference to the default samples
///
/// This is basically a factory method
std::shared_ptr<sample_la_structures<double>>
get_default_samples(size_type vec_rows = VECTOR_SIZE, size_type mat_rows = MATRIX_ROWS,
                    size_type mat_cols = MATRIX_COLUMNS, size_type sparse_size = SPARSE_SIZE,
                    size_type max_nn_per_row = SPARSE_MAX_NNZ_ROW);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
sample_la_structures<T>::sample_la_structures(size_type vec_n, size_type mat_m, size_type mat_n,
                                              size_type sparse_size, size_type max_nnz_per_row,
                                              size_type samples)
    : p_vectors(samples, vector<T>()), p_matrices(samples, matrix<T>()), p_vec_rows(vec_n),
      p_mat_rows(mat_m), p_mat_cols(mat_n), p_sparse_size(sparse_size),
      p_sparse_max_nnz_row(max_nnz_per_row), p_a_sparse()
{
    reset();
}

template <typename T>
void sample_la_structures<T>::reset()
{
    adjust(p_vec_rows, p_mat_rows, p_mat_cols, p_sparse_size, p_sparse_max_nnz_row);
}

template <typename T>
void sample_la_structures<T>::adjust(const size_type vec_n, const size_type mat_m,
                                     const size_type mat_n, const size_type sparse_size,
                                     const size_type max_nnz_per_row)
{
    std::stringstream strs;
    for (auto &vec : p_vectors) {
        if (vec.rows() != vec_n) {
            strs << "  * Resizing vectors from " << vec.rows() << " to " << vec_n;
            logger::get().log(strs, DEBUG);
            vec.allocate(vec_n);
            init(vec);
        }
    }
    for (auto &mat : p_matrices) {
        if (mat.rows() != mat_m || mat.cols() != mat_n) {
            strs << "  * Resizing row matrices from (" << mat.rows() << " x " << mat.cols()
                 << ") to (" << mat_m << " x " << mat_n << ")";
            logger::get().log(strs, DEBUG);
            mat.allocate(mat_m, mat_n);
            init(mat);
        }
    }
    if (sparse_size > 0 && max_nnz_per_row > 0) {
        strs << "  * Setting up sparse matrix  (" << sparse_size << " x " << sparse_size
             << ") with max " << max_nnz_per_row << " non-zeros per row";
        logger::get().log(strs, DEBUG);
        // setup a sparse matrix builder
        sparse_matrix_builder<T> a_build(sparse_size, sparse_size);
        std::mt19937 gen(42);
        std::uniform_int_distribution<size_type> rand_nnz_row(1, max_nnz_per_row);
        std::uniform_int_distribution<size_type> rand_col_idx(1, sparse_size);
        for (size_type i = 0; i < a_build.rows(); ++i) {
            for (size_type nnz = 0; nnz < rand_nnz_row(gen); ++nnz) {
                a_build(i, rand_col_idx(gen)) = get_random<T>();
            }
        }
        p_a_sparse = std::move(a_build);
    }
}

} // namespace test
} // namespace la

#endif
