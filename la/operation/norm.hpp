/// Part of the project "cpp-linear-algebra"
///
/// @file la/operation/norm.hpp
/// @brief Definition of norm computations in this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_OPERATIONS_NORM_HPP
#define LA_OPERATIONS_NORM_HPP

#include "la/util/constants.hpp"
#include "la/util/types.hpp"
#include <cmath>
#include <numeric>

namespace la {

/// @brief p-norm of a vector or matrix.
/// @return ||x||_p
template <size_type p = 2, typename ExpressionT>
typename ExpressionT::value_type norm(const ExpressionT &x);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// Some performance improvements for different common norms such as 1-, 2-, and max-norm.
template <size_type p = 2, typename ExpressionT>
typename ExpressionT::value_type norm(const ExpressionT &x)
{
    static_assert(la::util::has_evaluate<ExpressionT>, "ExpressionT must provide evaluate");
    static_assert(la::util::has_non_zeros<ExpressionT>, "ExpressionT must provide evaluate");
    typedef typename ExpressionT::value_type T;

    T result = T(0);
    auto indices = std::views::iota(size_type(0), x.non_zeros());
    if constexpr (p == 1) {
        result = std::transform_reduce(
#ifdef PARALLEL
            execution::par_unseq,
#endif
            indices.begin(), indices.end(), T(0), std::plus<T>(),
            [&x](const size_type i) { return std::abs(x.evaluate(i)); });
        return result;
    }
    if constexpr (p == 2) {
        result = std::transform_reduce(
#ifdef PARALLEL
            execution::par_unseq,
#endif
            indices.begin(), indices.end(), T(0), std::plus<T>(),
            [&x](const size_type i) { return std::abs(x.evaluate(i) * x.evaluate(i)); });
        return std::sqrt(result);
    }
    if constexpr (p == SIZE_TYPE_MAX) {
        const size_type max_index = *std::max_element(
#if PARALLEL
            execution::par_unseq,
#endif
            indices.begin(), indices.end(), [&](const size_type i, const size_type j) {
                return std::abs(x.evaluate(i)) < std::abs(x.evaluate(j));
            });
        return std::abs(x.evaluate(max_index));
    }
    result = std::transform_reduce(
#ifdef PARALLEL
        execution::par_unseq,
#endif
        indices.begin(), indices.end(), T(0), std::plus<T>(),
        [&x](const size_type i) { return std::pow(std::abs(x.evaluate(i)), p); });
    return std::pow(result, 1. / p);
}

} // namespace la

#endif
