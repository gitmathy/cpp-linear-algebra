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
#include "la/util/macros.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>

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

public:
    /// @brief Construct an empty matrix
    explicit sparse_matrix();

    /// @brief Allocate memory and set shape
    void allocate(size_type rows, size_type cols, size_type num_values);

    /// @brief write access to an element
    inline T &operator()(const size_type i, const size_type j);

    /// @brief read access to an element
    inline const T &operator()(const size_type i, const size_type j) const;

    /// @brief Number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Number of columns
    inline size_type cols() const { return p_cols; }
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
sparse_matrix<T>::sparse_matrix()
    : p_vals(nullptr), p_col_idx(nullptr), p_row_ptr(nullptr), p_rows(0), p_cols(0)
{}

template <typename T>
void sparse_matrix<T>::allocate(size_type rows, size_type cols, size_type num_values)
{
    LOG_DEBUG("Allocating memory for sparse matrix: rows: "
              << rows << "values: " << num_values << ", memory: "
              << (num_values * (sizeof(T) + sizeof(size_type)) + rows * sizeof(size_type)) << " B");

    util::deallocate_aligned(p_vals);
    util::deallocate_aligned(p_col_idx);
    util::deallocate_aligned(p_row_ptr);
    p_vals = util::allocate_aligned<T>(num_values);
    p_col_idx = util::allocate_aligned<size_type>(num_values);
    p_row_ptr = util::allocate_aligned<size_type>(rows);
    p_rows = rows;
    p_cols = cols;
}

template <typename T>
inline T &sparse_matrix<T>::operator()(const size_type i, const size_type j)
{
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix: out of bound");
    LOG_TRACE("sparse_matrix: Write access to element " << i << ", " << j);
    size_type *it = std::lower_bound(p_col_idx + p_row_ptr[i], p_col_idx + p_row_ptr[i + 1], j);
    if (it == p_col_idx + p_row_ptr[i + 1] || *it != j) {
        throw util::error("sparse_matrix: Cannot write to a non-zero element");
    }
    return p_vals[*it];
}

template <typename T>
inline const T &sparse_matrix<T>::operator()(const size_type i, const size_type j) const
{
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix: out of bound");
    LOG_TRACE("sparse_matrix: Read access to element " << i << ", " << j);
    size_type const *it =
        std::lower_bound(p_col_idx + p_row_ptr[i], p_col_idx + p_row_ptr[i + 1], j);
    if (it == p_col_idx + p_row_ptr[i + 1] || *it != j) {
        return T(0);
    }
    return *it;
}

} // namespace la
#endif
