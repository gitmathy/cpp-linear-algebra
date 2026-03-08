/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/matrix.hpp
/// @brief Declaration and definition of a dense matrix class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_MATRIX_HPP
#define LA_DATA_STRUCTURE_MATRIX_HPP

#include "la/data_structure/expressions/forward.hpp"
#include "la/util/file_io.hpp"
#include "la/util/macros.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <initializer_list>
#include <ranges>
#include <string>

namespace la {

/// @brief Class representing a dense matrix, i.e., all values are stored in a linear array
/// @tparam T Type of every element
template <typename T>
class matrix
{
public:
    /// @brief Type of every element
    typedef T value_type;

    /// @brief Definition of iterator type
    typedef T *iterator;
    /// @brief Definition of constant iterator type
    typedef const T *citerator;

private:
    /// @brief Storage of the values
    T *p_vals;

    /// @brief Number of rows
    size_type p_rows;

    /// @brief Number of columns
    size_type p_cols;

public:
    /// public variable members

    /// @brief Dimension of a matrix
    const static size_type dimension = size_type(2);

    /// @brief This matrix is dense
    const static bool dense = true;

public:
    /// @brief Default constructor creates an empty matrix
    explicit matrix() : p_vals(nullptr), p_rows(0), p_cols(0) {}

    /// @brief Construct a matrix of given size, initialize elements with 0
    /// @param m number of rows
    /// @param n number of columns
    /// @param val default value for all elements
    explicit matrix(const size_type m, const size_type n, const T &val = T());

    /// @brief Construct a matrix with a list of values
    matrix(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Move a matrix
    explicit matrix(matrix<T> &&rhs) noexcept;

    /// @brief Copy a matrix
    matrix(const matrix<T> &rhs);

    /// @brief Construct from expression
    /// @tparam ExpressionT expression of the operant
    ///
    /// evaluate the expression for every element in the matrix and assigns this value to the matrix
    /// element
    template <typename ExpressionT>
    matrix(const expressions::operant<ExpressionT> &exp);

    /// @brief Constructor from a matrix-matrix multiplication
    /// @tparam MatTypeLeft type of left matrix of the product
    /// @tparam MatTypeRight type of right matrix of the product
    /// @param mat_mult The proxy to the matrix-matrix multiplication
    template <typename MatTypeLeft, typename MatTypeRight>
    matrix(const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult);

    /// @brief Destruct a matrix
    ~matrix() { util::deallocate_aligned(p_vals); }

    /// @brief Allocate memory and set shape
    void allocate(const size_type m, const size_type n);

    /// @brief Resize a matrix. And set all values to val
    /// @param m number of rows
    /// @param n number of columns
    /// @param val value applied to every element of the matrix
    void resize(const size_type m, const size_type n, const T &val = T(0));

    /// @brief Get number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Get number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_rows * p_cols; }

    /// @brief Get first index in row i (also available for i==rows())
    inline size_type row_idx_begin(const size_type i) const;

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type nz_idx) const;

    /// @brief Get element (i,j) for reading
    inline const T &operator()(const size_type i, const size_type j) const;

    /// @brief Get element (i,j) for writing
    inline T &operator()(const size_type i, const size_type j);

    /// @brief Get nz_idx't element for reading
    inline const T &operator()(const size_type nz_idx) const;

    /// @brief Evaluate matrix at (i,j), i.e., (wrapper to (*this)(i,j)))
    inline const T &evaluate(const size_type i, const size_type j) const;

    /// @brief Evaluate matrix at (nz_idx) gives nz_idx'th element (wrapper to (*this)(nz_idx)))
    inline const T &evaluate(const size_type nz_idx) const;

    /// @brief Iterator to begin
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end
    inline iterator end() { return p_vals + p_rows * p_cols; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + p_rows * p_cols; }

    /// @brief Iterator to row begin
    inline iterator row_begin(const size_type i);
    /// @brief Iterator to row end
    inline iterator row_end(const size_type i);

    /// @brief Constant iterator to row begin
    inline citerator row_begin(const size_type i) const;
    /// @brief Constant iterator to row end
    inline citerator row_end(const size_type i) const;

    /// @brief Direct access to the memory. Use with caution
    inline T *vals() { return p_vals; }

    /// @brief Direct access to the memory. Use with caution
    inline T const *vals() const { return p_vals; }

    /// @brief Assign another matrix
    matrix<T> &operator=(const matrix<T> &rhs);

