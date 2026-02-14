#ifndef LA_INTERNAL_ADD_H
#define LA_INTERNAL_ADD_H

#include "includes/types.hpp"
#include <functional>

namespace la
{
namespace internal
{

/// ===============================================
/// A D D I T I O N
/// ===============================================

/// @brief Add operation
/// @tparam ExpressionLeft type of first summand
/// @tparam ExpressionRight type of second summand
template <typename ExpressionLeft, typename ExpressionRight> class add_operation
{
public:
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

private:
    // no private members

public:
    /// @brief Add at element i
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y, const la::size_type i)
    {
        return std::plus<value_type>()(x.evaluate(i), y.evaluate(i));
    }

    /// @brief Add at element i, j
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y, const la::size_type i,
                                      const la::size_type j)
    {
        return std::plus<value_type>()(x.evaluate(i, j), y.evaluate(i, j));
    }
};

/// ===============================================
/// S U B S T R A C T I O N
/// ===============================================

/// @brief Substract operation
/// @tparam ExpressionLeft type of minuent
/// @tparam ExpressionRight type of subtrahent
template <typename ExpressionLeft, typename ExpressionRight> class sub_operation
{
public:
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

private:
    // no private members

public:
    /// @brief Substract at element i
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y, const la::size_type i)
    {
        return std::minus<value_type>()(x.evaluate(i), y.evaluate(i));
    }

    /// @brief Substract at element i, j
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y, const la::size_type i,
                                      const la::size_type j)
    {
        return std::minus<value_type>()(x.evaluate(i, j), y.evaluate(i, j));
    }
};

} // namespace internal
} // namespace la

#endif
