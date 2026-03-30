/// Part of the project "cpp-linear-algebra"
///
/// @file la/operation/inner_product.hpp
/// @brief Definition of inner product in this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_OPERATIONS_INNER_PRODUCT_HPP
#define LA_OPERATIONS_INNER_PRODUCT_HPP

#include "la/data_structure/forward.hpp"
#include "la/data_structure/util/concepts.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <numeric>

namespace la {

template <typename LeftT, typename RightT>
typename LeftT::value_type inner_product(const LeftT &left, const RightT &right);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename LeftT, typename RightT>
typename LeftT::value_type inner_product(const LeftT &left, const RightT &right)
{
    static_assert(la::util::has_evaluate<LeftT>, "LeftT must provide evaluate");
    static_assert(la::util::has_evaluate<RightT>, "RightT must provide evaluate");
    static_assert(la::util::same_value_type<LeftT, RightT>,
                  "Left and RightT must have same value type");
    SHAPE_ASSERT(left.rows() == right.rows(), "Inner product only defined on same length");
    typedef typename LeftT::value_type T;
    auto indices = std::views::iota(size_type(0), left.rows());
    return std::transform_reduce(
#ifdef PARALLEL
        std::execution::par,
#endif
        indices.begin(), indices.end(), T(0), std::plus<>(),
        [&left, &right](const size_t i) { return left.evaluate(i) * right.evaluate(i); });
}

} // namespace la
#endif
