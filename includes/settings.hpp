#ifndef LA_SETTINGS_H
#define LA_SETTINGS_H

namespace la
{

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
#define LA_DEBUG_LEVEL 0

/// @brief Where to write errors and logs
#define LA_LOG_STREAM std::cout

} // namespace la
#endif
