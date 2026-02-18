#include "tests/includes/unit_tests/test_unary_assignment.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_unary_assignment_test::execute()
{
    la::vector<int> a(3, 1.0);
    la::vector<int> b = -a;

    if (!check_values(b, -1))
        report_error("vector = -vector produced wrong values");

    return (int)errors().size();
}

int matrix_unary_assignment_test::execute()
{
    la::matrix<int> a(2, 2, 1);
    la::matrix<int> b = -a;

    if (!check_values(b, -1))
        report_error("matrix = -matrix produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
