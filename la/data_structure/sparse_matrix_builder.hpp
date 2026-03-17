/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/sparse_matrix_builder.hpp
/// @brief Declaration and definition of a sparse matrix class builder
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_SPARSE_MATRIX_BUILDER_HPP
#define LA_DATA_STRUCTURE_SPARSE_MATRIX_BUILDER_HPP

#include "la/data_structure/forward.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

namespace la {

/// @brief Build a sparse matrix. During build process, the elements can be accessed via operator
/// (i,j). This builder is optimized for "big columns" and many read/write accesses before building
/// the sparse matrix
template <typename T>
class sparse_matrix_builder
{
public:
    /// @brief Type of every element
    typedef T value_type;

private:
    /// @brief Values, for every row, map column to the value
    std::vector<std::unordered_map<size_type, T>> p_vals;

    /// @brief Number of columns
    size_type p_cols;

    /// @brief Number of values
    size_type p_num_values;

public:
    /// @brief Construct the sparse matrix builder
    explicit sparse_matrix_builder(const size_type rows, const size_type cols);

    /// @brief write access to an element
    inline T &operator()(const size_type i, const size_type j);

    /// @brief read access to an element
    inline const T operator()(const size_type i, const size_type j) const;

    /// @brief Number of rows
    inline size_type rows() const { return size_type(p_vals.size()); }

    /// @brief Number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Get number of non-zeros
    inline size_type non_zeros() const { return p_num_values; }

    /// @brief Build the sparse matrix (moves all elements to the matrix)
    sparse_matrix<T> &move(sparse_matrix<T> &a);

    /// @brief Assemble a sparse matrix (while keeping all elements in the builder)
    sparse_matrix<T> assemble() const;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
sparse_matrix_builder<T>::sparse_matrix_builder(const size_type rows, const size_type cols)
    : p_vals(rows), p_cols(cols), p_num_values(0)
{}

template <typename T>
inline T &sparse_matrix_builder<T>::operator()(const size_type i, const size_type j)
{
    LOG_TRACE("sparse_matrix_builder: Write access to element " << i << ", " << j);
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix_builder: out of bound");
    // try to include a new default value of "0" at position (i,j). If this element already exists,
    // emplace does not include it. In all cases, an iterator to the element is returned
    auto insert = p_vals[i].emplace(std::make_pair(j, T(0)));
    p_num_values += insert.second ? 1 : 0;
    return insert.first->second;
}

template <typename T>
inline const T sparse_matrix_builder<T>::operator()(const size_type i, const size_type j) const
{
    LOG_TRACE("sparse_matrix_builder: Read access to element " << i << ", " << j);
    BOUNDARY_ASSERT(i < rows() && j < cols(), "sparse_matrix_builder: out of bound");
    if (auto it = p_vals[i].find(j); it != p_vals[i].end()) {
        // element has been inserted
        return it->second;
    }
    // no element found, so return 0
    return T(0);
}

template <typename T>
sparse_matrix<T> &sparse_matrix_builder<T>::move(sparse_matrix<T> &a)
{
    LOG_DEBUG("Move all elements from a sparse matrix builder to a sparse matrix");
    // allocate memory for the matrix
    a.allocate(rows(), cols(), p_num_values);

    // Next element to insert
    T *next_val = a.p_vals;
    // Next column index to insert
    size_type *next_idx = a.p_col_idx;
    // Next row ptr to insert
    size_type *next_row = a.p_row_ptr;
    *next_row = 0;

    // build every row
    for (size_type i = 0; i < rows(); ++i) {
        const size_type col_size = size_type(p_vals[i].size());
        // We want the rows ordered by column indices, so move them to a vector and sort them
        std::vector<std::pair<size_type, T>> column;
        column.reserve(col_size);
        for (auto &it : p_vals[i]) {
            column.emplace_back(it.first, std::move(it.second));
        }
        std::sort(column.begin(), column.end(), [](auto a, auto b) { return a.first < b.first; });
        // now, put the sorted values into the matrix
        const size_type next_row_ptr = *next_row + col_size;
        *(++next_row) = next_row_ptr;
        for (auto &element : column) {
            *(next_val++) = std::move(element.second);
            *(next_idx++) = element.first;
        }
    }
    LOG_DEBUG("Created sparse matrix from builder");
    p_vals.resize(0);
    p_cols = 0;
    p_num_values = 0;
    return a;
}

template <typename T>
sparse_matrix<T> sparse_matrix_builder<T>::assemble() const
{
    LOG_DEBUG("Build a sparse matrix from a sparse matrix builder");

    sparse_matrix<T> a;

    // allocate memory for the matrix
    a.allocate(rows(), cols(), p_num_values);

    // Next element to insert
    T *next_val = a.p_vals;
    // Next column index to insert
    size_type *next_idx = a.p_col_idx;
    // Next row ptr to insert
    size_type *next_row = a.p_row_ptr;
    *next_row = 0;

    // build every row
    for (size_type i = 0; i < rows(); ++i) {
        const size_type col_size = size_type(p_vals[i].size());
        // We want the rows ordered by column indices, so copy them to a vector and sort them
        std::vector<std::pair<size_type, T>> column;
        column.reserve(col_size);
        for (auto &it : p_vals[i]) {
            column.push_back(std::make_pair(it.first, it.second));
        }
        std::sort(column.begin(), column.end(), [](auto a, auto b) { return a.first < b.first; });
        // now, put the sorted values into the matrix
        const size_type next_row_ptr = *next_row + col_size;
        *(++next_row) = next_row_ptr;
        for (auto &element : column) {
            *(next_val++) = element.second;
            *(next_idx++) = element.first;
        }
    }
    LOG_DEBUG("Created sparse matrix from builder");
    return a;
}

} // namespace la
#endif
