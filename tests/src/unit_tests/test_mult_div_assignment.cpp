#include "tests/includes/unit_tests/test_mult_div_assignment.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

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

    return (int)errors().size();
}

} // namespace test
} // namespace la
