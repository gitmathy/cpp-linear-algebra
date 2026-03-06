/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/mixed_sparse_data.hpp
/// @brief Implementations of function using mixed sparse data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_MIXED_SPARSE_DATA_HPP
#define LA_DATA_STRUCTURE_MIXED_SPARSE_DATA_HPP

#include "la/data_structure/sparse_matrix.hpp"
#include "la/data_structure/sparse_matrix_builder.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"

namespace la {

// Member of sparse_matrix
// -----------------------

template <typename T>
sparse_matrix<T>::sparse_matrix(sparse_matrix_builder<T> &&rhs) noexcept
    : p_vals(nullptr), p_col_idx(nullptr), p_row_ptr(nullptr), p_rows(0), p_cols(0)
{
    *this = std::move(rhs);
}

template <typename T>
sparse_matrix<T> &sparse_matrix<T>::operator=(sparse_matrix_builder<T> &&rhs) noexcept
{
    rhs.move(*this);
    return *this;
}

} // namespace la
#endif
