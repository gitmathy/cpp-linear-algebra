#ifndef LA_ASSERT_H
#define LA_ASSERT_H

#include "includes/log.hpp"
#include "includes/settings.hpp"
#include <stdexcept>
#include <string>

namespace la
{

class error : public std::runtime_error
{
public:
    /// @brief Constructor with only an error message
    /// @param message
    explicit error(const std::string &message) : std::runtime_error(message) {}

    /// @brief Constructor with an error code
    /// @param message Message that indicates the error
    /// @param code if this error was raised by shape or boundary check
    error(const std::string &message, int code) : std::runtime_error(message + "(code " + std::to_string(code) + ")") {}

    /// @brief Default destructor
    ~error() = default;
};

/// @brief Implementation of asserts, called by the macros *_ASSERT
/// @tparam AssertionT Type that needs to be evaluated to bool
/// @param assertion This must be true, otherwise a std::invalid_argument error is thrown
/// @param message Contend of the exception
template <typename AssertionT> inline void __assert(AssertionT assertion, const std::string &message, const int type)
{
    if (!bool(assertion))
    {
        LOG_ERROR("Error detected: " << message);
        throw error(message, type);
    }
}

/// @brief Asserting shapes
#if LA_CHECK | LA_CHECK_SHAPE_C
#define SHAPE_ASSERT(a, b) (la::__assert((a), (b), (LA_CHECK_SHAPE_C)))
#else
#define SHAPE_ASSERT(a, b) ((void)0)
#endif

/// @brief Asserting boundaries while accessing arrays
#if LA_CHECK | LA_CHECK_BOUNDARY_C
#define BOUNDARY_ASSERT(a, b) (la::__assert((a), (b), (LA_CHECK_BOUNDARY_C)))
#else
#define BOUNDARY_ASSERT(a, b) ((void)0)
#endif

} // namespace la
#endif
