#ifndef LA_TEST_UNIT_TEST_H
#define LA_TEST_UNIT_TEST_H

#include "tests/includes/base_test.hpp"
#include <list>

namespace la
{
namespace test
{

/// @brief A single unit test used as a base class
class unit_test : public base_test
{
protected:
    /// @brief List of all errors during the test
    std::list<std::string> p_errors;

    /// @brief Report an error
    void report_error(const std::string &what);

public:
    /// @brief Construct a unit test
    unit_test(const std::string &name) : base_test(name), p_errors() {}

    /// @brief Destruct a unit test
    virtual ~unit_test() {};

    /// @brief Setup the test
    virtual void setup() {};

    /// @brief Tear down the test
    virtual void tear_down() {};

    /// @brief Get the errors
    const std::list<std::string> &errors() const { return p_errors; }

    /// @brief True if test has been executed and an error was recorded
    inline bool failed() const { return !p_errors.empty(); }
};

} // namespace test
} // namespace la
#endif
