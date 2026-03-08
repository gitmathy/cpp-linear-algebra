/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/traits.hpp
/// @brief Definition and declaration of traits
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURES_EXPRESSIONS_TRAITS_HPP
#define LA_DATA_STRUCTURES_EXPRESSIONS_TRAITS_HPP

#include "la/data_structure/expressions/literal.hpp"
#include "la/data_structure/matrix.hpp"
#include "la/data_structure/sparse_matrix.hpp"
#include "la/data_structure/static_vector.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/types.hpp"

namespace la {
namespace expressions {

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
    constexpr static size_type dimension = ExpressionT::dimension;

    /// @brief density
    constexpr static bool dense = ExpressionT::dense;
};

/// @brief Specialization for `vector<T>`: store as a reference in expression nodes
/// This avoids copying large vector objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<vector<T>>
{
    typedef const vector<T> &expression_type;
    typedef T value_type;
    constexpr static size_type dimension = size_type(1);
    constexpr static bool dense = vector<T>::dense;
};

/// @brief Specialization for `static_vector<T,N>`: store as a reference in expression nodes
/// This avoids copying large vector objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T, size_type N>
struct expression_traits<static_vector<T, N>>
{
    typedef const static_vector<T, N> &expression_type;
    typedef T value_type;
    constexpr static size_type dimension = size_type(1);
    constexpr static bool dense = static_vector<T, N>::dense;
};

/// @brief Specialization for `matrix<T,StorageT>`: store as a reference in expression nodes
/// This avoids copying large matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<matrix<T>>
{
    typedef const matrix<T> &expression_type;
    typedef T value_type;
    constexpr static size_type dimension = size_type(2);
    constexpr static bool dense = matrix<T>::dense;
};

/// @brief Specialization for `spare_matrix<T>`: store as a reference in expression nodes
/// This avoids copying large sparse matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<sparse_matrix<T>>
{
    typedef const sparse_matrix<T> &expression_type;
    typedef T value_type;
    constexpr static size_type dimension = size_type(2);
    constexpr static bool dense = sparse_matrix<T>::dense;
};

/// @brief Specialization for `internal::literal<T>`: store as a reference in expression nodes
/// This avoids copying large matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T>
struct expression_traits<literal<T>>
{
    typedef literal<T> expression_type;
    typedef T value_type;
    constexpr static size_type dimension = size_type(0);
    constexpr static bool dense = literal<T>::dense;
};

} // namespace expressions

} // namespace la

#endif
