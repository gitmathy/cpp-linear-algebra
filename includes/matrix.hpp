#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "includes/types.hpp"
#include <algorithm>

namespace la
{

/// @brief Storing matrix row- or column-wise
enum storage_type
{
    ROW_WISE,
    COLUMN_WISE
};

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

    /// @brief Destruct a matrix
    ~matrix();

    /// @brief Resize a matrix. And set all values to val
    /// @param m number of rows
    /// @param n number of columns
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
    inline iterator row_begin(size_type i) { return p_vals + i * p_cols; }
    /// @brief Iterator to row end (only valid for ROW_WISE)
    inline iterator row_end(size_type i) { return p_vals + (i + 1) * p_cols; }

    /// @brief Constant iterator to row begin (only valid for ROW_WISE)
    inline citerator row_begin(size_type i) const { return p_vals + i * p_cols; }
    /// @brief Constant iterator to row end (only valid for ROW_WISE)
    inline citerator row_end(size_type i) const { return p_vals + (i + 1) * p_cols; }

    /// @brief Iterator to column begin (only valid for COL_WISE)
    inline iterator col_begin(size_type i) { return p_vals + i * p_rows; }
    /// @brief Iterator to column end (only valid for COL_WISE)
    inline iterator col_end(size_type i) { return p_vals + (i + 1) * p_rows; }

    /// @brief Constant iterator to column begin (only valid for COL_WISE)
    inline citerator col_begin(size_type i) const { return p_vals + i * p_rows; }
    /// @brief Constant iterator to column end (only valid for COL_WISE)
    inline citerator col_end(size_type i) const { return p_vals + (i + 1) * p_rows; }
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T, storage_type storage>
matrix<T, storage>::matrix(size_type m, size_type n) : p_vals(new T[m * n]), p_rows(m), p_cols(n)
{
    for (size_type i = 0; i < m * n; ++i)
        p_vals[i] = T(0);
}

template <typename T, storage_type storage>
matrix<T, storage>::matrix(size_type m, size_type n, const T &val) : p_vals(new T[m * n]), p_rows(m), p_cols(n)
{
    for (size_type i = 0; i < m * n; ++i)
        p_vals[i] = val;
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

template <typename T, storage_type storage> matrix<T, storage>::~matrix() { delete[] p_vals; }

template <typename T, storage_type storage>
matrix<T, storage>::matrix(const matrix<T, storage> &rhs) : p_vals(nullptr), p_rows(rhs.p_rows), p_cols(rhs.p_cols)
{
    const size_type n = p_rows * p_cols;
    p_vals = new T[n];
    std::copy(rhs.p_vals, rhs.p_vals + n, p_vals);
}

template <typename T, storage_type storage> void matrix<T, storage>::resize(size_type m, size_type n, const T &val)
{
    delete[] p_vals;
    p_vals = new T[m * n];
    p_rows = m;
    p_cols = n;
    std::fill(p_vals, p_vals + m * n, val);
}

template <typename T, storage_type storage>
inline const T &matrix<T, storage>::operator()(size_type i, size_type j) const
{
    return storage == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

template <typename T, storage_type storage> inline T &matrix<T, storage>::operator()(size_type i, size_type j)
{
    return storage == ROW_WISE ? p_vals[i * p_cols + j] : p_vals[j * p_rows + i];
}

} // namespace la
#endif
