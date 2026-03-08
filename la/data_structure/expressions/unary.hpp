/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/unary.hpp
/// @brief Definition and declaration of unary expressions, e.g. -x
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURES_UNARY_HPP
#define LA_DATA_STRUCTURES_UNARY_HPP

#include "la/data_structure/expressions/traits.hpp"
#include "la/util/types.hpp"

namespace la {
namespace expressions {

/// @brief Representing an unary expression consisting one "operants" and an operation, e.g.,
/// (vector, minus)
/// @tparam ExpressionT type of expression
/// @tparam OpsT type of unary operation
template <typename ExpressionT, typename OpsT>
class unary_expression
{
public:
    /// @brief Value type
    typedef typename expression_traits<ExpressionT>::value_type value_type;

    /// @brief Type of expression
    typedef typename expression_traits<ExpressionT>::expression_type expression_type;

private:
    /// @brief The expression
    expression_type p_expression;

public:
    /// @brief No default constructor
    unary_expression() = delete;

    /// @brief Construct by values
    unary_expression(const expression_type &right) : p_expression(right) {}

    /// @brief Copying an unary expression
    unary_expression(const unary_expression &unary) : p_expression(unary.p_expression) {}

    /// @brief Moving an unary_expression
    unary_expression(unary_expression &&unary) noexcept;

    /// @brief Evaluate unary
    inline value_type evaluate(const size_type i) const;

    /// @brief Evaluate binary_expression (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const;

    /// @brief Get the rows of the result
    inline size_type rows() const { return p_expression.rows(); }

    /// @brief Get the columns of the result
    inline size_type cols() const { return p_expression.cols(); }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_expression.non_zeros(); }

    /// @brief Get dimension of result
    constexpr static size_type dimension = ExpressionT::dimension;

    /// @brief Density is the same as for the expression
    constexpr static bool dense = ExpressionT::dense;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename ExpressionT, typename OpsT>
unary_expression<ExpressionT, OpsT>::unary_expression(unary_expression &&unary) noexcept
    : p_expression(std::move(unary.p_expression))
{}

template <typename ExpressionT, typename OpsT>
inline unary_expression<ExpressionT, OpsT>::value_type
unary_expression<ExpressionT, OpsT>::evaluate(const size_type i) const
{
    LOG_TRACE("unary_expression evaluation at " << i);
    BOUNDARY_ASSERT((ExpressionT::dimension < 2 && i < rows()) ||
                        (ExpressionT::dimension == 2 && i < non_zeros()),
                    "unary_expression row_idx_begin: index out of bound");
    return OpsT::evaluate(p_expression, i);
}

template <typename ExpressionT, typename OpsT>
inline unary_expression<ExpressionT, OpsT>::value_type
unary_expression<ExpressionT, OpsT>::evaluate(const size_type i, const size_type j) const
{
    LOG_TRACE("unary_expression evaluation at " << i << " / " << rows() << ", " << j << " / "
                                                << cols());
    BOUNDARY_ASSERT(i < rows() && j < cols(), "unary_expression evaluate: index out of bound");
    return OpsT::evaluate(p_expression, i, j);
}

} // namespace expressions
} // namespace la

#endif
