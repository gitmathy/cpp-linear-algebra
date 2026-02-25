/// Part of the project "cpp-linear-algebra"
///
/// @file includes/internal/memory.hpp
/// @brief Memory handling
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_INTERNAL_MEMORY_H
#define LA_INTERNAL_MEMORY_H

#include "includes/assert.hpp"
#include "includes/types.hpp"
#include <algorithm>
#include <cstdlib>
#include <new>
#include <type_traits>
#ifdef _MSC_VER
#include <malloc.h>
#endif

namespace la {
namespace internal {

/// @brief Allocate memory aligned to the memory
/// @tparam T Value type
/// @param n Size of values
/// @return Pointer to aligned array
template <typename T>
T *allocate_aligned(size_type n)
{
    static_assert(std::is_trivial<T>::value, "allocate_aligned only for trivial types");

    const std::size_t alignment = std::max(std::size_t(64), alignof(T));
    std::size_t size = n * sizeof(T);
    // if size is not a multiple of the alignment, adjust it's value (needed for aligned alloc)
    if (size % alignment != 0) {
        size = ((size + alignment - 1) / alignment) * alignment;
    }

    // Allocate the memory
    void *ptr = nullptr;
#ifdef _MSC_VER
    ptr = _aligned_malloc(size, alignment);
#else
    ptr = std::aligned_alloc(alignment, size);
#endif
    return static_cast<T *>(ptr);
}

/// @brief Deallocate memory which has been allocated with allocate_aligned
/// @tparam T value type
/// @param ptr Pointer to memory which needs to be freed
template <typename T>
void deallocate_aligned(T *ptr)
{
    if (ptr == nullptr) {
        return;
    }
    static_assert(std::is_trivial<T>::value, "deallocate_aligned only for trivial types");
#ifdef _MSC_VER
    _aligned_free(ptr);
#else
    std::free(ptr);
#endif
}

} // namespace internal
} // namespace la

#endif
