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
/// @tparam ExpT type of expression
/// @tparam OpsT type of unary operation
template <typename ExpT, typename OpsT>
class unary_expression
{
public:
    /// @brief Value type
    typedef typename expression_traits<ExpT>::value_type value_type;

    /// @brief Type of expression
    typedef typename expression_traits<ExpT>::expression_type expression_type;

private:
    /// @brief The left expression
    expression_type p_expression;

public:
    /// @brief No default constructor
    unary_expression() = delete;

    /// @brief Construct by values
    unary_expression(const expression_type &right) : p_expression(right) {}

    /// @brief Copying an unary expression
    unary_expression(const unary_expression &unary) : p_expression(unary.p_expression) {}

    /// @brief Moving an unary_expression
    unary_expression(unary_expression &&unary) noexcept
        : p_expression(std::move(unary.p_expression))
    {}

    /// @brief Evaluate unary
    inline value_type evaluate(const size_type i) const { return OpsT::evaluate(p_expression, i); }

    /// @brief Evaluate binary_expression (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const
    {
        return OpsT::evaluate(p_expression, i, j);
    }

    /// @brief Get the rows of the result
    inline size_type rows() const { return p_expression.rows(); }

    /// @brief Get the columns of the result
    inline size_type cols() const { return p_expression.cols(); }

    /// @brief Get dimension of result
    const static size_type dimension = ExpT::dimension;
};

} // namespace expressions

} // namespace la

#endif
