#include "tests/includes/unit_tests/test_apply_func.hpp"
#include "la/dense"

namespace la {
namespace test {

int vector_apply_func_test::execute()
{
    la::vector<double> v(5, 2.0);
    v.apply_func([](double x) { return x * 3.0; });
    if (!check_values(v, 6.0))
        report_error("vector apply_func produced wrong values");
    return (int)errors().size();
}

int matrix_apply_func_test::execute()
{
    la::matrix<double> A(2, 2, 1.5);
    A.apply_func([](double x) { return x + 0.5; });
    if (!check_values(A, 2.0))
        report_error("matrix apply_func produced wrong values");
    return (int)errors().size();
}

} // namespace test
} // namespace la
