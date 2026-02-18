#ifndef LA_TEST_LOG_H
#define LA_TEST_LOG_H

#include <sstream>
#include <string>

namespace la {
namespace test {

/// @brief Log level of test execution
enum TestLogLevel {
    ERROR = 0,
    WARNING = 1,
    INFO = 2,
    DEBUG = 3,
};

const TestLogLevel DEFAULT_LOG_LEVEL = DEBUG;

/// @brief Logger as singleton pattern
class logger
{
private:
    /// @brief Implementing singleton pattern
    static logger *p_instance;

    /// @brief Level of logging
    TestLogLevel p_level;

    /// @brief Construct a logger
    /// @param log_level
    logger();

public:
    /// @brief Default destructor
    ~logger() = default;

    /// @brief Get the logger, as singleton pattern
    /// @return
    static logger &get();

    /// @brief Set the log level
    /// @param level the level of logging
    void set_level(const TestLogLevel &level);

    /// @brief Log a message
    /// @param what What to log
    /// @param level Level of the log
    void log(const std::string &what, const TestLogLevel &level);

    /// @brief Log a message
    /// @param what What to log and cleared afterwards
    /// @param level Level of the log
    void log(std::stringstream &what, const TestLogLevel &level);
};

} // namespace test
} // namespace la
#endif
