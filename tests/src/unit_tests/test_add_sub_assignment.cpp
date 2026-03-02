/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_add_sub_assignment.cpp
/// @brief Implementation of test of add and substract assignment
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_add_sub_assignment.hpp"
#include "la/dense"
#include "la/static"
#include "la/util/constants.hpp"

namespace la {
namespace test {

int vector_add_sub_assignment_test::execute()
{
    vector<double> a(3, 1.0);
    vector<double> b(3, 2.0);

    a += b;
    if (std::abs(a(0) - 3.0) > util::EPS || std::abs(a(1) - 3.0) > util::EPS ||
        std::abs(a(2) - 3.0) > util::EPS)
        report_error("vector += vector produced wrong values");

    a -= b;
    if (!check_values(a, 1.0))
        report_error("vector -= vector produced wrong values");

    return (int)errors().size();
}

int static_vector_add_sub_assignment_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b(2);

    a += b;
    if (!check_values(a, 3))
        report_error("static_vector += static_vector produced wrong values");

    a -= b;
    if (!check_values(a, 1))
        report_error("static_vector -= static_vector produced wrong values");

    return (int)errors().size();
}

int matrix_add_sub_assignment_test::execute()
{
    matrix<double> a(2, 2, 1.0);
    matrix<double> b(2, 2, 2.0);

    a += b;
    if (!check_values(a, 3.0))
        report_error("matrix += matrix produced wrong values");

    a -= b;
    if (!check_values(a, 1.0))
        report_error("matrix -= matrix produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
