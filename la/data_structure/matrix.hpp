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
#include "la/util/macros.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <fstream>
#include <initializer_list>
#include <ranges>
#include <string>

namespace la {

/// @brief Class representing a dense matrix, i.e., all values are stored
///
/// All values are stored in a single array of elements. Depending on the template parameter
/// StorageT, the values are either stored by rows (ROW_WISE) or by columns (COLUMN_WISE).
/// @tparam T Type of every element
template <typename T, storage_type StorageT = ROW_WISE>
class matrix
{
public:
    /// @brief Type of every element
    typedef T value_type;

    /// @brief Storage type
    static constexpr storage_type storage = StorageT;

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

public:
    /// @brief Default constructor creates an empty matrix
    explicit matrix() : p_vals(nullptr), p_rows(0), p_cols(0) {}

    /// @brief Construct a matrix of given size, initialize elements with 0
    /// @param m number of rows
    /// @param n number of columns
    /// @param val default value for all elements
    explicit matrix(size_type m, size_type n, const T &val = T());

    /// @brief Construct a matrix with a list of values
    matrix(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Move a matrix
    explicit matrix(matrix<T, StorageT> &&rhs) noexcept;

    /// @brief Copy a matrix
    matrix(const matrix<T, StorageT> &rhs);

    /// @brief Copy from matrix with other StorageT type
    /// @tparam OtherStorage The other StorageT type
    template <storage_type OtherStorage>
    matrix(const matrix<T, OtherStorage> &rhs);

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
    void allocate(size_type m, size_type n);

    /// @brief Resize a matrix. And set all values to val
    /// @param m number of rows
    /// @param n number of columns
    /// @param val value applied to every element of the matrix
    void resize(size_type m, size_type n, const T &val = T(0));

    /// @brief Get number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Get number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Get element (i,j) for reading
    inline const T &operator()(size_type i, size_type j) const;

    /// @brief Get element (i,j) for writing
    inline T &operator()(size_type i, size_type j);

    /// @brief Evaluate matrix at (i,j), i.e., read element (i,j)
    inline const T &evaluate(size_type i, size_type j) const;

    /// @brief Evaluate matrix at (i) raises an error
    inline const T &evaluate(size_type i) const;

    /// @brief Iterator to begin
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end
    inline iterator end() { return p_vals + p_rows * p_cols; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + p_rows * p_cols; }

    /// @brief Iterator to row begin (only valid for ROW_WISE)
    inline iterator row_begin(size_type i);
    /// @brief Iterator to row end (only valid for ROW_WISE)
    inline iterator row_end(size_type i);

    /// @brief Constant iterator to row begin (only valid for ROW_WISE)
    inline citerator row_begin(size_type i) const;
    /// @brief Constant iterator to row end (only valid for ROW_WISE)
    inline citerator row_end(size_type i) const;

    /// @brief Iterator to column begin (only valid for COL_WISE)
    inline iterator col_begin(size_type i);
    /// @brief Iterator to column end (only valid for COL_WISE)
    inline iterator col_end(size_type i);

    /// @brief Constant iterator to column begin (only valid for COL_WISE)
    inline citerator col_begin(size_type i) const;
    /// @brief Constant iterator to column end (only valid for COL_WISE)
    inline citerator col_end(size_type i) const;

    /// @brief Direct access to the memory. Use with caution
    inline T *vals() { return p_vals; }

    /// @brief Direct access to the memory. Use with caution
    inline T const *vals() const { return p_vals; }

    /// @brief Assign another matrix
    matrix<T, StorageT> &operator=(const matrix<T, StorageT> &rhs);

    /// @brief Assign another matrix with another StorageT type
    ///
    /// Note this should be avoided as memory access is not optimized!
    template <storage_type OtherStorage>
    matrix<T, StorageT> &operator=(const matrix<T, OtherStorage> &rhs);

    /// @brief Move assign a matrix
    matrix<T, StorageT> &operator=(matrix<T, StorageT> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT>
    matrix<T, StorageT> &operator=(const expressions::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    matrix<T, StorageT> &
    operator=(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Assign the result of a matrix-matrix multiplication
    template <typename MatTypeLeft, typename MatTypeRight>
    matrix<T, StorageT> &
    operator=(const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult);

    /// @brief Add another matrix
    matrix<T, StorageT> &operator+=(const matrix<T, StorageT> &rhs);

    /// @brief Add another matrix with another StorageT type
    ///
    /// Note this should be avoided as memory access is not optimized!
    template <storage_type OtherStorage>
    matrix<T, StorageT> &operator+=(const matrix<T, OtherStorage> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT>
    matrix<T, StorageT> &operator+=(const expressions::operant<ExpressionT> &exp);

    /// @brief Multiply with a scalar
    matrix<T, StorageT> &operator*=(const T &rhs);

    /// @brief Multiply from another expression
    template <typename ExpressionT>
    matrix<T, StorageT> &operator*=(const expressions::operant<ExpressionT> &exp);

    /// @brief Subtract another matrix
    matrix<T, StorageT> &operator-=(const matrix<T, StorageT> &rhs);

    /// @brief Substract another matrix with another StorageT type
    ///
    /// Note this should be avoided as memory access is not optimized!
    template <storage_type OtherStorage>
    matrix<T, StorageT> &operator-=(const matrix<T, OtherStorage> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT>
    matrix<T, StorageT> &operator-=(const expressions::operant<ExpressionT> &exp);

    /// @brief Apply a function to every entry, i.e., A(i,j)=func(A(i,j))
    /// @tparam function, supports func(T)
    template <typename function>
    matrix<T, StorageT> &apply_func(function func);

    /// @brief Write matrix to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true);

    /// @brief Read matrix from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

// ===============================================
// P U B L I C   F U N C T I O N S
// ===============================================

/// @brief Write a vector to an output stream
template <typename T, storage_type StorageT>
std::ostream &operator<<(std::ostream &os, const matrix<T, StorageT> &mat);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T, storage_type StorageT>
void matrix<T, StorageT>::allocate(size_type m, size_type n)
{
    LOG_DEBUG("Allocating memory for matrix: " << (m * n * sizeof(T)) << " B");
    util::deallocate_aligned(p_vals);
    p_vals = util::allocate_aligned<T>(m * n);
    p_rows = m;
    p_cols = n;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT>::matrix(size_type m, size_type n, const T &val)
    : p_vals(nullptr), p_rows(0), p_cols(0)
{
    resize(m, n, val);
}

template <typename T, storage_type StorageT>
matrix<T, StorageT>::matrix(const std::initializer_list<std::initializer_list<T>> &init_list)
    : p_vals(nullptr), p_rows(0), p_cols(0)
{
    *this = init_list;
}

// take ownership and leave rhs in a valid empty state
template <typename T, storage_type StorageT>
matrix<T, StorageT>::matrix(matrix<T, StorageT> &&rhs) noexcept
    : p_vals(rhs.p_vals), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    rhs.p_vals = nullptr;
    rhs.p_rows = 0;
    rhs.p_cols = 0;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT>::matrix(const matrix<T, StorageT> &rhs)
    : p_vals(nullptr), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    *this = rhs;
}

template <typename T, storage_type StorageT>
template <storage_type OtherStorage>
matrix<T, StorageT>::matrix(const matrix<T, OtherStorage> &rhs)
    : p_vals(nullptr), p_rows(0), p_cols(0)
{
    *this = rhs;
}

template <typename T, storage_type StorageT>
template <typename ExpressionT>
matrix<T, StorageT>::matrix(const expressions::operant<ExpressionT> &exp)
    : p_vals(nullptr), p_rows(0)
{
    *this = exp;
}

template <typename T, storage_type StorageT>
template <typename MatTypeLeft, typename MatTypeRight>
matrix<T, StorageT>::matrix(
    const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult)
{
    *this = mat_mult;
}

template <typename T, storage_type StorageT>
void matrix<T, StorageT>::resize(size_type m, size_type n, const T &val)
{
    LOG_DEBUG("Resizing matrix to (" << m << " x " << n << ')');
    allocate(m, n);
#ifdef PARALLEL
    std::fill(execution::par_unseq, p_vals, p_vals + m * n, val);
#else
    std::fill(p_vals, p_vals + m * n, val);
#endif
}

template <typename T, storage_type StorageT>
inline const T &matrix<T, StorageT>::operator()(size_type i, size_type j) const
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix read element");
    LOG_TRACE("Read access to matrix at position " << i << ", " << j);
    return StorageT == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

template <typename T, storage_type StorageT>
inline T &matrix<T, StorageT>::operator()(size_type i, size_type j)
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix write element");
    LOG_TRACE("Write access to matrix at position " << i << ", " << j);
    return StorageT == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

template <typename T, storage_type StorageT>
inline const T &matrix<T, StorageT>::evaluate(size_type i, size_type j) const
{
    LOG_TRACE("Evaluating matrix at position " << i << ", " << j);
    return (*this)(i, j);
}

template <typename T, storage_type StorageT>
inline const T &matrix<T, StorageT>::evaluate(size_type) const
{
    throw util::error("Evaluate matrix at i is not implemented");
}

// ITERATORS
// ---------

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::iterator matrix<T, StorageT>::row_begin(size_type i)
{
    LAYOUT_ASSERT(StorageT == ROW_WISE, "Invalid layout for matrix::row_begin");
    return p_vals + i * p_cols;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::iterator matrix<T, StorageT>::row_end(size_type i)
{
    LAYOUT_ASSERT(StorageT == ROW_WISE, "Invalid layout for matrix::row_end");
    return p_vals + (i + 1) * p_cols;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::citerator matrix<T, StorageT>::row_begin(size_type i) const
{
    LAYOUT_ASSERT(StorageT == ROW_WISE, "Invalid layout for matrix::row_begin const");
    return p_vals + i * p_cols;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::citerator matrix<T, StorageT>::row_end(size_type i) const
{
    LAYOUT_ASSERT(StorageT == ROW_WISE, "Invalid layout for matrix::row_end const");
    return p_vals + (i + 1) * p_cols;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::iterator matrix<T, StorageT>::col_begin(size_type i)
{
    LAYOUT_ASSERT(StorageT == COLUMN_WISE, "Invalid layout for matrix::col_begin");
    return p_vals + i * p_rows;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::iterator matrix<T, StorageT>::col_end(size_type i)
{
    LAYOUT_ASSERT(StorageT == COLUMN_WISE, "Invalid layout for matrix::col_end");
    return p_vals + (i + 1) * p_rows;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::citerator matrix<T, StorageT>::col_begin(size_type i) const
{
    LAYOUT_ASSERT(StorageT == COLUMN_WISE, "Invalid layout for matrix::col_begin const");
    return p_vals + i * p_rows;
}

template <typename T, storage_type StorageT>
typename matrix<T, StorageT>::citerator matrix<T, StorageT>::col_end(size_type i) const
{
    LAYOUT_ASSERT(StorageT == COLUMN_WISE, "Invalid layout for matrix::col_end const");
    return p_vals + (i + 1) * p_rows;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT> &matrix<T, StorageT>::operator=(const matrix<T, StorageT> &rhs)
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

template <typename T, storage_type StorageT>
template <storage_type OtherStorage>
matrix<T, StorageT> &matrix<T, StorageT>::operator=(const matrix<T, OtherStorage> &rhs)
{
    allocate(rhs.rows(), rhs.cols());
    LOG_WARNING("Unoptimized StorageT access due to StorageT layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par, range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j)
            (*this)(i, j) = rhs(i, j);
    });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j)
            (*this)(i, j) = rhs(i, j);
    });
#endif
    return *this;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT> &matrix<T, StorageT>::operator=(matrix<T, StorageT> &&rhs) noexcept
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

template <typename T, storage_type StorageT>
template <typename ExpressionT>
matrix<T, StorageT> &matrix<T, StorageT>::operator=(const expressions::operant<ExpressionT> &exp)
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

template <typename T, storage_type StorageT>
matrix<T, StorageT> &
matrix<T, StorageT>::operator=(const std::initializer_list<std::initializer_list<T>> &init_list)
{
    if (init_list.begin()->size() == 0) {
        LOG_WARNING("Empty matrix, due to empty first list of row values");
        allocate(0, 0);
        return *this;
    }
    const size_type m = (StorageT == ROW_WISE) ? init_list.size() : init_list.begin()->size();
    const size_type n = (StorageT == ROW_WISE) ? init_list.begin()->size() : init_list.size();
    allocate(m, n);
    if constexpr (StorageT == ROW_WISE) {
        size_type i = 0;
        for (std::initializer_list<T> row_vals : init_list) {
            SHAPE_ASSERT(row_vals.size() == n, "Invalid number of row elements in matrix init");
            std::copy(row_vals.begin(), row_vals.end(), row_begin(i));
            ++i;
        }
    } else {
        // Column-wise matrix
        size_type j = 0;
        for (std::initializer_list<T> col_vals : init_list) {
            SHAPE_ASSERT(col_vals.size() == m, "Invalid number of column elements in matrix init");
            std::copy(col_vals.begin(), col_vals.end(), col_begin(j));
            ++j;
        }
    }
    return *this;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT> &matrix<T, StorageT>::operator+=(const matrix<T, StorageT> &rhs)
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

template <typename T, storage_type StorageT>
template <storage_type OtherStorage>
matrix<T, StorageT> &matrix<T, StorageT>::operator+=(const matrix<T, OtherStorage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix += matrix with different storage_type");
    LOG_WARNING("Unoptimized StorageT access due to StorageT layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) += rhs(i, j);
        }
    });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) += rhs(i, j);
        }
    });
#endif
    return *this;
}

template <typename T, storage_type StorageT>
template <typename ExpressionT>
matrix<T, StorageT> &matrix<T, StorageT>::operator+=(const expressions::operant<ExpressionT> &exp)
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
template <typename T, storage_type StorageT>
matrix<T, StorageT> &matrix<T, StorageT>::operator*=(const T &rhs)
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

template <typename T, storage_type StorageT>
template <typename ExpressionT>
matrix<T, StorageT> &matrix<T, StorageT>::operator*=(const expressions::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(),
                 "Invalid shape for matrix *= operant");
    LOG_WARNING("Copying matrix for assignment with an expression");
    matrix<T, StorageT> tmp(*this * exp);
    *this = std::move(tmp);
    return *this;
}

template <typename T, storage_type StorageT>
matrix<T, StorageT> &matrix<T, StorageT>::operator-=(const matrix<T, StorageT> &rhs)
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

template <typename T, storage_type StorageT>
template <storage_type OtherStorage>
matrix<T, StorageT> &matrix<T, StorageT>::operator-=(const matrix<T, OtherStorage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix -= matrix with different storage_type");
    LOG_WARNING("Unoptimized StorageT access due to StorageT layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) -= rhs(i, j);
        }
    });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) {
        for (size_type j = 0; j < this->p_cols; ++j) {
            (*this)(i, j) -= rhs(i, j);
        }
    });
#endif
    return *this;
}

template <typename T, storage_type StorageT>
template <typename ExpressionT>
matrix<T, StorageT> &matrix<T, StorageT>::operator-=(const expressions::operant<ExpressionT> &exp)
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

template <typename T, storage_type StorageT>
template <typename function>
matrix<T, StorageT> &matrix<T, StorageT>::apply_func(function func)
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

template <typename T, storage_type StorageT>
void matrix<T, StorageT>::to_file(const std::string &filename, const bool binary)
{
    std::ios_base::openmode mode = binary ? std::ios::out : std::ios::binary | std::ios::out;
    std::ofstream ofs(filename, mode);
    if (!ofs) {
        LOG_ERROR("Failed to open file '" << filename << "' for write");
        throw util::error("Cannot open file for write.", "file_io");
    }
    if (binary) {
        ofs.write(reinterpret_cast<const char *>(&p_rows), sizeof(size_type));
        ofs.write(reinterpret_cast<const char *>(&p_cols), sizeof(size_type));
        ofs.write(reinterpret_cast<const char *>(p_vals), p_rows * p_cols * sizeof(T));
    } else {
        ofs << p_rows << ' ' << p_cols << ' ';
        std::copy(p_vals, p_vals + p_rows * p_cols, std::ostream_iterator<T>(ofs, " "));
    }
    ofs.close();
}

template <typename T, storage_type StorageT>
void matrix<T, StorageT>::from_file(const std::string &filename, const bool binary)
{
    std::ios_base::openmode mode = binary ? std::ios::in : std::ios::binary | std::ios::in;
    std::ifstream ifs(filename, mode);
    if (!ifs) {
        LOG_ERROR("Failed to open file " << filename);
        throw util::error("Cannot open file for read.", "file_io");
    }
    // Read size information
    size_type rows = size_type(0), cols = size_type(0);
    if (binary) {
        ifs.read(reinterpret_cast<char *>(&rows), sizeof(size_type));
        ifs.read(reinterpret_cast<char *>(&cols), sizeof(size_type));
        if (!ifs) {
            LOG_ERROR("Reading binary matrix information failed due to I/O error");
            throw util::error("Cannot read header for read.", "file_io");
        }
    } else {
        if (!(ifs >> rows >> cols)) {
            LOG_ERROR("Reading text matrix information failed due to I/O error");
            throw util::error("Cannot read header for read.", "file_io");
        }
    }
    allocate(rows, cols);
    if (binary) {
        ifs.read(reinterpret_cast<char *>(p_vals), rows * cols * sizeof(T));
        if (!ifs) {
            LOG_ERROR("Reading binary data failed due to I/O error");
            throw util::error("Cannot read binary data.", "file_io");
        }
    } else {
        T value = T(0);
        for (T *first = begin(); first != end(); ++first) {
            if (ifs >> value) {
                *first = value;
            } else {
                LOG_ERROR("Reading text data failed due to I/O error");
                throw util::error("Cannot read text data.", "file_io");
            }
        }
    }
    ifs.close();
}

template <typename T, storage_type StorageT>
std::ostream &operator<<(std::ostream &os, const matrix<T, StorageT> &mat)
{
    for (size_type i = 0; i < mat.rows(); ++i) {
        for (size_type j = 0; j < mat.cols(); ++j) {
            os << mat(i, j) << (j != mat.cols() - 1 ? '\t' : ' ');
        }
        os << '\n';
    }
    return os;
}

// specialized for ROW_WISE matrices
template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T, ROW_WISE> &mat)
{
    for (size_type i = 0; i < mat.rows(); ++i) {
        std::copy(mat.row_begin(i), mat.row_end(i), std::ostream_iterator<T>(os, "\t"));
        os << '\n';
    }
    return os;
}

} // namespace la
#endif
