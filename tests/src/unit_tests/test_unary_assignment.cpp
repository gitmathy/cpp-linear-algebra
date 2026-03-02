/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_unary_assignment.cpp
/// @brief Implementation of test for unary assignments
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_unary_assignment.hpp"
#include "la/dense"
#include "la/static"

namespace la {
namespace test {

int vector_unary_assignment_test::execute()
{
    vector<int> a(3, 1);
    vector<int> b = -a;

    if (!check_values(b, -1)) {
        report_error("vector = -vector produced wrong values");
    }

    return (int)errors().size();
}

int static_vector_unary_assignment_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b = -a;

    if (!check_values(b, -1)) {
        report_error("static_vector = -static_vector produced wrong values");
    }

    return (int)errors().size();
}

int matrix_unary_assignment_test::execute()
{
    matrix<int> a(2, 2, 1);
    matrix<int> b = -a;

    if (!check_values(b, -1)) {
        report_error("matrix = -matrix produced wrong values");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
