/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/sparse_matrix.hpp
/// @brief Declaration and definition of a sparse matrix class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_SPARSE_MATRIX_HPP
#define LA_DATA_STRUCTURE_SPARSE_MATRIX_HPP

#include "la/data_structure/forward.hpp"
#include "la/util/error.hpp"
#include "la/util/file_io.hpp"
#include "la/util/macros.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <initializer_list>

namespace la {

/// @brief Sparse matrix class using the CSR (compressed storage row) format
/// @tparam T
template <typename T>
class sparse_matrix
{
public:
    /// @brief Type of every element
    typedef T value_type;

    /// @brief Definition of iterator type
    typedef T *iterator;
    /// @brief Definition of constant iterator type
    typedef const T *citerator;

    /// @brief Definition of index iterator type
    typedef size_type *idx_iterator;
    /// @brief Definition of constant index iterator type
    typedef const size_type *cidx_iterator;

    /// @brief Builder is allowed to access the raw (private) elements
    friend class sparse_matrix_builder<T>;

private:
    /// @brief Storage of the values
    T *p_vals;

    /// @brief Column indices
    size_type *p_col_idx;

    /// @brief Index of first element in a row
    size_type *p_row_ptr;

    /// @brief Number of rows
    size_type p_rows;

    /// @brief Number of columns
    size_type p_cols;

    /// @brief Total number of values
    size_type p_num_vals;

public:
    /// public variable members

    /// @brief Dimension of a matrix
    const static size_type dimension = size_type(2);

    /// @brief This matrix is dense
    const static bool dense = false;

public:
    /// @brief Construct an empty matrix
    explicit sparse_matrix();

    /// @brief Construct from initializer lists
    sparse_matrix(const std::initializer_list<std::initializer_list<size_type>> &col_idx,
                  const std::initializer_list<T> &values, const size_type cols);

    /// @brief Move from a sparse matrix builder
    explicit sparse_matrix(sparse_matrix_builder<T> &&rhs) noexcept;

    /// @brief Free all the memory
    ~sparse_matrix();

    /// @brief Allocate memory and set shape
    void allocate(const size_type rows, const size_type cols, const size_type num_values);

    /// @brief Number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_num_vals; }

    /// @brief Get first index in row i
    inline size_type row_idx_begin(const size_type i) const;

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type nz_idx) const;

    /// @brief write access to an element
    inline T &operator()(const size_type i, const size_type j);

    /// @brief read access to an element
    inline const T operator()(const size_type i, const size_type j) const;

    /// @brief read access to i'th element
    inline const T &operator()(const size_type i) const;

    /// @brief Evaluate matrix at (i,j), i.e., read element (i,j)
    inline const T evaluate(const size_type i, const size_type j) const;

    /// @brief Evaluate sparse matrix at (i), means reading i'th non-zero
    inline const T &evaluate(const size_type i) const;

    /// @brief Iterator to begin of values
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end of values
    inline iterator end() { return p_vals + p_num_vals; }

    /// @brief Constant iterator to begin of values
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end of values
    inline citerator end() const { return p_vals + p_num_vals; }

    /// @brief Iterator to begin of values in a row
    inline iterator row_begin(const size_type i);
    /// @brief Iterator to end of values in a row
    inline iterator row_end(const size_type i);

    /// @brief Constant iterator to begin of values in a row
    inline citerator row_begin(const size_type i) const;
    /// @brief Constant iterator to end of values in a row
    inline citerator row_end(const size_type i) const;

    /// @brief Iterator to begin of row pointer
    inline idx_iterator begin_row_ptr() { return p_row_ptr; }
    /// @brief Iterator to end of row pointer
    inline idx_iterator end_row_ptr() { return p_row_ptr + p_rows + 1; }

    /// @brief Constant iterator to begin of row pointer
    inline cidx_iterator begin_row_ptr() const { return p_row_ptr; }
    /// @brief Constant iterator to end of row pointer
    inline cidx_iterator end_row_ptr() const { return p_row_ptr + p_rows + 1; }

