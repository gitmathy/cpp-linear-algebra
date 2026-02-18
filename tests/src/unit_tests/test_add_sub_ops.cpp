#include "tests/includes/unit_tests/test_add_sub_ops.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_add_sub_ops_test::execute()
{
    la::vector<double> a(3, 1.0);
    la::vector<double> b(3, 2.0);

    // use operator+ / - (operants) instead of in-place ops
    la::vector<double> c = a + b;
    if (!check_values(c, 3.0))
        report_error("vector add (via +) produced wrong values");

    la::vector<double> d = b - a;
    if (!check_values(d, 1.0))
        report_error("vector sub (via -) produced wrong values");

    // scalar + vector and vector + scalar
    la::vector<double> s1 = a + 2.0;
    if (!check_values(s1, 3.0))
        report_error("vector add scalar (vector + scalar) produced wrong values");

    la::vector<double> s2 = 2.0 + a;
    if (!check_values(s2, 3.0))
        report_error("vector add scalar (scalar + vector) produced wrong values");

    // adding/subtracting operants with vector
    la::vector<double> op1 = a + (a + b); // vector + operant
    if (!check_values(op1, 4.0))
        report_error("vector add operant (vector + operant) produced wrong values");

    la::vector<double> op2 = (a + b) + a; // operant + vector
    if (!check_values(op2, 4.0))
        report_error("vector add operant (operant + vector) produced wrong values");

    la::vector<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0))
        report_error("vector sub operant (vector - operant) produced wrong values");

    return (int)errors().size();
}

int matrix_add_sub_ops_test::execute()
{
    la::matrix<double> a(2, 2, 1.0);
    la::matrix<double> b(2, 2, 2.0);

    // use operator+ / - (operants)
    la::matrix<double> c = a + b;
    if (!check_values(c, 3.0))
        report_error("matrix add (via +) produced wrong values");

    la::matrix<double> d = b - a;
    if (!check_values(d, 1.0))
        report_error("matrix sub (via -) produced wrong values");

    // scalar + matrix and matrix + scalar
    la::matrix<double> s1 = a + 2.0; // matrix + scalar
    if (!check_values(s1, 3.0))
        report_error("matrix add scalar (matrix + scalar) produced wrong values");

    la::matrix<double> s2 = 2.0 + a; // scalar + matrix
    if (!check_values(s2, 3.0))
        report_error("matrix add scalar (scalar + matrix) produced wrong values");

    // adding/subtracting operants with matrix
    la::matrix<double> op1 = a + (a + b); // matrix + operant
    if (!check_values(op1, 4.0))
        report_error("matrix add operant (matrix + operant) produced wrong values");

    la::matrix<double> op2 = (a + b) + a; // operant + matrix
    if (!check_values(op2, 4.0))
        report_error("matrix add operant (operant + matrix) produced wrong values");

    la::matrix<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0))
        report_error("matrix sub operant (matrix - operant) produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
