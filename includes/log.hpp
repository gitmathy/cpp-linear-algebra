#ifndef LA_LOG_H
#define LA_LOG_H

#include "includes/settings.hpp"
#include <iostream>

namespace la
{

// Logging errors
#if LA_DEBUG_LEVEL >= LA_DEBUG_ERROR_C
#define LOG_ERROR(a)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        LA_LOG_STREAM << "LA ERROR: " << a << std::endl;                                                               \
    } while (false)
#else
#define LOG_ERROR(a) ((void)0)
#endif

// Logging warnings
#if LA_DEBUG_LEVEL >= LA_DEBUG_WARNING_C
#define LOG_WARNING(a)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        LA_LOG_STREAM << "LA WARNING: " << a << std::endl;                                                             \
    } while (false)
#else
#define LOG_WARNING(a) ((void)0)
#endif

// Logging infos
#if LA_DEBUG_LEVEL >= LA_DEBUG_INFO_C
#define LOG_INFO(a)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        LA_LOG_STREAM << "LA INFO: " << a << std::endl;                                                                \
    } while (false)
#else
#define LOG_INFO(a) ((void)0)
#endif

// Logging debug information
#if LA_DEBUG_LEVEL >= LA_DEBUG_DEBUG_C
#define LOG_DEBUG(a)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        LA_LOG_STREAM << "LA DEBUG: " << a << std::endl;                                                               \
    } while (false)
#else
#define LOG_DEBUG(a) ((void)0)
#endif

// Logging trace information
#if LA_DEBUG_LEVEL >= LA_DEBUG_TRACE_C
#define LOG_TRACE(a)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        LA_LOG_STREAM << "LA TRACE: " << a << std::endl;                                                               \
    } while (false)
#else
#define LOG_TRACE(a) ((void)0)
#endif

} // namespace la
#endif
