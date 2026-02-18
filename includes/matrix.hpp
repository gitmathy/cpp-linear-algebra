#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "includes/assert.hpp"
#include "includes/types.hpp"
#include <algorithm>
#include <ranges>

namespace la
{

namespace internal
{
/// @brief Forward declaration to not include internals
/// @tparam ExpressionT
template <typename ExpressionT> class operant;
} // namespace internal

/// @brief Dense matrix
/// @tparam T Type of every element
template <typename T, storage_type storage = ROW_WISE> class matrix
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

    /// @brief Allocate memory and set dimensions
    /// @param n Size of the vector
    void allocate(size_type m, size_type n);

public:
    /// @brief Construct a matrix of given size, initialize elements with 0
    /// @param m number of rows
    /// @param n number of columns
    explicit matrix(size_type m, size_type n);

    /// @brief Construct a amtrix with a given value
    matrix(size_type m, size_type n, const T &val);

    /// @brief Move a matrix
    explicit matrix(matrix<T, storage> &&rhs) noexcept;

    /// @brief Copy a matrix
    matrix(const matrix<T, storage> &rhs);

    /// @brief Copy from matrix with other storage type
    /// @tparam other_storage The other storage type
    template <storage_type other_storage> matrix(const matrix<T, other_storage> &rhs);

    /// @brief Construct from expression
    template <typename ExpressionT> matrix(const internal::operant<ExpressionT> &exp);

    /// @brief Destruct a matrix
    ~matrix() { delete[] p_vals; }

    /// @brief Resize a matrix. And set all values to val
    /// @param m number of rows
    /// @param n number of columns
    void resize(size_type m, size_type n, const T &val = T(0));

    /// @brief Get number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Get number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief A matrix is two dimensional
    inline size_type dimension() const { return 2; }

    /// @brief Get element (i,j) for reading
    inline const T &operator()(size_type i, size_type j) const;

    /// @brief Get element (i,j) for writing
    inline T &operator()(size_type i, size_type j);

    /// @brief Evaluate matrix at (i,j), i.e., read element (i,j)
    inline const T &evaluate(size_type i, size_type j) const { return (*this)(i, j); }

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

    /// @brief Assign another matrix
    matrix<T, storage> &operator=(const matrix<T, storage> &rhs);

    /// @brief Assign another matrix with another storage type
    template <storage_type other_storage> matrix<T, storage> &operator=(const matrix<T, other_storage> &rhs);

