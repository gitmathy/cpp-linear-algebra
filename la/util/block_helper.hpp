/// Part of the project "cpp-linear-algebra"
///
/// @file la/util/block_helper.hpp
/// @brief Definition and helper for block based algorithms
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_UTIL_BLOCK_HELPER_HPP
#define LA_UTIL_BLOCK_HELPER_HPP

#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <numeric>
#include <vector>

namespace la {
namespace util {

/// @brief Generates a vector of starting indices for blocks of a given size.
/// @param start First index of a block
/// @param end maximal index
/// @param block_size size of the block
/// @return Vector containing the first index of every block
inline std::vector<size_type> create_block_indices(size_type start, size_type end,
                                                   size_type block_size)
{
    std::vector<size_type> indices;
    LAYOUT_ASSERT(start < end, "block must consist of more than one element");
    indices.reserve((end - start) / block_size + 1);
    for (size_type i = start; i < end; i += block_size) {
        indices.push_back(i);
    }
    return indices;
}

/// @brief Create an index array from [start, end)
/// @param start First index
/// @param end Last index
/// @return vector containing the indices
inline std::vector<size_type> create_range_indices(const size_type start, const size_type end)
{
    if (start >= end)
        return {};
    std::vector<size_type> indices(end - start);
    // Fill with 0, 1, 2... and then offset by start
    std::iota(indices.begin(), indices.end(), start);
    return indices;
}

} // namespace util
} // namespace la
#endif
