#include "includes/unit_test.hpp"

namespace la_test
{

unit_test::unit_test(const std::string &name) : p_name(name), p_errors(), p_logger(logger::get()) {}

const std::list<std::string> &unit_test::errors() const { return p_errors; }

void unit_test::setup() {}

void unit_test::tear_down() {}

} // namespace la_test
