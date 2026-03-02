/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_add_sub_ops.cpp
/// @brief Implementation of test of add and substract
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_add_sub_ops.hpp"
#include "la/dense"
#include "la/static"

namespace la {
namespace test {

int vector_add_sub_ops_test::execute()
{
    vector<double> a(3, 1.0);
    vector<double> b(3, 2.0);

    // use operator+ / - (operants) instead of in-place ops
    vector<double> c = a + b;
    if (!check_values(c, 3.0)) {
        report_error("vector add (via +) produced wrong values");
    }

    vector<double> d = b - a;
    if (!check_values(d, 1.0)) {
        report_error("vector sub (via -) produced wrong values");
    }

    // scalar + vector and vector + scalar
    vector<double> s1 = a + 2.0;
    if (!check_values(s1, 3.0)) {
        report_error("vector add scalar (vector + scalar) produced wrong values");
    }

    vector<double> s2 = 2.0 + a;
    if (!check_values(s2, 3.0)) {
        report_error("vector add scalar (scalar + vector) produced wrong values");
    }

    // adding/subtracting operants with vector
    vector<double> op1 = a + (a + b); // vector + operant
    if (!check_values(op1, 4.0)) {
        report_error("vector add operant (vector + operant) produced wrong values");
    }

    vector<double> op2 = (a + b) + a; // operant + vector
    if (!check_values(op2, 4.0)) {
        report_error("vector add operant (operant + vector) produced wrong values");
    }

    vector<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0)) {
        report_error("vector sub operant (vector - operant) produced wrong values");
    }

    return (int)errors().size();
}

int static_vector_add_sub_ops_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b(2);

    // use operator+ / - (operants) instead of in-place ops
    static_vector<int, 3> c = a + b;
    if (!check_values(c, 3)) {
        report_error("static_vector add (via +) produced wrong values");
    }

    static_vector<int, 3> d = b - a;
    if (!check_values(d, 1)) {
        report_error("static_vector sub (via -) produced wrong values");
    }

    // scalar + vector and vector + scalar
    static_vector<int, 3> s1 = a + 2;
    if (!check_values(s1, 3)) {
        report_error("static_vector add scalar (vector + scalar) produced wrong values");
    }

    static_vector<int, 3> s2 = 2 + a;
    if (!check_values(s2, 3)) {
        report_error("static_vector add scalar (scalar + vector) produced wrong values");
    }

    // adding/subtracting operants with vector
    static_vector<int, 3> op1 = a + (a + b); // vector + operant
    if (!check_values(op1, 4)) {
        report_error("static_vector add operant (vector + operant) produced wrong values");
    }

    static_vector<int, 3> op2 = (a + b) + a; // operant + vector
    if (!check_values(op2, 4)) {
        report_error("static_vector add operant (operant + vector) produced wrong values");
    }

    static_vector<int, 3> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0)) {
        report_error("static_vector sub operant (vector - operant) produced wrong values");
    }

    return (int)errors().size();
}

int matrix_add_sub_ops_test::execute()
{
    matrix<double> a(2, 2, 1.0);
    matrix<double> b(2, 2, 2.0);

    // use operator+ / - (operants)
    matrix<double> c = a + b;
    if (!check_values(c, 3.0)) {
        report_error("matrix add (via +) produced wrong values");
    }

    matrix<double> d = b - a;
    if (!check_values(d, 1.0)) {
        report_error("matrix sub (via -) produced wrong values");
    }

    // scalar + matrix and matrix + scalar
    matrix<double> s1 = a + 2.0; // matrix + scalar
    if (!check_values(s1, 3.0)) {
        report_error("matrix add scalar (matrix + scalar) produced wrong values");
    }

    matrix<double> s2 = 2.0 + a; // scalar + matrix
    if (!check_values(s2, 3.0)) {
        report_error("matrix add scalar (scalar + matrix) produced wrong values");
    }

    // adding/subtracting operants with matrix
    matrix<double> op1 = a + (a + b); // matrix + operant
    if (!check_values(op1, 4.0)) {
        report_error("matrix add operant (matrix + operant) produced wrong values");
    }

    matrix<double> op2 = (a + b) + a; // operant + matrix
    if (!check_values(op2, 4.0)) {
        report_error("matrix add operant (operant + matrix) produced wrong values");
    }

    matrix<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0)) {
        report_error("matrix sub operant (matrix - operant) produced wrong values");
    }

    matrix<int, ROW_WISE> A(2, 3, 1);
    matrix<int, COLUMN_WISE> B(2, 3, 2);
    matrix<int, ROW_WISE> C = A + B;
    if (!check_values(C, 3)) {
        report_error("matrix add different storage produced wrong value");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
