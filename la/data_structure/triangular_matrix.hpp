/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/triangular_matrix.hpp
/// @brief Declaration and definition of a dense matrix class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_TRIANGULAR_MATRIX_HPP
#define LA_DATA_STRUCTURE_TRIANGULAR_MATRIX_HPP

#include "la/util/constants.hpp"
#include "la/util/error.hpp"
#include "la/util/file_io.hpp"
#include "la/util/macros.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <initializer_list>
#include <ranges>
#include <utility>

namespace la {

/// @brief Triangular matrix
/// @tparam T value type
/// @tparam LOWER (true) lower triangular matrix or (false) upper triangular matrix
template <typename T, bool LOWER = true>
class triang_matrix
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

    /// @brief Number of non-zero elements (computed by rows and columns)
    size_type p_non_zeros;

public:
    /// public variable members

    /// @brief Dimension of a matrix
    constexpr static size_type dimension = size_type(2);

    /// @brief This matrix is dense
    constexpr static bool dense = true;

public:
    /// @brief Constructing a empty triangular matrix
    explicit triang_matrix() : p_vals(nullptr), p_rows(0), p_cols(0), p_non_zeros(0) {}

    /// @brief Constructing of given size with default value
    explicit triang_matrix(const size_type m, const size_type n, const T &val = T());

    /// @brief Copy a triangular matrix
    triang_matrix(const triang_matrix<T, LOWER> &rhs);

    /// @brief Move a triangular matrix
    explicit triang_matrix(triang_matrix<T, LOWER> &&rhs) noexcept;

