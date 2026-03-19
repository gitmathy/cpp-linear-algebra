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

#include "la/util/types.hpp"
#include <memory>

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

    /// @brief Type of an iterator to constant indices
    typedef const size_type *cidx_iterator;

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
    operant(const operant<ExpT> &op);

    /// @brief Moving from another operant (possibly different expression type)
    template <typename ExpT>
    operant(operant<ExpT> &&op) noexcept;

    /// @brief Evaluate operant
    inline value_type evaluate(const size_type i) const;

    /// @brief Evaluate operant (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const;

    /// @brief Get row_idx_begin
    inline size_type row_idx_begin(const size_type i) const;

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type nz_idx) const;

    /// @brief Number of rows
    inline size_type rows() const { return p_expression.rows(); }

    /// @brief Number of columns
    inline size_type cols() const { return p_expression.cols(); }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_expression.non_zeros(); }

    /// @brief Constant iterator to begin of column indices
    inline auto begin_col_idx(const size_type i) const;

    /// @brief Constant iterator to end of column indices
    inline auto end_col_idx(const size_type i) const;

    /// @brief Dimension of the operant is defined by the expression
    constexpr static size_type dimension = ExpressionT::dimension;

    /// @brief Density is the same as for the expression
    constexpr static bool dense = ExpressionT::dense;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename ExpressionT>
template <typename ExpT>
operant<ExpressionT>::operant(const operant<ExpT> &op) : p_expression(op.p_expression)
{}

template <typename ExpressionT>
template <typename ExpT>
operant<ExpressionT>::operant(operant<ExpT> &&op) noexcept
    : p_expression(std::move(op.p_expression))
{}

template <typename ExpressionT>
inline operant<ExpressionT>::value_type operant<ExpressionT>::evaluate(const size_type i) const
{
    LOG_TRACE("Operant evaluation at " << i);
    BOUNDARY_ASSERT((ExpressionT::dimension < 2 && i < rows()) ||
                        (ExpressionT::dimension == 2 && i < non_zeros()),
                    "operant row_idx_begin: index out of bound");
    return p_expression.evaluate(i);
}

template <typename ExpressionT>
inline operant<ExpressionT>::value_type operant<ExpressionT>::evaluate(const size_type i,
                                                                       const size_type j) const
{
    LOG_TRACE("Operant evaluation at " << i << " / " << rows() << ", " << j << " / " << cols());
    BOUNDARY_ASSERT(i < rows() && j < cols(), "operant evaluate: index out of bound");
    return p_expression.evaluate(i, j);
}

template <typename ExpressionT>
inline size_type operant<ExpressionT>::row_idx_begin(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "operant row_idx_begin: index out of bound");
    return p_expression.row_idx_begin(i);
}

template <typename ExpressionT>
inline size_type operant<ExpressionT>::col_idx(const size_type nz_idx) const
{
    BOUNDARY_ASSERT(nz_idx < non_zeros(), "operant col_idx: index out of bound");
    return p_expression.col_idx(nz_idx);
}

template <typename ExpressionT>
inline auto operant<ExpressionT>::begin_col_idx(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "operant begin_col_idx: index out of bound");
    return p_expression.begin_col_idx(i);
}

template <typename ExpressionT>
inline auto operant<ExpressionT>::end_col_idx(const size_type i) const
{
    BOUNDARY_ASSERT(i <= rows(), "operant end_col_idx: index out of bound");
    return p_expression.end_col_idx(i);
}

} // namespace expressions
} // namespace la

#endif
