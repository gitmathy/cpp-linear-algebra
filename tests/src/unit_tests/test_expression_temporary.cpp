#include "tests/includes/unit_tests/test_expression_temporary.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_expression_temporary_test::execute()
{
    la::vector<double> a(3, 1.0);
    la::vector<double> b(3, 2.0);

    // mimic expression chaining using += (keeps the test slim)
    la::vector<double> r = a;
    r += b;
    r += a;
    if (!check_values(r, 4.0))
        report_error("vector expression produced wrong values");

    return (int)errors().size();
}

int matrix_expression_temporary_test::execute()
{
    la::matrix<double> A(2, 2, 1.0);
    la::matrix<double> B(2, 2, 2.0);

    // mimic expression chaining with matrices
    la::matrix<double> R = A;
    R += B;
    R += A;
    if (!check_values(R, 4.0))
        report_error("matrix expression produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
