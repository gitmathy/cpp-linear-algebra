/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/forward.hpp
/// @brief Forward declarations of basic data structure
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_FORWARD_HPP
#define LA_DATA_STRUCTURE_FORWARD_HPP

#include "la/util/types.hpp"

namespace la {

// Forward declaration of dense matrix
// see la/data_structure/matrix.hpp
template <typename T>
class matrix;

// Forward declaration of sparse matrix
// see la/data_structure/sparse_matrix.hpp
template <typename T>
class sparse_matrix;

// Forward declaration of sparse matrix builder
// see la/data_structure/sparse_matrix_builder.hpp
template <typename T>
class sparse_matrix_builder;

// Forward declaration of vector
// see la/data_structure/vector.hpp
template <typename T>
class vector;

// Forward declaration of static_vector
// see la/data_structure/static_vector.hpp
template <typename T, size_type N>
class static_vector;

} // namespace la
#endif
