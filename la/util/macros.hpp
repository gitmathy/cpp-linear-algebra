/// Part of the project "cpp-linear-algebra"
///
/// @file la/util/macros.hpp
/// @brief Definition of macros the project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_UTIL_MACROS_HPP
#define LA_UTIL_MACROS_HPP

#include "la/util/error.hpp"
#include <iostream>

namespace la {

/// @brief Check shapes
#define LA_CHECK_SHAPE_C 1

/// @brief Check boundaries. This has a big impact on performance
#define LA_CHECK_BOUNDARY_C 2

/// @brief Layout check, i.e., matrix row-wise or column-wise
#define LA_CHECK_LAYOUT_C 4

/// @brief Check everything
// #define LA_CHECK ~0

/// @brief Check nothing
#define LA_CHECK 0

/// @brief No logs are written
#define LA_DEBUG_SILENT_C 0
/// @brief Write logs of severity error
#define LA_DEBUG_ERROR_C 2
/// @brief Write logs of severity warning
#define LA_DEBUG_WARNING_C 4
/// @brief Write logs of severity info
#define LA_DEBUG_INFO_C 6
/// @brief Write logs of severity debug
#define LA_DEBUG_DEBUG_C 8
/// @brief Write logs of severity trace
#define LA_DEBUG_TRACE_C 10

/// @brief Log everything
// #define LA_DEBUG_LEVEL 10

// /// @brief Log nothing
#define LA_DEBUG_LEVEL 2

/// @brief Where to write errors and logs
#define LA_LOG_STREAM std::cout

// Logging errors
#if LA_DEBUG_LEVEL >= LA_DEBUG_ERROR_C
#define LOG_ERROR(a)                                                                               \
    do {                                                                                           \
        LA_LOG_STREAM << "LA ERROR: " << a << std::endl;                                           \
    } while (false)
#else
#define LOG_ERROR(a) ((void)0)
#endif

// Logging warnings
#if LA_DEBUG_LEVEL >= LA_DEBUG_WARNING_C
#define LOG_WARNING(a)                                                                             \
    do {                                                                                           \
        LA_LOG_STREAM << "LA WARNING: " << a << std::endl;                                         \
    } while (false)
#else
#define LOG_WARNING(a) ((void)0)
#endif

// Logging infos
#if LA_DEBUG_LEVEL >= LA_DEBUG_INFO_C
#define LOG_INFO(a)                                                                                \
    do {                                                                                           \
        LA_LOG_STREAM << "LA INFO: " << a << std::endl;                                            \
    } while (false)
#else
#define LOG_INFO(a) ((void)0)
#endif

// Logging debug information
#if LA_DEBUG_LEVEL >= LA_DEBUG_DEBUG_C
#define LOG_DEBUG(a)                                                                               \
    do {                                                                                           \
        LA_LOG_STREAM << "LA DEBUG: " << a << std::endl;                                           \
    } while (false)
#else
#define LOG_DEBUG(a) ((void)0)
#endif

// Logging trace information
#if LA_DEBUG_LEVEL >= LA_DEBUG_TRACE_C
#define LOG_TRACE(a)                                                                               \
    do {                                                                                           \
        LA_LOG_STREAM << "LA TRACE: " << a << std::endl;                                           \
    } while (false)
#else
#define LOG_TRACE(a) ((void)0)
#endif

namespace util {

/// @brief Implementation of asserts, called by the macros *_ASSERT
/// @tparam AssertionT Type that needs to be evaluated to bool
/// @param assertion This must be true, otherwise a std::invalid_argument error is thrown
/// @param type Error code
/// @param message Contend of the exception
template <typename AssertionT>
inline void assert__(AssertionT assertion, const std::string &message, const std::string &code)
{
    if (!bool(assertion)) {
        LOG_ERROR("Error detected: " << message);
        throw error(message, code);
    }
}

} // namespace util

/// @brief Asserting shapes
#if LA_CHECK & LA_CHECK_SHAPE_C
#define SHAPE_ASSERT(a, b) (la::util::assert__((a), (b), ("shape_check")))
#else
#define SHAPE_ASSERT(a, b) ((void)0)
#endif

/// @brief Asserting boundaries while accessing arrays
#if LA_CHECK & LA_CHECK_BOUNDARY_C
#define BOUNDARY_ASSERT(a, b) (la::util::assert__((a), (b), ("boundary_check")))
#else
#define BOUNDARY_ASSERT(a, b) ((void)0)
#endif

/// @brief Asserting boundaries while accessing arrays
#if LA_CHECK & LA_CHECK_LAYOUT_C
#define LAYOUT_ASSERT(a, b) (la::util::assert__((a), (b), ("layout_check")))
#else
#define LAYOUT_ASSERT(a, b) ((void)0)
#endif

} // namespace la
#endif
