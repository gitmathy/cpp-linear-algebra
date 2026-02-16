#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

void unit_test::report_error(const std::string &what)
{
    p_errors.push_back(what);
    log(what, ERROR);
}

} // namespace test
} // namespace la
