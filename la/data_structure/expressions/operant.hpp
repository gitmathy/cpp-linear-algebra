/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/operant.hpp
/// @brief Definition and declaration of operants storing one component in an expression
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURES_EXPRESSIONS_OPERANT_HPP
#define LA_DATA_STRUCTURES_EXPRESSIONS_OPERANT_HPP

namespace la {
namespace expressions {

/// @brief An operant stores one operant of an operation, e.g, vector, scalar, other operant
/// @tparam ExpressionT type of the operant
template <typename ExpressionT>
class operant
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
    template <typename ExpT>
    operant(const operant<ExpT> &op) : p_expression(op.p_expression)
    {}

    /// @brief Moving from another operant (possibly different expression type)
    template <typename ExpT>
    operant(operant<ExpT> &&op) noexcept : p_expression(std::move(op.p_expression))
    {}

    /// @brief Evaluate operant
    inline value_type evaluate(const size_type i) const { return p_expression.evaluate(i); }

    /// @brief Evaluate operant (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const
    {
        return p_expression.evaluate(i, j);
    }

    /// @brief Get row_idx_begin
    inline size_type row_idx_begin(const size_type i) const
    {
        return p_expression.row_idx_begin(i);
    }

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type nz_idx) const { return p_expression.col_idx(nz_idx); }

    /// @brief Number of rows
    inline size_type rows() const { return p_expression.rows(); }

    /// @brief Number of columns
    inline size_type cols() const { return p_expression.cols(); }

    /// @brief Dimension of the operant is defined by the expression
    const static size_type dimension = ExpressionT::dimension;

    /// @brief Density is the same as for the expression
    const static bool dense = ExpressionT::dense;
};

} // namespace expressions
} // namespace la

#endif
