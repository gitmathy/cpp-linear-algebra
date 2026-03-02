/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_mult_div_assignment.cpp
/// @brief Implementation of test of multiplication assignment computations
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_mult_div_assignment.hpp"
#include "la/dense"
#include "la/static"

namespace la {
namespace test {

int vector_mult_div_assignment_test::execute()
{

    vector<int> x = {2, 3};
    vector<int> y = {3, 2};
    y *= x;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying vector");
    }
    if (!check_values(y, 6)) {
        report_error("Wrong element for multiplying vectors");
    }

    y *= 2;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying vector with scalar");
    }
    if (!check_values(y, 12)) {
        report_error("Wrong element for multiplying vector with a scalar");
    }

    x *= (y * 2);
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying vector with operant");
    }
    if (!(x(0) == 48 && x(1) == 72)) {
        report_error("Wrong element for multiplying vector with a operant");
    }

    return (int)errors().size();
}

int static_vector_mult_div_assignment_test::execute()
{

    static_vector<int, 2> x = {2, 3};
    static_vector<int, 2> y = {3, 2};
    y *= x;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector");
    }
    if (!check_values(y, 6)) {
        report_error("Wrong element for multiplying static_vectors");
    }

    y *= 2;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector with scalar");
    }
    if (!check_values(y, 12)) {
        report_error("Wrong element for multiplying static_vector with a scalar");
    }

    x *= (y * 2);
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector with operant");
    }
    if (!(x(0) == 48 && x(1) == 72)) {
        report_error("Wrong element for multiplying static_vector with a operant");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
