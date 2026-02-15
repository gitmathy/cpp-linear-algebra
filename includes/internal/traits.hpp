#ifndef LA_INTERNAL_TRAITS_H
#define LA_INTERNAL_TRAITS_H

#include "includes/types.hpp"

namespace la
{
// forward-declare vector so we can specialize expression_traits for it
template <typename T> class vector;

// forward-declare vector so we can specialize expression_traits for it
template <typename T, storage_type storage> class matrix;

namespace internal
{

/// @brief Determining expression type and value type from an expression
/// @tparam ExpressionT the expression type
template <typename ExpressionT> struct expression_traits
{
    /// @brief type of the expression
    typedef const ExpressionT expression_type;

    /// @brief type of the values
    typedef typename ExpressionT::value_type value_type;
};

/// @brief Specialization for `la::vector<T>`: store as a reference in expression nodes
/// This avoids copying large vector objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T> struct expression_traits<la::vector<T>>
{
    typedef const la::vector<T> &expression_type;
    typedef T value_type;
};

/// @brief Specialization for `la::matrix<T,storage>`: store as a reference in expression nodes
/// This avoids copying large matrix objects into expression trees; operant/binary_expression
/// will hold references to existing vectors while `operant` itself still owns temporaries.
template <typename T, storage_type storage> struct expression_traits<la::matrix<T, storage>>
{
    typedef const la::matrix<T, storage> &expression_type;
    typedef T value_type;
};

} // namespace internal

} // namespace la

#endif
