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
#include "la/util/macros.hpp"
#include <numeric>

namespace la {

/// @brief Inner product of a vector
/// @return left^T * right
template <typename T>
T inner_product(const vector<T> &left, const vector<T> &right);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
T inner_product(const vector<T> &left, const vector<T> &right)
{
    SHAPE_ASSERT(left.rows() == right.rows(), "vectors for inner product not of same length");
    return std::inner_product(left.begin(), left.end(), right.begin(), T(0));
}

} // namespace la
#endif
