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

#include <iostream>
#include <stdexcept>
#include <string>

namespace la {
namespace util {

enum ErrorCode { SHAPE, BOUNDARY, LAYOUT, NON_ZERO, FILE_ERROR, UNKNOWN };

inline std::string error_to_str(const ErrorCode code)
{
    switch (code) {
        case SHAPE:
            return "shape";
        case BOUNDARY:
            return "boundary";
        case LAYOUT:
            return "layout";
        case NON_ZERO:
            return "non-zero";
        case FILE_ERROR:
            return "file-error";
        case UNKNOWN:
            return "unkown";
    }
    return "unkown-error";
}

/// @brief Error class used in this project
class error : public std::runtime_error
{
private:
    /// @brief error message
    std::string p_error_message;

public:
    /// @brief Constructor with only an error message
    /// @param message
    explicit inline error(const std::string &message, const std::string &function,
                          const ErrorCode code);

    /// @brief Default destructor
    virtual ~error() = default;

    // Overriding the virtual what() function
    inline const char *what() const noexcept override { return p_error_message.c_str(); }
};

/// @brief Error class for shape error
class shape_error : public error
{

public:
    /// @brief Construct with error message and function name
    explicit inline shape_error(const std::string &message, const std::string &function);

    /// @brief Default destructor
    ~shape_error() = default;
};

/// @brief Error class for boundary error
class boundary_error : public error
{

public:
    /// @brief Construct with error message and function name
    explicit inline boundary_error(const std::string &message, const std::string &function);

    /// @brief Default destructor
    ~boundary_error() = default;
};

/// @brief Error class for layout error
class layout_error : public error
{

public:
    /// @brief Construct with error message and function name
    explicit inline layout_error(const std::string &message, const std::string &function);

    /// @brief Default destructor
    ~layout_error() = default;
};

/// @brief Error class for non zero errors
class non_zero_error : public error
{

public:
    /// @brief Construct with error message and function name
    explicit inline non_zero_error(const std::string &message, const std::string &function);

    /// @brief Default destructor
    ~non_zero_error() = default;
};

/// @brief Error class for non zero errors
class file_error : public error
{

public:
    /// @brief Construct with error message and function name
    explicit inline file_error(const std::string &message, const std::string &function);

    /// @brief Default destructor
    ~file_error() = default;
};

// ===============================================
// I N L I N E   I M P L E M E N T A T I O N S
// ===============================================

inline error::error(const std::string &message, const std::string &function, const ErrorCode code)
    : std::runtime_error(message)
{
    p_error_message = std::string(std::string("Code '") + error_to_str(code) + "' - in " +
                                  function + " - msg: " + std::runtime_error::what());
}

inline shape_error::shape_error(const std::string &message, const std::string &function)
    : error(message, function, SHAPE)
{}

inline boundary_error::boundary_error(const std::string &message, const std::string &function)
    : error(message, function, BOUNDARY)
{}

inline layout_error::layout_error(const std::string &message, const std::string &function)
    : error(message, function, LAYOUT)
{}

inline non_zero_error::non_zero_error(const std::string &message, const std::string &function)
    : error(message, function, NON_ZERO)
{}

inline file_error::file_error(const std::string &message, const std::string &function)
    : error(message, function, FILE_ERROR)
{}

/// @brief Create a error class based on the error code
/// @param code Code of the error
/// @param message What has happened?
/// @param function Name of function
[[noreturn]] inline void error_factory(const std::string &message, const std::string &function,
                                       const ErrorCode code)
{
    switch (code) {
        case SHAPE:
            throw shape_error(message, function);
        case BOUNDARY:
            throw boundary_error(message, function);
        case LAYOUT:
            throw layout_error(message, function);
        case NON_ZERO:
            throw non_zero_error(message, function);
        case FILE_ERROR:
            throw file_error(message, function);
        case UNKNOWN:
            throw error(message, function, code);
    }
    throw error(message, function, UNKNOWN);
}

} // namespace util
} // namespace la

#endif
