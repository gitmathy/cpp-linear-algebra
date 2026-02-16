#ifndef LA_TEST_BASE_TEST_H
#define LA_TEST_BASE_TEST_H

#include "tests/includes/log.hpp"
#include <list>

namespace la
{
namespace test
{

/// @brief A single test used as a base class for unit tests and performance tests
class base_test
{
protected:
    /// @brief Name of the test
    std::string p_name;

    /// @brief A reference to the logger
    logger &p_logger;

    /// @brief Wrapping calls to the logger
    void log(const std::string &what, const TestLogLevel &level) { p_logger.log(what, level); }

    /// @brief Wrapping calls to the logger
    void log(std::stringstream &what, const TestLogLevel &level) { p_logger.log(what, level); }

public:
    /// @brief Setup a test with a given name
    base_test(const std::string &name) : p_name(name), p_logger(logger::get()) {}

    /// @brief Destruct a unit test
    virtual ~base_test() = default;

    /// @brief Get the name of the test
    inline const std::string &name() const { return p_name; }

    /// @brief Setup the test
    virtual void setup() = 0;

    /// @brief Execute the test
    /// @return A number for the result of the test
    virtual int execute() = 0;

    /// @brief Tear down the test
    virtual void tear_down() = 0;
};

} // namespace test
} // namespace la

#endif
