/// Part of the project "cpp-linear-algebra"
///
/// @file includes/assert.hpp
/// @brief Definition of macros to perform asserts and throw errors
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ASSERT_H
#define LA_ASSERT_H

#include "includes/log.hpp"
#include "includes/settings.hpp"
#include <stdexcept>
#include <string>

namespace la {

#ifdef _MSC_VER
#define LOG_ERROR(a) ((void)0)
#endif

class error : public std::runtime_error
{
public:
    /// @brief Constructor with only an error message
    /// @param message
    explicit inline error(const std::string &message) : std::runtime_error(message) {}

    /// @brief Constructor with an error code
    /// @param message Message that indicates the error
    /// @param code Error codes
    inline error(const std::string &message, const std::string &code)
        : std::runtime_error(message + " (code: " + code + ")")
    {}

    /// @brief Default destructor
    ~error() = default;
};

/// @brief Implementation of asserts, called by the macros *_ASSERT
/// @tparam AssertionT Type that needs to be evaluated to bool
/// @param assertion This must be true, otherwise a std::invalid_argument error is thrown
/// @param type Error code
/// @param message Contend of the exception
template <typename AssertionT>
inline void __assert(AssertionT assertion, const std::string &message, const std::string &code)
{
    if (!bool(assertion)) {
        LOG_ERROR("Error detected: " << message);
        throw error(message, code);
    }
}

/// @brief Asserting shapes
#if LA_CHECK & LA_CHECK_SHAPE_C
#define SHAPE_ASSERT(a, b) (la::__assert((a), (b), ("shape_check")))
#else
#define SHAPE_ASSERT(a, b) ((void)0)
#endif

/// @brief Asserting boundaries while accessing arrays
#if LA_CHECK & LA_CHECK_BOUNDARY_C
#define BOUNDARY_ASSERT(a, b) (la::__assert((a), (b), ("boundary_check")))
#else
#define BOUNDARY_ASSERT(a, b) ((void)0)
#endif

/// @brief Asserting boundaries while accessing arrays
#if LA_CHECK & LA_CHECK_LAYOUT_C
#define LAYOUT_ASSERT(a, b) (la::__assert((a), (b), ("layout_check")))
#else
#define LAYOUT_ASSERT(a, b) ((void)0)
#endif

} // namespace la
#endif
