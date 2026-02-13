#ifndef TEST_LA_UNIT_TEST_H
#define TEST_LA_UNIT_TEST_H

#include "includes/test_log.hpp"
#include <list>

namespace la_test
{

/// @brief A single unit test used as a base class
class unit_test
{
protected:
    /// @brief Name of the test
    std::string p_name;
    std::list<std::string> p_errors;
    logger &p_logger;

public:
    /// @brief Construct a unit test
    /// @param name Name of the test
    /// @param log_level log level
    unit_test(const std::string &name);
    /// @brief Destruct a unit test
    virtual ~unit_test() = default;

    inline const std::string &name() const { return p_name; }

    /// @brief Setup the test
    virtual void setup();
    /// @brief Execute the test
    /// @return True if the test is fine
    virtual bool execute() = 0;
    /// @brief Tear down the test
    virtual void tear_down();

    const std::list<std::string> &errors() const;
};

} // namespace la_test

#endif
