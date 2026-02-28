#ifndef LA_TEST_UNIT_TEST_H
#define LA_TEST_UNIT_TEST_H

#include "la/util/constants.hpp"
#include "tests/includes/base_test.hpp"
#include <list>

namespace la {
namespace test {

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
    unit_test(const std::string &name, const std::string &description)
        : base_test(name, description), p_errors()
    {}

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

// ===============================================
// H E L P E R   F U N C T I O N S
// ===============================================

/// @brief Check if all values in a vector or matrix have the same given value
template <typename la_struct>
inline bool check_values(const la_struct &x, const typename la_struct::value_type &value)
{
    for (auto it = x.begin(); it != x.end(); ++it) {
        if ((*it - value) > util::EPS) {
            return false;
        }
    }
    return true;
}

} // namespace test
} // namespace la
#endif
