/// Part of the project "cpp-linear-algebra"
///
/// @file la/util/constants.hpp
/// @brief Definition of constants used in this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_UTIL_CONSTANTS_HPP
#define LA_UTIL_CONSTANTS_HPP

#include "la/util/types.hpp"
#include <limits>

namespace la {

/// @brief Used for undefined size_types
inline constexpr size_type SIZE_TYPE_MAX = std::numeric_limits<size_type>::max();

// constants only used internally
namespace util {

/// @brief Block size used in this project
inline constexpr size_type BLOCK_SIZE = size_type(64);

/// @brief eps for comparision of a double is close to zero
inline constexpr double EPS = 1e-12;

} // namespace util

} // namespace la

#endif