    /// @brief Move assign a matrix
    matrix<T> &operator=(matrix<T> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT>
    matrix<T> &operator=(const expressions::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    matrix<T> &operator=(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Assign the result of a matrix-matrix multiplication
    template <typename MatTypeLeft, typename MatTypeRight>
    matrix<T> &
    operator=(const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult);

    /// @brief Add another matrix
    matrix<T> &operator+=(const matrix<T> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT>
    matrix<T> &operator+=(const expressions::operant<ExpressionT> &exp);

    /// @brief Multiply with a scalar
    matrix<T> &operator*=(const T &rhs);

    /// @brief Multiply from another expression
    template <typename ExpressionT>
    matrix<T> &operator*=(const expressions::operant<ExpressionT> &exp);

    /// @brief Subtract another matrix
    matrix<T> &operator-=(const matrix<T> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT>
    matrix<T> &operator-=(const expressions::operant<ExpressionT> &exp);

    /// @brief Multiply row i with a right hand side
    template <typename ExpressionT>
    T row_multiply(const expressions::operant<ExpressionT> &right, const size_t i);

    /// @brief Apply a function to every entry, i.e., A(i,j)=func(A(i,j))
    /// @tparam function, supports func(T)
    template <typename function>
    matrix<T> &apply_func(function func);

    /// @brief Write matrix to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true) const;

    /// @brief Read matrix from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

// ===============================================
// P U B L I C   F U N C T I O N S
// ===============================================

/// @brief Write a vector to an output stream
template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T> &mat);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
void matrix<T>::allocate(const size_type m, const size_type n)
{
    LOG_DEBUG("Allocating memory for matrix: " << (m * n * sizeof(T)) << " B");
    util::deallocate_aligned(p_vals);
    p_vals = util::allocate_aligned<T>(m * n);
    p_rows = m;
    p_cols = n;
}

template <typename T>
matrix<T>::matrix(const size_type m, const size_type n, const T &val)
    : p_vals(nullptr), p_rows(0), p_cols(0)
{
    resize(m, n, val);
}

template <typename T>
matrix<T>::matrix(const std::initializer_list<std::initializer_list<T>> &init_list)
    : p_vals(nullptr), p_rows(0), p_cols(0)
{
    *this = init_list;
}

// take ownership and leave rhs in a valid empty state
template <typename T>
matrix<T>::matrix(matrix<T> &&rhs) noexcept : p_vals(nullptr), p_rows(0), p_cols(0)
{
    *this = std::move(rhs);
}

template <typename T>
matrix<T>::matrix(const matrix<T> &rhs) : p_vals(nullptr), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    *this = rhs;
}

template <typename T>
template <typename ExpressionT>
matrix<T>::matrix(const expressions::operant<ExpressionT> &exp) : p_vals(nullptr), p_rows(0)
{
    *this = exp;
}

template <typename T>
template <typename MatTypeLeft, typename MatTypeRight>
matrix<T>::matrix(const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult)
{
    *this = mat_mult;
}

template <typename T>
void matrix<T>::resize(const size_type m, const size_type n, const T &val)
{
    LOG_DEBUG("Resizing matrix to (" << m << " x " << n << ')');
    allocate(m, n);
#ifdef PARALLEL
    std::fill(execution::par_unseq, p_vals, p_vals + m * n, val);
#else
    std::fill(p_vals, p_vals + m * n, val);
#endif
}

template <typename T>
inline size_type matrix<T>::row_idx_begin(const size_type i) const
{
    LAYOUT_ASSERT(StorageT == ROW_WISE, "matrix: row_idx_begin only valid for row_wise");
    return i * p_cols;
}

template <typename T>
inline size_type matrix<T>::col_idx(const size_type nz_idx) const
{
    BOUNDARY_ASSERT(nz_idx < non_zeros(), "matrix: col_idx index out of bound");
    return nz_idx % p_cols;
}

template <typename T>
inline const T &matrix<T>::operator()(const size_type i, const size_type j) const
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix read element");
    LOG_TRACE("Read access to matrix at position " << i << ", " << j);
    return p_vals[i * p_cols + j];
}

template <typename T>
inline T &matrix<T>::operator()(const size_type i, const size_type j)
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix write element");
    LOG_TRACE("Write access to matrix at position " << i << ", " << j);
    return p_vals[i * p_cols + j];
}

template <typename T>
inline const T &matrix<T>::operator()(const size_type nz_idx) const
{
    BOUNDARY_ASSERT(nz_idx < non_zeros(), "Index out of bound: matrix read i'th value");
    LOG_TRACE("Read " << nz_idx << "'th element of dense matrix");
    return p_vals[nz_idx];
}

template <typename T>
inline const T &matrix<T>::evaluate(const size_type i, const size_type j) const
{
    LOG_TRACE("Evaluating matrix at position " << i << ", " << j);
    return (*this)(i, j);
}

template <typename T>
inline const T &matrix<T>::evaluate(const size_type nz_idx) const
{
    LOG_TRACE("Evaluating matrix at position " << i);
    return (*this)(nz_idx);
}

// ITERATORS
// ---------

template <typename T>
typename matrix<T>::iterator matrix<T>::row_begin(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "matrix: row_begin index out of bound");
    return p_vals + i * p_cols;
}

template <typename T>
typename matrix<T>::iterator matrix<T>::row_end(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "matrix: row_end index out of bound");
    return p_vals + (i + 1) * p_cols;
}

template <typename T>
typename matrix<T>::citerator matrix<T>::row_begin(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "matrix: row_begin index out of bound");
    return p_vals + i * p_cols;
}

