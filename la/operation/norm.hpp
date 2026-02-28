/// Part of the project "cpp-linear-algebra"
///
/// @file includes/settings.hpp
/// @brief Definition of settings controlling the project
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
template <size_type p = 2, typename la_type>
typename la_type::value_type norm(const la_type &x);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// Some performance improvements for different common norms such as 1-, 2-, and max-norm.
template <size_type p, typename la_type>
typename la_type::value_type norm(const la_type &x)
{
    typedef typename la_type::value_type T;
    T result = T(0);
    if constexpr (p == 1) {
#ifdef PARALLEL
        result = std::transform_reduce(execution::par_unseq, // Parallel and unsequenced execution
                                       x.begin(), x.end(), T(0), std::plus<T>(),
                                       [](const T val) { return std::abs(val); });
#else
        result = std::accumulate(x.begin(), x.end(), T(0),
                                 [](const T sum, const T val) { return sum + std::abs(val); });
#endif
        return result;
    }
    if constexpr (p == 2) {
#ifdef PARALLEL
        result =
            std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                  x.begin(), x.end(), T(0), std::plus<T>(),
                                  [](const T val) { return std::abs(val * val); });
#else
        result = std::accumulate(x.begin(), x.end(), T(0), [](const T sum, const T val) {
            return sum + std::abs(val * val);
        });
#endif
        return std::sqrt(result);
    }
    if constexpr (p == SIZE_TYPE_MAX) {
        result = std::abs(*std::max_element(
#if PARALLEL
            std::execution::par_unseq,
#endif
            x.begin(), x.end(), [](T a, T b) { return std::abs(a) < std::abs(b); }));
        return result;
    }
#ifdef PARALLEL
    result = std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                   x.begin(), x.end(), T(0), std::plus<T>(),
                                   [](const T val) { return std::pow(std::abs(val), p); });
#else
    result = std::accumulate(x.begin(), x.end(), T(0), [](const T sum, const T val) {
        return sum + std::pow(std::abs(val), p);
    });
#endif
    return std::pow(result, 1. / p);
}

} // namespace la

#endif
