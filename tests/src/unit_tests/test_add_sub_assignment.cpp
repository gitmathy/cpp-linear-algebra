#include "tests/includes/unit_tests/test_add_sub_assignment.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la
{
namespace test
{

int vector_add_sub_assignment_test::execute()
{
    la::vector<double> a(3, 1.0);
    la::vector<double> b(3, 2.0);

    a += b;
    if (std::abs(a(0) - 3.0) > LA_EPS || std::abs(a(1) - 3.0) > LA_EPS || std::abs(a(2) - 3.0) > LA_EPS)
        report_error("vector += vector produced wrong values");

    a -= b;
    if (!check_values(a, 1.0))
        report_error("vector -= vector produced wrong values");

    return (int)errors().size();
}

int matrix_add_sub_assignment_test::execute()
{
    la::matrix<double> a(2, 2, 1.0);
    la::matrix<double> b(2, 2, 2.0);

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
