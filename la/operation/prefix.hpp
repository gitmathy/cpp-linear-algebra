/// Part of the project "cpp-linear-algebra"
///
/// @file la/operation/prefix.hpp
/// @brief Definition of prefixes for structures, e.g., -
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_OPERATIONS_PREFIX_HPP
#define LA_OPERATIONS_PREFIX_HPP

#include "la/data_structure/expressions/operant.hpp"
#include "la/data_structure/expressions/operations.hpp"
#include "la/data_structure/expressions/traits.hpp"
#include "la/data_structure/expressions/unary.hpp"
#include "la/data_structure/forward.hpp"

namespace la {

/// @brief -vector
template <typename T>
auto operator-(const vector<T> &right);

/// @brief -static_vector
template <typename T, size_type N>
auto operator-(const static_vector<T, N> &right);

/// @brief -matrix
template <typename T, storage_type StorageT>
auto operator-(const matrix<T, StorageT> &right);

/// @brief -operant
template <typename ExpT>
auto operator-(const expressions::operant<ExpT> &right);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

/// @brief -vector
template <typename T>
auto operator-(const vector<T> &right)
{
    typedef expressions::unary_expression<vector<T>, expressions::minus_operation<vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

/// @brief -static_vector
template <typename T, size_type N>
auto operator-(const static_vector<T, N> &right)
{
    typedef expressions::unary_expression<static_vector<T, N>,
                                          expressions::minus_operation<static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

/// @brief -matrix
template <typename T, storage_type StorageT>
auto operator-(const matrix<T, StorageT> &right)
{
    typedef expressions::unary_expression<matrix<T, StorageT>,
                                          expressions::minus_operation<matrix<T, StorageT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

/// @brief -operant
template <typename ExpT>
auto operator-(const expressions::operant<ExpT> &right)
{
    typedef expressions::unary_expression<expressions::operant<ExpT>,
                                          expressions::minus_operation<expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

} // namespace la

#endif
