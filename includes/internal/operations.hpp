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
/// A D D I T I O N
/// ===============================================

/// @brief Add operation
/// @tparam ExpressionLeft type of first summand
/// @tparam ExpressionRight type of second summand
template <typename ExpressionLeft, typename ExpressionRight>
class add_operation
{
public:
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

public:
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
class sub_operation
{
public:
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename ExpressionLeft::value_type value_type;

public:
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
/// M A T R I X   V E C T O R   M U L T I P L I C A T I O N
/// =======================================================

/// @brief Multiplying a matrix with a vector
/// @tparam MatType Matrix type
/// @tparam VecType Vector type
template <typename MatType, typename VecType>
class mat_vec_multiplication
{
public:
    /// @brief We silently assume that the value type for both expressions is the same
    typedef typename MatType::value_type value_type;

    /// @brief Multiply at row i: (i'th row of matrix with the vector)
    /// We are parallelizing at outer loop to evaluate the expression yielding from this operation
    static inline value_type evaluate(const MatType &x, const VecType &y, const la::size_type i)
    {
        SHAPE_ASSERT(x.cols() == y.rows(), "Multiplying matrix*vector");
        value_type init = value_type(0);
        for (size_type j = 0; j < y.rows(); ++j) {
            init += x.evaluate(i, j) * y.evaluate(j);
        }
        return init;
    }

    /// @brief Multiply at element (i,j)
    static inline value_type evaluate(const MatType &x, const VecType &y, const la::size_type i,
                                      const la::size_type j)
    {
        throw error("No matrix-vector multiplication at an element (i,j)");
    }
};
} // namespace internal
} // namespace la

#endif
