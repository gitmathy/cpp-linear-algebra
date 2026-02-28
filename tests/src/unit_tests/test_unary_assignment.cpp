#include "tests/includes/unit_tests/test_unary_assignment.hpp"
#include "la/dense"

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
