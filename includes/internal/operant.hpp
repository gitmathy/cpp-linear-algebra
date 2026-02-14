#ifndef LA_INTERNAL_OPERANT_H
#define LA_INTERNAL_OPERANT_H

#include "includes/internal/traits.hpp"
#include "includes/types.hpp"
#include <memory>

namespace la
{
namespace internal
{

/// @brief An operant stores one operant of an operation, e.g, vector, scalar, other operant
/// @tparam ExpressionT type of the operant
template <typename ExpressionT> class operant
{
public:
    /// @brief Type of the value
    typedef typename expression_traits<ExpressionT>::value_type value_type;

    /// @brief Type of the expression
    typedef typename expression_traits<ExpressionT>::expression_type expression_type;

private:
    /// @brief Owned expression (store by value to keep temporaries alive)
    expression_type p_expression;

public:
    /// @brief No default constructor
    operant() = delete;

    /// @brief Construct by expression (copy)
    operant(const ExpressionT &expression) : p_expression(expression) {}

    /// @brief Construct by expression (move)
    operant(ExpressionT &&expression) : p_expression(std::move(expression)) {}

    /// @brief Copying from another operant (possibly different expression type)
    template <typename ExpT> operant(const operant<ExpT> &op) : p_expression(op.p_expression) {}

    /// @brief Moving from another operant (possibly different expression type)
    template <typename ExpT> operant(operant<ExpT> &&op) noexcept : p_expression(std::move(op.p_expression)) {}

    /// @brief Evaluate operant
    inline value_type evaluate(const size_type i) const { return p_expression.evaluate(i); }

    /// @brief Evaluate operant (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const { return p_expression.evaluate(i, j); }

    inline size_type size() const { return p_expression.size(); }
};

} // namespace internal

} // namespace la

#endif
