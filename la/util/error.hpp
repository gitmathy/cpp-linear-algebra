/// Part of the project "cpp-linear-algebra"
///
/// @file la/util/error.hpp
/// @brief Definition error class for this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_UTIL_ERROR_HPP
#define LA_UTIL_ERROR_HPP

#include <stdexcept>
#include <string>

namespace la {
namespace util {

/// @brief Error class used in this project
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

} // namespace util
} // namespace la

#endif
