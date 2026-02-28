/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_test.cpp
/// @brief Implementation of unit test class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

void unit_test::report_error(const std::string &what)
{
    p_errors.push_back(what);
    log(what, ERROR);
}

} // namespace test
} // namespace la
