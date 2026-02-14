#ifndef LA_INTERNAL_TRAITS_H
#define LA_INTERNAL_TRAITS_H

namespace la
{
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

} // namespace internal

} // namespace la

#endif