template <typename T>
typename matrix<T>::citerator matrix<T>::row_end(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "matrix: row_end index out of bound");
    return p_vals + (i + 1) * p_cols;
}

template <typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    allocate(rhs.p_rows, rhs.p_cols);
#ifdef PARALLEL
    std::copy(execution::par_unseq, rhs.p_vals, rhs.p_vals + rhs.rows() * rhs.cols(), p_vals);
#else
    std::copy(rhs.p_vals, rhs.p_vals + rhs.rows() * rhs.cols(), p_vals);
#endif

    return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator=(matrix<T> &&rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    util::deallocate_aligned(p_vals);
    p_vals = nullptr;
    p_rows = 0;
    p_cols = 0;
    std::swap(p_vals, rhs.p_vals);
    std::swap(p_rows, rhs.p_rows);
    std::swap(p_cols, rhs.p_cols);
    return *this;
}

template <typename T>
template <typename ExpressionT>
matrix<T> &matrix<T>::operator=(const expressions::operant<ExpressionT> &exp)
{
    if (exp.rows() != p_rows || exp.cols() != p_cols) {
        allocate(exp.rows(), exp.cols());
    }
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j)
            (*this)(i, j) = exp.evaluate(i, j);
    });
#else
    std::for_each(range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) = exp.evaluate(i, j);
        }
    });
#endif
    return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>> &init_list)
{
    if (init_list.begin()->size() == 0) {
        LOG_WARNING("Empty matrix, due to empty first list of row values");
        allocate(0, 0);
        return *this;
    }
    const size_type m = init_list.size();
    const size_type n = init_list.begin()->size();
    allocate(m, n);
    size_type i = 0;
    for (std::initializer_list<T> row_vals : init_list) {
        SHAPE_ASSERT(row_vals.size() == n, "Invalid number of row elements in matrix init");
        std::copy(row_vals.begin(), row_vals.end(), row_begin(i));
        ++i;
    }
    return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix += matrix");
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
matrix<T> &matrix<T>::operator+=(const expressions::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(),
                 "Invalid shape for matrix += operant");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) += exp.evaluate(i, j);
        }
    });
#else
    std::for_each(range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) += exp.evaluate(i, j);
        }
    });
#endif
    return *this;
}
template <typename T>
matrix<T> &matrix<T>::operator*=(const T &rhs)
{
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
matrix<T> &matrix<T>::operator*=(const expressions::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(),
                 "Invalid shape for matrix *= operant");
    LOG_WARNING("Copying matrix for assignment with an expression");
    matrix<T> tmp(*this * exp);
    *this = std::move(tmp);
    return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator-=(const matrix<T> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix -= matrix");
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
matrix<T> &matrix<T>::operator-=(const expressions::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(),
                 "Invalid shape for matrix -= operant");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) -= exp.evaluate(i, j);
        }
    });
#else
    std::for_each(range.begin(), range.end(), [this, &exp](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) -= exp.evaluate(i, j);
        }
    });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
T matrix<T>::row_multiply(const expressions::operant<ExpressionT> &right, const size_t i)
{
    SHAPE_ASSERT(right.row() == cols() && ExpressionT::dimension < 2,
                 "Row multiply mismatching dimensions");
    T init = T(0);
    for (size_type j = 0; j < this->p_cols; ++j) {
        init += (*this)(i, j) * right.evaluate(j);
    }
    return init;
}

template <typename T>
template <typename function>
matrix<T> &matrix<T>::apply_func(function func)
{
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#endif
    return *this;
}

template <typename T>
void matrix<T>::to_file(const std::string &filename, const bool binary) const
{
    util::file_writer writer(filename, binary);
    writer.append(p_rows);
    writer.append(p_cols);
    writer.append(p_vals, p_rows * p_cols);
}

template <typename T>
void matrix<T>::from_file(const std::string &filename, const bool binary)
{
    util::file_reader reader(filename, binary);
    // Read size information
    size_type rows = size_type(0), cols = size_type(0);
    reader.get(rows);
    reader.get(cols);
    // Allocate memory
    allocate(rows, cols);
    reader.get(p_vals, rows * cols);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T> &mat)
{
    for (size_type i = 0; i < mat.rows(); ++i) {
        std::copy(mat.row_begin(i), mat.row_end(i), std::ostream_iterator<T>(os, "\t"));
        os << '\n';
    }
    return os;
}

} // namespace la
#endif