    /// @brief Move assign a matix
    matrix<T, storage> &operator=(matrix<T, storage> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT> matrix<T, storage> &operator=(const internal::operant<ExpressionT> &exp);

    /// @brief Add another matix
    matrix<T, storage> &operator+=(const matrix<T, storage> &rhs);

    /// @brief Add another matix with another storage type
    template <storage_type other_storage> matrix<T, storage> &operator+=(const matrix<T, other_storage> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT> matrix<T, storage> &operator+=(const internal::operant<ExpressionT> &exp);

    /// @brief Subtract another matix
    matrix<T, storage> &operator-=(const matrix<T, storage> &rhs);

    /// @brief Substract another matix with another storage type
    template <storage_type other_storage> matrix<T, storage> &operator-=(const matrix<T, other_storage> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT> matrix<T, storage> &operator-=(const internal::operant<ExpressionT> &exp);

    /// @brief Apply a function to every entry, i.e., A(i,j)=func(A(i,j))
    /// @tparam function, supports func(T)
    template <typename function> matrix<T, storage> &apply_func(function func);
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T, storage_type storage> void matrix<T, storage>::allocate(size_type m, size_type n)
{
    if (p_vals != nullptr)
    {
        delete[] p_vals;
    }
    p_vals = new T[m * n];
    p_rows = m;
    p_cols = n;
}

template <typename T, storage_type storage>
matrix<T, storage>::matrix(size_type m, size_type n) : p_vals(nullptr), p_rows(0), p_cols(0)
{
    resize(m, n);
}

template <typename T, storage_type storage>
matrix<T, storage>::matrix(size_type m, size_type n, const T &val) : p_vals(nullptr), p_rows(0), p_cols(0)
{
    resize(m, n, val);
}

// take ownership and leave rhs in a valid empty state
template <typename T, storage_type storage>
matrix<T, storage>::matrix(matrix<T, storage> &&rhs) noexcept
    : p_vals(rhs.p_vals), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    rhs.p_vals = nullptr;
    rhs.p_rows = 0;
    rhs.p_cols = 0;
}

template <typename T, storage_type storage>
matrix<T, storage>::matrix(const matrix<T, storage> &rhs) : p_vals(nullptr), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    *this = rhs;
}

template <typename T, storage_type storage>
template <storage_type other_storage>
matrix<T, storage>::matrix(const matrix<T, other_storage> &rhs) : p_vals(nullptr), p_rows(0), p_cols(0)
{
    *this = rhs;
}

template <typename T, storage_type storage>
template <typename ExpressionT>
matrix<T, storage>::matrix(const internal::operant<ExpressionT> &exp) : p_vals(nullptr), p_rows(0)
{
    *this = exp;
}

template <typename T, storage_type storage> void matrix<T, storage>::resize(size_type m, size_type n, const T &val)
{
    allocate(m, n);
#ifdef PARALLEL
    std::fill(execution::par_unseq, p_vals, p_vals + m * n, val);
#else
    std::fill(p_vals, p_vals + m * n, val);
#endif
}

template <typename T, storage_type storage>
inline const T &matrix<T, storage>::operator()(size_type i, size_type j) const
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix read element");
    return storage == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

template <typename T, storage_type storage> inline T &matrix<T, storage>::operator()(size_type i, size_type j)
{
    BOUNDARY_ASSERT(i < p_rows && j < p_cols, "Index out of bound: matrix write element");
    return storage == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

// ITERATORS
// ---------

template <typename T, storage_type storage>
typename matrix<T, storage>::iterator matrix<T, storage>::row_begin(size_type i)
{
    LAYOUT_ASSERT(storage == ROW_WISE, "Invalid layour for matrix::row_begin");
    return p_vals + i * p_cols;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::iterator matrix<T, storage>::row_end(size_type i)
{
    LAYOUT_ASSERT(storage == ROW_WISE, "Invalid layour for matrix::row_end");
    return p_vals + (i + 1) * p_cols;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::citerator matrix<T, storage>::row_begin(size_type i) const
{
    LAYOUT_ASSERT(storage == ROW_WISE, "Invalid layour for matrix::row_begin const");
    return p_vals + i * p_cols;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::citerator matrix<T, storage>::row_end(size_type i) const
{
    LAYOUT_ASSERT(storage == ROW_WISE, "Invalid layour for matrix::row_end const");
    return p_vals + (i + 1) * p_cols;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::iterator matrix<T, storage>::col_begin(size_type i)
{
    LAYOUT_ASSERT(storage == COLUMN_WISE, "Invalid layour for matrix::col_begin");
    return p_vals + i * p_rows;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::iterator matrix<T, storage>::col_end(size_type i)
{
    LAYOUT_ASSERT(storage == COLUMN_WISE, "Invalid layour for matrix::col_end");
    return p_vals + (i + 1) * p_rows;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::citerator matrix<T, storage>::col_begin(size_type i) const
{
    LAYOUT_ASSERT(storage == COLUMN_WISE, "Invalid layour for matrix::col_begin const");
    return p_vals + i * p_rows;
}

template <typename T, storage_type storage>
typename matrix<T, storage>::citerator matrix<T, storage>::col_end(size_type i) const
{
    LAYOUT_ASSERT(storage == COLUMN_WISE, "Invalid layour for matrix::col_end const");
    return p_vals + (i + 1) * p_rows;
}

template <typename T, storage_type storage>
matrix<T, storage> &matrix<T, storage>::operator=(const matrix<T, storage> &rhs)
{
    if (this == &rhs)
        return *this;
    allocate(rhs.p_rows, rhs.p_cols);
#ifdef PARALLEL
    std::copy(execution::par_unseq, rhs.p_vals, rhs.p_vals + rhs.rows() * rhs.cols(), p_vals);
#else
    std::copy(rhs.p_vals, rhs.p_vals + rhs.rows() * rhs.cols(), p_vals);
#endif

    return *this;
}

template <typename T, storage_type storage>
template <storage_type other_storage>
matrix<T, storage> &matrix<T, storage>::operator=(const matrix<T, other_storage> &rhs)
{
    allocate(rhs.rows(), rhs.cols());
    LOG_WARNING("Unoptimized storage access due to storage layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par, range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) = rhs(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) = rhs(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
matrix<T, storage> &matrix<T, storage>::operator=(matrix<T, storage> &&rhs) noexcept
{
    if (this == &rhs)
        return *this;
    delete[] p_vals;
    p_vals = nullptr;
    p_rows = 0;
    p_cols = 0;
    std::swap(p_vals, rhs.p_vals);
    std::swap(p_rows, rhs.p_rows);
    std::swap(p_cols, rhs.p_cols);
    return *this;
}

template <typename T, storage_type storage>
template <typename ExpressionT>
matrix<T, storage> &matrix<T, storage>::operator=(const internal::operant<ExpressionT> &exp)
{
    if (exp.rows() != p_rows || exp.cols() != p_cols)
        allocate(exp.rows(), exp.cols());
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) = exp.evaluate(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) = exp.evaluate(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
matrix<T, storage> &matrix<T, storage>::operator+=(const matrix<T, storage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(), "Invalid shape for matrix += matrix");
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T, storage_type storage>
template <storage_type other_storage>
matrix<T, storage> &matrix<T, storage>::operator+=(const matrix<T, other_storage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix += matrix with different storage_type");
    LOG_WARNING("Unoptimized storage access due to storage layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) += rhs(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) += rhs(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
template <typename ExpressionT>
matrix<T, storage> &matrix<T, storage>::operator+=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(), "Invalid shape for matrix += operant");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) += exp.evaluate(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) += exp.evaluate(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
matrix<T, storage> &matrix<T, storage>::operator-=(const matrix<T, storage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(), "Invalid shape for matrix -= matrix");
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T, storage_type storage>
template <storage_type other_storage>
matrix<T, storage> &matrix<T, storage>::operator-=(const matrix<T, other_storage> &rhs)
{
    SHAPE_ASSERT(rows() == rhs.rows() && cols() == rhs.cols(),
                 "Invalid shape for matrix -= matrix with different storage_type");
    LOG_WARNING("Unoptimized storage access due to storage layout");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) -= rhs(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) -= rhs(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
template <typename ExpressionT>
matrix<T, storage> &matrix<T, storage>::operator-=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(p_rows == exp.rows() && p_cols == exp.cols(), "Invalid shape for matrix -= operant");
    auto range = std::views::iota(size_type(0), p_rows);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) -= exp.evaluate(i, j);
                  });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i)
                  {
                      for (size_type j = 0; j < this->p_cols; ++j)
                          (*this)(i, j) -= exp.evaluate(i, j);
                  });
#endif
    return *this;
}

template <typename T, storage_type storage>
template <typename function>
matrix<T, storage> &matrix<T, storage>::apply_func(function func)
{
    auto range = std::views::iota(size_type(0), rows() * cols());
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#else
    std::for_each(range.begin(), range.end(), [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#endif
    return *this;
}
} // namespace la
#endif
