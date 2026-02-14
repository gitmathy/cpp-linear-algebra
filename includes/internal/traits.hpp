#ifndef LA_INTERNAL_TRAITS_H
#define LA_INTERNAL_TRAITS_H

namespace la
{
// forward-declare vector so we can specialize expression_traits for it
template <typename T> class vector;

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

} // namespace internal

} // namespace la

#endif
