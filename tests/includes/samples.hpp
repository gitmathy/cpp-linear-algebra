#ifndef LA_TEST_SAMPLES_H
#define LA_TEST_SAMPLES_H

#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include <deque>
#include <memory>

namespace la {
namespace test {

/// @brief Default size for vectors
const size_type VECTOR_SIZE = 100000000;

/// @brief Default size of matrix rows
const size_type MATRIX_ROWS = 1000;

/// @brief Default size of matrix columns
const size_type MATRIX_COLUMNS = 100000;

/// @brief Storing a set of vectors and matrices which can be used by the performance tests. This
/// helps to not allocate memory in every single performance test
template <typename T>
class sample_la_structures
{
private:
    /// @brief Set of vectors used for testing
    std::deque<vector<T>> p_vectors;

    /// @brief Set of row-wise stored matrices used for testing
    std::deque<matrix<T, ROW_WISE>> p_row_matrices;

    /// @brief Set of column-wise stored matrices used for testing
    std::deque<matrix<T, COLUMN_WISE>> p_col_matrices;

    /// @brief Default sizes of vectors and matrices
    size_type p_vec_rows, p_mat_rows, p_mat_cols;

public:
    /// @brief Allocate memory for all vectors and matrices and initialize them with random values
    sample_la_structures(size_type vec_n, size_type mat_m, size_type mat_n, size_type samples = 3);

    /// @brief Delete the copy constructor as we do not want to have copies
    sample_la_structures(const sample_la_structures &) = delete;

    /// @brief Make sure, all matrices and vectors have the default size, if size is changed, assign
    /// random values
    void reset();

    /// @brief Adjust size of vectors and matrices for a given test (without changing the default
    /// size)
    void adjust(const size_type vec_n, const size_type mat_m, const size_type mat_n);

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
    inline const matrix<T, ROW_WISE> &row_mat(size_type i) const { return p_row_matrices[i]; }
    /// @brief Get i'th row-wise stored matrix for writing
    inline matrix<T, ROW_WISE> &row_mat(size_type i) { return p_row_matrices[i]; }

    /// @brief Get i'th column-wise stored matrix for reading
    inline const matrix<T, COLUMN_WISE> &col_mat(size_type i) const { return p_col_matrices[i]; }
    /// @brief Get i'th column-wise stored matrix for writing
    inline matrix<T, COLUMN_WISE> &col_mat(size_type i) { return p_col_matrices[i]; }
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
                    size_type mat_cols = MATRIX_COLUMNS);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
sample_la_structures<T>::sample_la_structures(size_type vec_n, size_type mat_m, size_type mat_n,
                                              size_type samples)
    : p_vectors(samples, vector<T>()), p_row_matrices(samples, matrix<T, ROW_WISE>()),
      p_col_matrices(samples, matrix<T, COLUMN_WISE>()), p_vec_rows(vec_n), p_mat_rows(mat_m),
      p_mat_cols(mat_n)
{
    reset();
}

template <typename T>
void sample_la_structures<T>::reset()
{
    adjust(p_vec_rows, p_mat_rows, p_mat_cols);
}

template <typename T>
void sample_la_structures<T>::adjust(const size_type vec_n, const size_type mat_m,
                                     const size_type mat_n)
{
    for (auto &vec : p_vectors) {
        if (vec.rows() != vec_n) {
            std::cout << "  * Resizing vectors from " << vec.rows() << " to " << vec_n << std::endl;
            vec.allocate(vec_n);
            init(vec);
        }
    }
    for (auto &mat : p_row_matrices) {
        if (mat.rows() != mat_m || mat.cols() != mat_n) {
            std::cout << "  * Resizing row matrices from (" << mat.rows() << " x " << mat.cols()
                      << ") to (" << mat_m << " x " << mat_n << ")" << std::endl;
            mat.allocate(mat_m, mat_n);
            init(mat);
        }
    }
    for (auto &mat : p_col_matrices) {
        if (mat.rows() != mat_m || mat.cols() != mat_n) {
            std::cout << "  * Resizing row matrices from (" << mat.rows() << " x " << mat.cols()
                      << ") to (" << mat_m << " x " << mat_n << ")" << std::endl;
            mat.allocate(mat_m, mat_n);
            init(mat);
        }
    }
}

} // namespace test
} // namespace la

#endif
