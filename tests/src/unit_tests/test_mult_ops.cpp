#include "tests/includes/unit_tests/test_mult_ops.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la
{
namespace test
{

int mat_vec_mult_test::execute()
{
    la::matrix<int> A(2, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    la::vector<int> x(3);
    x(0) = 1;
    x(1) = 2;
    x(2) = 3;
    la::vector<int> y = A * x;
    if (!(y(0) == 14 && y(1) == 32))
        report_error("matrix*vector produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