    /// @brief Construct a triangular matrix with a list of values
    ///
    /// Wide lower or tall upper cannot be constructed on this way
    triang_matrix(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Destruct a triangular matrix
    ~triang_matrix() { util::deallocate_aligned(p_vals); }

    /// @brief Allocate memory and set shape
    void allocate(const size_type m, const size_type n);

    /// @brief Resize a matrix. And set all values to val
    void resize(const size_type m, const size_type n, const T &val = T(0));

    /// @brief Get number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Get number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_non_zeros; }

    /// @brief Number of non-zeros in a given row
    inline size_type non_zeros(const size_type i) const;

    /// @brief Get first index in row i (also available for i==rows())
    inline size_type row_idx_begin(const size_type i) const;

    /// @brief Get the non-zero index of a given row-column index
    /// @return Index of index of the element(i,j). If this is a zero element, return
    ///     SIZE_TYPE_MAX.
    inline size_type get_idx(const size_type i, const size_type j) const;

    /// @brief Get element (i,j) for reading (copy of type, as this could be zero)
    inline const T operator()(const size_type i, const size_type j) const;

    /// @brief Get element (i,j) for writing
    inline T &operator()(const size_type i, const size_type j);

    /// @brief Get nz_idx't element for reading
    inline const T &operator()(const size_type nz_idx) const;

    /// @brief Iterator to begin
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end
    inline iterator end() { return p_vals + p_non_zeros; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + p_non_zeros; }

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

    /// @brief Assign another triangular matrix
    triang_matrix<T, LOWER> &operator=(const triang_matrix<T, LOWER> &rhs);

    /// @brief Move assign a triangular matrix
    triang_matrix<T, LOWER> &operator=(triang_matrix<T, LOWER> &&rhs) noexcept;

    // /// @brief Assign from expression
    // template <typename ExpressionT>
    // triang_matrix<T, LOWER> &operator=(const expressions::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    triang_matrix<T, LOWER> &
    operator=(const std::initializer_list<std::initializer_list<T>> &init_list);

    /// @brief Apply a function to every entry, i.e., A(i,j)=func(A(i,j))
    /// @tparam function, supports func(T)
    template <typename function>
    triang_matrix<T, LOWER> &apply_func(function func);

    /// @brief Write matrix to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true) const;

    /// @brief Read matrix from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T, bool LOWER>
triang_matrix<T, LOWER>::triang_matrix(const size_type m, const size_type n, const T &val)
    : p_vals(nullptr), p_rows(0), p_cols(0), p_non_zeros(0)
{
    LOG_DEBUG("Constructing triangular matrix (" << m << " x " << n << ')');
    resize(m, n, val);
}

template <typename T, bool LOWER>
triang_matrix<T, LOWER>::triang_matrix(
    const std::initializer_list<std::initializer_list<T>> &init_list)
    : p_vals(nullptr), p_rows(0), p_cols(0), p_non_zeros(0)
{
    *this = init_list;
}

template <typename T, bool LOWER>
triang_matrix<T, LOWER>::triang_matrix(const triang_matrix<T, LOWER> &rhs)
    : p_vals(nullptr), p_rows(0), p_cols(0), p_non_zeros(0)
{
    *this = rhs;
}

template <typename T, bool LOWER>
triang_matrix<T, LOWER>::triang_matrix(triang_matrix<T, LOWER> &&rhs) noexcept
    : p_vals(nullptr), p_rows(0), p_cols(0), p_non_zeros(0)
{
    *this = std::move(rhs);
}

template <typename T, bool LOWER>
void triang_matrix<T, LOWER>::allocate(const size_type m, const size_type n)
{
    auto compute_num_values = [](const size_type a, const size_type b) {
        // number of values for lower triangular matrix:
        //   m>=n: n*(n+1)/2 + (m-n)*n
        //   m<n: m*(m+1)/2
        return a < b ? a * (a + 1) / 2 : b * (b + 1) / 2 + (a - b) * b;
    };
    const size_type num_values = (LOWER) ? compute_num_values(m, n) : compute_num_values(n, m);
    const size_type num_old = non_zeros();
    LOG_DEBUG("Allocating memory for triangular matrix for " << num_values << " elements");
    if (num_values != num_old) {
        util::deallocate_aligned(p_vals);
        p_vals = util::allocate_aligned<T>(num_values);
    }
    p_rows = m;
    p_cols = n;
    p_non_zeros = num_values;
}

template <typename T, bool LOWER>
void triang_matrix<T, LOWER>::resize(const size_type m, const size_type n, const T &val)
{
    LOG_DEBUG("Resizing triangular matrix to (" << m << " x " << n << ')');
    allocate(m, n);
#ifdef PARALLEL
    std::fill(execution::par_unseq, p_vals, p_vals + non_zeros(), val);
#else
    std::fill(p_vals, p_vals + non_zeros(), val);
#endif
}

template <typename T, bool LOWER>
inline size_type triang_matrix<T, LOWER>::non_zeros(const size_type i) const
{
    BOUNDARY_ASSERT(i < p_rows, "Row index out of bound");
    if constexpr (LOWER) {
        // Row i has (i + 1) elements, but cannot exceed the total columns.
        return std::min(i + 1, p_cols);
    } else {
        // Row starts at i. If i >= p_cols, the row is empty (0).
        // Otherwise, size is (p_cols - i).
        if (i >= p_cols) {
            return 0;
        }
        return p_cols - i;
    }
}

template <typename T, bool LOWER>
inline size_type triang_matrix<T, LOWER>::row_idx_begin(const size_type i) const
{
    LOG_TRACE("Get first index in row " << i);
    BOUNDARY_ASSERT(i <= rows(), "Row index out of bound");
    if constexpr (LOWER) {
        const size_type min_dim = std::min(p_rows, p_cols);
        if (i <= min_dim) {
            return i * (i + 1) / 2;
        } else {
            return min_dim * (min_dim + 1) / 2 + (i - min_dim) * p_cols;
        }
    } else { // UPPER
        if (i >= p_cols) {
            return non_zeros(); // Past the stored data
        }
        // Sum of arithmetic progression for row lengths from p_cols down to (p_cols - i + 1)
        return (i * p_cols) - (i * (i - 1) / 2);
    }
}

template <typename T, bool LOWER>
inline size_type triang_matrix<T, LOWER>::get_idx(const size_type i, const size_type j) const
{
    BOUNDARY_ASSERT(i < p_rows, "Row index out of bound");
    BOUNDARY_ASSERT(j < p_cols, "Column index out of bound");
    LOG_TRACE("Getting index (" << i << "x" << j << ") in triangular matrix");
    if constexpr (LOWER) {
        const size_type min_dim = std::min(p_rows, p_cols);
        if (i < min_dim) {
            // here we are in the triangular part.
            return (j > i) ? SIZE_TYPE_MAX : i * (i + 1) / 2 + j;
        } else {
            // here we are in the "full part" at the lower
            return min_dim * (min_dim + 1) / 2 + (i - min_dim) * p_cols + j;
        }
    } else {         // upper triangular matrix
        if (j < i) { // left of diagonal
            return SIZE_TYPE_MAX;
        }
        if (i >= p_cols) {
            // tall matrix (rows > cols), so we are below the non-zeros
            return SIZE_TYPE_MAX;
        }
        return (j < i) ? SIZE_TYPE_MAX : (i * p_cols) - (i * (i - 1) / 2) + (j - i);
    };
}

template <typename T, bool LOWER>
inline const T triang_matrix<T, LOWER>::operator()(const size_type i, const size_type j) const
{
    const size_type idx = get_idx(i, j);
    return idx == SIZE_TYPE_MAX ? 0 : p_vals[idx];
}

template <typename T, bool LOWER>
inline T &triang_matrix<T, LOWER>::operator()(const size_type i, const size_type j)
{
    const size_type idx = get_idx(i, j);
    BOUNDARY_ASSERT(idx != SIZE_TYPE_MAX, "Cannot write to zero-element");
    return p_vals[idx];
}

template <typename T, bool LOWER>
inline const T &triang_matrix<T, LOWER>::operator()(const size_type nz_idx) const
{
    BOUNDARY_ASSERT(nz_idx != p_non_zeros, "Non-zero element is out of bound");
    return p_vals[nz_idx];
}

template <typename T, bool LOWER>
inline typename triang_matrix<T, LOWER>::iterator
triang_matrix<T, LOWER>::row_begin(const size_type i)
{
    LOG_TRACE("Get iterator to beginning of row");
    BOUNDARY_ASSERT(i < rows(), "Row index out of bound");
    return p_vals + row_idx_begin(i);
}

template <typename T, bool LOWER>
inline typename triang_matrix<T, LOWER>::iterator
triang_matrix<T, LOWER>::row_end(const size_type i)
{
    LOG_TRACE("Get iterator to end of row");
    BOUNDARY_ASSERT(i < rows(), "Row index out of bound");
    return p_vals + row_idx_begin(i + 1);
}

template <typename T, bool LOWER>
inline typename triang_matrix<T, LOWER>::citerator
triang_matrix<T, LOWER>::row_begin(const size_type i) const
{
    LOG_TRACE("Get iterator to beginning of row");
    BOUNDARY_ASSERT(i < rows(), "Row index out of bound");
    return p_vals + row_idx_begin(i);
}

template <typename T, bool LOWER>
inline typename triang_matrix<T, LOWER>::citerator
triang_matrix<T, LOWER>::row_end(const size_type i) const
{
    LOG_TRACE("Get iterator to end of row");
    BOUNDARY_ASSERT(i < rows(), "Row index out of bound");
    return p_vals + row_idx_begin(i + 1);
}

template <typename T, bool LOWER>
triang_matrix<T, LOWER> &triang_matrix<T, LOWER>::operator=(const triang_matrix<T, LOWER> &rhs)
{
    LOG_DEBUG("Copying a triangular matrix");
    if (this == &rhs) {
        return *this;
    }
    allocate(rhs.rows(), rhs.cols());
#ifdef PARALLEL
    std::copy(execution::par_unseq, rhs.p_vals, rhs.p_vals + non_zeros(), p_vals);
#else
    std::copy(rhs.p_vals, rhs.p_vals + non_zeros(), p_vals);
#endif
    return *this;
}

template <typename T, bool LOWER>
triang_matrix<T, LOWER> &triang_matrix<T, LOWER>::operator=(triang_matrix<T, LOWER> &&rhs) noexcept
{
    LOG_DEBUG("Moving a triangular matrix");
    if (this == &rhs) {
        return *this;
    }
    util::deallocate_aligned(p_vals);
    p_vals = nullptr;
    p_rows = 0;
    p_cols = 0;
    p_non_zeros = 0;
    std::swap(p_vals, rhs.p_vals);
    std::swap(p_rows, rhs.p_rows);
    std::swap(p_cols, rhs.p_cols);
    std::swap(p_non_zeros, rhs.p_non_zeros);
    return *this;
}

// template <typename T, bool LOWER>
// template <typename ExpressionT>
// triang_matrix<T, LOWER> &
// triang_matrix<T, LOWER>::operator=(const expressions::operant<ExpressionT> &exp);

template <typename T, bool LOWER>
triang_matrix<T, LOWER> &
triang_matrix<T, LOWER>::operator=(const std::initializer_list<std::initializer_list<T>> &init_list)
{
    LOG_DEBUG("Assigning triangular matrix from initializer list");
    if (init_list.size() == 0) {
        allocate(0, 0);
        return *this;
    }
    allocate(init_list.size(), LOWER ? (init_list.begin() + init_list.size() - 1)->size()
                                     : init_list.begin()->size());
    size_type i = 0;
    T *start = p_vals;
    for (auto it = init_list.begin(); it != init_list.end(); ++it, ++i) {
        SHAPE_ASSERT(non_zeros(i) == it->size(), "Initializer list of invalid length");
        std::copy(it->begin(), it->end(), start);
        start += it->size();
    }
    return *this;
}
template <typename T, bool LOWER>
template <typename function>
triang_matrix<T, LOWER> &triang_matrix<T, LOWER>::apply_func(function func)
{
    LOG_DEBUG("Applying function to every element of a triangular matrix");
    auto range = std::views::iota(size_type(0), non_zeros());
    std::for_each(range.begin(), range.end(),
#ifdef PARALLEL
                  execution::par_unseq,
#endif
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
    return *this;
}

template <typename T, bool LOWER>
void triang_matrix<T, LOWER>::to_file(const std::string &filename, const bool binary) const
{
    util::file_writer writer(filename, binary);
    writer.append(p_rows);
    writer.append(p_cols);
    writer.append(p_non_zeros);
    writer.append(p_vals, p_non_zeros);
}

template <typename T, bool LOWER>
void triang_matrix<T, LOWER>::from_file(const std::string &filename, const bool binary)
{
    util::file_reader reader(filename, binary);
    // Read size information
    size_type rows = size_type(0), cols = size_type(0), non_zeros = size_type(0);
    reader.get(rows);
    reader.get(cols);
    reader.get(non_zeros);
    // Allocate memory
    allocate(rows, cols);
    reader.get(p_vals, p_non_zeros);
}

} // namespace la
#endif
