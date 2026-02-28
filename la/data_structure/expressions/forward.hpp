/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/forward.hpp
/// @brief Forward declaration of expression types
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_EXPRESSIONS_FORWARD_HPP
#define LA_DATA_STRUCTURE_EXPRESSIONS_FORWARD_HPP

namespace la {
namespace expressions {

// Forward declaration expression_traits
// see la/data_structure/expressions/traits.hpp
template <typename ExpressionT>
struct expression_traits;

// Forward declaration operant
// see la/data_structure/expressions/operant.hpp
template <typename ExpressionT>
class operant;

// Forward declaration of binary_expression
// see la/data_structure/expressions/binary.hpp
template <typename ExpTLeft, typename ExpTRight, typename OpsT>
class binary_expression;

// Forward declaration of literal
// see la/data_structure/expressions/literal.hpp
template <typename T>
class literal;

// Forward declaration of minus_operation
// see la/data_structure/expressions/operations.hpp
template <typename ExpressionT>
struct minus_operation;

// Forward declaration of add_operation
// see la/data_structure/expressions/operations.hpp
template <typename ExpressionLeft, typename ExpressionRight>
struct add_operation;

// Forward declaration of sub_operation
// see la/data_structure/expressions/operations.hpp
template <typename ExpressionLeft, typename ExpressionRight>
struct sub_operation;

// Forward declaration of mult_operation
// see la/data_structure/expressions/operations.hpp
template <typename ExpressionLeft, typename ExpressionRight>
struct mult_operation;

// Forward declaration of matrix_multiply_op
// see la/data_structure/expressions/operations.hpp
template <typename MatTypeLeft, typename MatTypeRight>
struct matrix_multiply_op;

} // namespace expressions
} // namespace la
#endif