    /// @brief Iterator to begin of column indices
    inline idx_iterator begin_col_idx() { return p_col_idx; }
    /// @brief Iterator to end of column indices
    inline idx_iterator end_col_idx() { return p_col_idx + p_num_vals; }

    /// @brief Constant iterator to begin of column indices
    inline cidx_iterator begin_col_idx() const { return p_col_idx; }
    /// @brief Constant iterator to end of column indices
    inline cidx_iterator end_col_idx() const { return p_col_idx + p_num_vals; }

    /// @brief Iterator to begin of column indices
    inline idx_iterator begin_col_idx(const size_type i);
    /// @brief Iterator to end of column indices
    inline idx_iterator end_col_idx(const size_type i);

    /// @brief Constant iterator to begin of column indices
    inline cidx_iterator begin_col_idx(const size_type i) const;
    /// @brief Constant iterator to end of column indices
    inline cidx_iterator end_col_idx(const size_type i) const;

    /// @brief Write matrix to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true) const;

    /// @brief Read matrix from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
sparse_matrix<T>::sparse_matrix()
    : p_vals(nullptr), p_col_idx(nullptr), p_row_ptr(nullptr), p_rows(0), p_cols(0), p_num_vals(0)
{}

template <typename T>
sparse_matrix<T>::sparse_matrix(
    const std::initializer_list<std::initializer_list<size_type>> &col_idx,
    const std::initializer_list<T> &values, const size_type cols)
    : p_vals(nullptr), p_col_idx(nullptr), p_row_ptr(nullptr), p_rows(0), p_cols(0), p_num_vals(0)
{
    allocate(col_idx.size(), cols, values.size());
    LOG_DEBUG("Construct sparse matrix by initializer list");
    size_type *next_row = begin_row_ptr();
    *next_row = 0;
    for (std::initializer_list<size_type> col_indices_in_row : col_idx) {
        LOG_TRACE("Assigning " << col_indices_in_row.size() << " values in row");
        const size_type next_row_ptr = *next_row + col_indices_in_row.size();
        std::copy(col_indices_in_row.begin(), col_indices_in_row.end(),
                  begin_col_idx() + *next_row);
        BOUNDARY_ASSERT(next_row + 1 != end_row_ptr(), "Row pointer out of bound");
        *(++next_row) = next_row_ptr;
    }
    LOG_DEBUG("Indices assigned (" << *next_row << "), now, assign values(" << num_vals() << ")");
    SHAPE_ASSERT(*next_row == non_zeros(), "column indices do not match number of values");
    std::copy(values.begin(), values.end(), p_vals);
}

template <typename T>
sparse_matrix<T>::~sparse_matrix()
{
    util::deallocate_aligned(p_vals);
    util::deallocate_aligned(p_col_idx);
    util::deallocate_aligned(p_row_ptr);
}

template <typename T>
void sparse_matrix<T>::allocate(const size_type rows, const size_type cols,
                                const size_type num_values)
{
    LOG_DEBUG("Allocating memory for sparse matrix - rows: "
              << rows << ", values: " << num_values << ", memory: "
              << (num_values * (sizeof(T) + sizeof(size_type)) + rows * sizeof(size_type)) << " B");

    util::deallocate_aligned(p_vals);
    util::deallocate_aligned(p_col_idx);
    util::deallocate_aligned(p_row_ptr);
    p_vals = util::allocate_aligned<T>(num_values);
    p_col_idx = util::allocate_aligned<size_type>(num_values);
    p_row_ptr = util::allocate_aligned<size_type>(rows + 1);
    p_rows = rows;
    p_cols = cols;
    p_num_vals = num_values;
}

template <typename T>
inline size_type sparse_matrix<T>::row_idx_begin(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: row_idx_begin index out of bound");
    return p_row_ptr[i];
}

template <typename T>
inline size_type sparse_matrix<T>::col_idx(const size_type nz_idx) const
{
    BOUNDARY_ASSERT(nz_idx < non_zeros(), "sparse_matrix: col_idx index out of bound");
    return p_col_idx[nz_idx];
}

template <typename T>
inline T &sparse_matrix<T>::operator()(const size_type i, const size_type j)
{
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix: out of bound");
    LOG_TRACE("sparse_matrix: Write access to element " << i << ", " << j);
    size_type *last = p_col_idx + p_row_ptr[i + 1];
    size_type *it = std::lower_bound(p_col_idx + p_row_ptr[i], last, j);
    if (it == last || *it != j) {
        throw util::error("sparse_matrix: Cannot write to a non-zero element");
    }
    return p_vals[*it];
}

template <typename T>
inline const T sparse_matrix<T>::operator()(const size_type i, const size_type j) const
{
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix: out of bound");
    LOG_TRACE("sparse_matrix: Read access to element " << i << ", " << j);
    size_type *const last = p_col_idx + p_row_ptr[i + 1];
    size_type *const it = std::lower_bound(p_col_idx + p_row_ptr[i], last, j);
    if (it == last || *it != j) {
        return T(0);
    }
    return *it;
}

template <typename T>
inline const T &sparse_matrix<T>::operator()(const size_type i) const
{
    BOUNDARY_ASSERT(i < non_zeros(), "sparse_matrix: index out of bound");
    LOG_TRACE("sparse_matrix: Read access to " << i << "'th element");
    return p_vals[i];
}

template <typename T>
inline const T sparse_matrix<T>::evaluate(const size_type i, const size_type j) const
{
    LOG_TRACE("Evaluating matrix at position " << i << ", " << j);
    return (*this)(i, j);
}

template <typename T>
inline const T &sparse_matrix<T>::evaluate(const size_type i) const
{
    LOG_TRACE("Evaluating matrix at " << i << "'th non-zero");
    return (*this)(i);
}

template <typename T>
inline sparse_matrix<T>::iterator sparse_matrix<T>::row_begin(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: row_begin index out of bound");
    return p_vals + p_row_ptr[i];
}

template <typename T>
inline sparse_matrix<T>::iterator sparse_matrix<T>::row_end(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: row_end index out of bound");
    return p_vals + p_row_ptr[i + 1];
}

template <typename T>
inline sparse_matrix<T>::citerator sparse_matrix<T>::row_begin(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: row_begin index out of bound");
    return p_vals + p_row_ptr[i];
}

template <typename T>
inline sparse_matrix<T>::citerator sparse_matrix<T>::row_end(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: row_end index out of bound");
    return p_vals + p_row_ptr[i + 1];
}

template <typename T>
inline sparse_matrix<T>::idx_iterator sparse_matrix<T>::begin_col_idx(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: begin_col_idx index out of bound");
    return p_col_idx + p_row_ptr[i];
}
template <typename T>
inline sparse_matrix<T>::idx_iterator sparse_matrix<T>::end_col_idx(const size_type i)
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: end_col_idx index out of bound");
    return p_col_idx + p_row_ptr[i + 1];
}

