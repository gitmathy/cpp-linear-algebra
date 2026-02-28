#include "tests/includes/unit_tests/test_mixed_operations.hpp"
#include "la/dense"

namespace la {
namespace test {

int mixed_operations::execute()
{
    la::vector<int> a = {1, 2};
    la::vector<int> b = {2, 3};
    la::matrix<int> A = {{1, 2}, {3, 4}};
    la::matrix<int> B = {{3, 4}, {4, 5}};

    la::vector<int> x = -a + b + 2 * b + (A + B) * a + (2 * B) * b;

    if (!(x.rows() == 2)) {
        report_error("Wrong size when mixed multiplication and division");
    }
    if (!(x(0) == 57 && x(1) == 78)) {
        report_error("Wrong element for multiplying vector with a scalar");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
