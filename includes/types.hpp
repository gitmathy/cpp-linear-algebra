/// Part of the project "cpp-linear-algebra"
///
/// @file includes/types.hpp
/// @brief Definition of types used in this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TYPES_H
#define LA_TYPES_H

#include <cstddef>

namespace la {

/// @brief Type used to index vectors and matrices
typedef std::size_t size_type;

/// @brief Storing matrix row- or column-wise
enum storage_type { ROW_WISE, COLUMN_WISE };

} // namespace la
#endif