template <typename T>
inline sparse_matrix<T>::cidx_iterator sparse_matrix<T>::begin_col_idx(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: begin_col_idx index out of bound");
    return p_col_idx + p_row_ptr[i];
}

template <typename T>
inline sparse_matrix<T>::cidx_iterator sparse_matrix<T>::end_col_idx(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "sparse_matrix: end_col_idx index out of bound");
    return p_col_idx + p_row_ptr[i + 1];
}

template <typename T>
void sparse_matrix<T>::to_file(const std::string &filename, const bool binary) const
{
    util::file_writer writer(filename, binary);
    writer.append(p_rows);
    writer.append(p_cols);
    writer.append(p_num_vals);
    writer.append(p_vals, p_num_vals);
    writer.append(p_col_idx, p_num_vals);
    writer.append(p_row_ptr, p_rows + 1);
}

template <typename T>
void sparse_matrix<T>::from_file(const std::string &filename, const bool binary)
{
    util::file_reader reader(filename, binary);
    // Read size information
    size_type rows = size_type(0), cols = size_type(0), num_vals = size_type(0);
    reader.get(rows);
    reader.get(cols);
    reader.get(num_vals);
    // Allocate memory
    allocate(rows, cols, num_vals);
    // Read values
    reader.get(p_vals, num_vals);
    reader.get(p_col_idx, num_vals);
    reader.get(p_row_ptr, rows + 1);
}

} // namespace la
#endif
