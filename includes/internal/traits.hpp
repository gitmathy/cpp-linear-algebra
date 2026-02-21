/// Part of the project "cpp-linear-algebra"
///
/// @file includes/internal/traits.hpp
/// @brief Definition and declaration of traits
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_INTERNAL_TRAITS_H
#define LA_INTERNAL_TRAITS_H

#include "includes/types.hpp"

namespace la {
// forward-declare vector so we can specialize expression_traits for it
template <typename T>
class vector;

// forward-declare matrix so we can specialize expression_traits for it
template <typename T, storage_type StorageT>
class matrix;

// forward-declare literal so we can specialize expression_traits for it
template <typename T>
class literal;

namespace internal {

/// @brief Determining expression type and value type from an expression
/// @tparam ExpressionT the expression type
template <typename ExpressionT>
struct expression_traits
{
    /// @brief type of the expression
    typedef const ExpressionT expression_type;

    /// @brief type of the values
    typedef typename ExpressionT::value_type value_type;

    /// @brief dimension of the expression
    const static size_type dimension = ExpressionT::dimension;
};

/// @brief Specialization for `la::vector<T>`: store as a reference in expression nodes
/// This avoids copying large vector objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<la::vector<T>>
{
    typedef const la::vector<T> &expression_type;
    typedef T value_type;
    const static size_type dimension = size_type(1);
};

/// @brief Specialization for `la::matrix<T,StorageT>`: store as a reference in expression nodes
/// This avoids copying large matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T, storage_type StorageT>
struct expression_traits<la::matrix<T, StorageT>>
{
    typedef const la::matrix<T, StorageT> &expression_type;
    typedef T value_type;
    const static size_type dimension = size_type(2);
};

/// @brief Specialization for `la::internal::literal<T>`: store as a reference in expression nodes
/// This avoids copying large matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<la::literal<T>>
{
    typedef la::literal<T> expression_type;
    typedef T value_type;
    const static size_type dimension = size_type(0);
};

} // namespace internal

} // namespace la

#endif
