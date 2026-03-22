/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/util/concepts.hpp
/// @brief Definition and declaration of solving linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_UTIL_CONCEPTS_HPP
#define LA_ALGORITHM_UTIL_CONCEPTS_HPP

#include "la/util/types.hpp"
#include <concepts>

namespace la {
namespace util {

/// @brief Check if T has value_type defined
template <typename T>
concept has_value_type = requires { typename T::value_type; };

/// @brief Check if two data structured define the same value_type
template <typename T, typename U>
concept same_value_type = requires {
    typename T::value_type;
    typename U::value_type;
} && std::same_as<typename T::value_type, typename U::value_type>;

/// @brief Check if T provides access to elements via row and column index, i.e., (i,j)
template <typename T>
concept has_row_col_element_access = requires(T &m, size_type r, size_type c) {
    { m(r, c) };
};

/// @brief Check if T can be accessed via a row index, i.e., (i)
template <typename T>
concept has_nnz_access = requires(T &v, size_type r) {
    { v(r) };
};

/// @brief Check I provides access to values via row_begin()
template <typename T>
concept has_row_begin_access = requires(T &t, size_type r) {
    { t.row_begin(r) };
};

/// @brief Check if T provides row_index_begin
template <typename T>
concept has_row_idx_begin = requires(T &t, size_type r) {
    { t.row_idx_begin(r) };
};

/// @brief Check if T provides begin_col_idx
template <typename T>
concept has_begin_col_idx = requires(T &t, size_type r) {
    { t.begin_col_idx(r) };
};

/// @brief Check if T provides end_col_idx
template <typename T>
concept has_end_col_idx = requires(T &t, size_type r) {
    { t.end_col_idx(r) };
};

template <typename T>
concept has_col_idx = requires(T &t, size_type r) {
    { t.col_idx(r) };
};

/// @brief Check if provides access to values via vals()
template <typename T>
concept has_vals_access = requires(T &t) {
    { t.vals() };
};

/// @brief Check if provides access to row pointers
template <typename T>
concept has_row_ptr_access = requires(T &t) {
    { t.begin_row_ptr() };
};

/// @brief Check if provides access to column indices
template <typename T>
concept has_col_idx_access = requires(T &t) {
    { t.begin_col_idx() };
};

/// @brief Check if provides access finding diag element
template <typename T>
concept has_diag_idx = requires(T &t, size_type r) {
    { t.diag_idx(r) };
};

template <typename T, typename VecT>
concept has_solve = requires(T &t, VecT &b, VecT &x) {
    { t.solve(b, x) };
};

} // namespace util
} // namespace la
#endif
