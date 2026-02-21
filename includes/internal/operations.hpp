/// Part of the project "cpp-linear-algebra"
///
/// @file includes/internal/operations.hpp
/// @brief Definition and declaration of operations available to matrices and vectors
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_INTERNAL_ADD_H
#define LA_INTERNAL_ADD_H

#include "includes/assert.hpp"
#include "includes/types.hpp"
#include <functional>

namespace la {
namespace internal {

/// ===============================================
/// M I N U S
/// ===============================================

/// @brief Minus of an expression
/// @tparam ExpressionT type of the expression
template <typename ExpressionT>
struct minus_operation
{
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionT::value_type value_type;

    /// @brief Invert at element i
    static inline value_type evaluate(const ExpressionT &x, const la::size_type i)
    {
        return -x.evaluate(i);
    }

    /// @brief Add at element i, j
    static inline value_type evaluate(const ExpressionT &x, const la::size_type i,
                                      const la::size_type j)
    {
        return -x.evaluate(i, j);
    }
};

/// ===============================================
/// A D D I T I O N
/// ===============================================

/// @brief Add operation
/// @tparam ExpressionLeft type of first summand
/// @tparam ExpressionRight type of second summand
template <typename ExpressionLeft, typename ExpressionRight>
struct add_operation
{
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

    /// @brief Add at element i
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y,
                                      const la::size_type i)
    {
        return std::plus<value_type>()(x.evaluate(i), y.evaluate(i));
    }

    /// @brief Add at element i, j
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y,
                                      const la::size_type i, const la::size_type j)
    {
        return std::plus<value_type>()(x.evaluate(i, j), y.evaluate(i, j));
    }
};

/// ===============================================
/// S U B S T R A C T I O N
/// ===============================================

/// @brief Substract operation
/// @tparam ExpressionLeft type of minuend
/// @tparam ExpressionRight type of subtrahend
template <typename ExpressionLeft, typename ExpressionRight>
struct sub_operation
{
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

    /// @brief Substract at element i
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y,
                                      const la::size_type i)
    {
        return std::minus<value_type>()(x.evaluate(i), y.evaluate(i));
    }

    /// @brief Substract at element i, j
    static inline value_type evaluate(const ExpressionLeft &x, const ExpressionRight &y,
                                      const la::size_type i, const la::size_type j)
    {
        return std::minus<value_type>()(x.evaluate(i, j), y.evaluate(i, j));
    }
};

/// =======================================================
/// M U L T I P L I C A T I O N
/// =======================================================

/// @brief Multiplication operation
/// @tparam ExpressionLeft type of left factor
/// @tparam ExpressionRight type of right factor
template <typename ExpressionLeft, typename ExpressionRight>
struct mult_operation
{
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

    /// @brief Multiply at row i (result is one-dimensional)
    /// We are parallelizing at outer loop to evaluate the expression yielding from this operation
    static inline value_type evaluate(const ExpressionLeft &left, const ExpressionRight &right,
                                      const size_type i)
    {
        LAYOUT_ASSERT(ExpressionRight::dimension < 2,
                      "Multiplication at (i) is only valid for zero- or one-dimensional rhs");
        if constexpr (ExpressionLeft::dimension == 2 && ExpressionRight::dimension == 1) {
            // multiplying a matrix-like left hand side with a vector-like right hand side
            SHAPE_ASSERT(left.cols() == right.rows(), "Multiplying matrix*vector");
            value_type init = value_type(0);
            for (size_type j = 0; j < right.rows(); ++j) {
                init += left.evaluate(i, j) * right.evaluate(j);
            }
            return init;
        }
        // vector*vector, scalar*vector, or vector*scalar
        return left.evaluate(i) * right.evaluate(i);
    }

    /// @brief Multiply at element (i,j) (result is two-dimensional)
    static inline value_type evaluate(const ExpressionLeft &left, const ExpressionRight &right,
                                      const la::size_type i, const la::size_type j)
    {
        LAYOUT_ASSERT((ExpressionLeft::dimension == 2 && ExpressionRight::dimension == 2) ||
                          (ExpressionLeft::dimension == 2 && ExpressionRight::dimension == 0) ||
                          (ExpressionLeft::dimension == 0 && ExpressionRight::dimension == 2),
                      "Multiplication at (i) is only valid for zero- or one-dimensional rhs");
        if constexpr (ExpressionLeft::dimension == 2 && ExpressionRight::dimension == 2) {
            // multiplying a matrix-like left hand side with a matrix-like right hand side
            SHAPE_ASSERT(left.cols() == right.rows(), "Multiplying matrix*vector");
            value_type init = value_type(0);
            for (size_type k = 0; k < right.rows(); ++k) {
                init += left.evaluate(i, k) * right.evaluate(k, j);
            }
            return init;
        }
        // either left or right is zero-dimensional
        return left.evaluate(i, j) * right.evaluate(i, j);
    }
};

} // namespace internal
} // namespace la

#endif
