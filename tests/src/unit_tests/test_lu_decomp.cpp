#include "tests/includes/unit_tests/test_lu_decomp.hpp"
#include "includes/algorithms/decompositions.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int lu_decomposition_test::execute()
{
    matrix<double, ROW_WISE> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    vector<double> b({4, 6, 7});

    la::algorithm::lu_decomposition<double> lu(A);
    vector<double> x = lu.solve(b);

    if (x.rows() != 3) {
        report_error("wrong size of LU decomposition solve");
    }

    if (!(std::abs(x(0) - 2.2) < LA_EPS && std::abs(x(1) - 1.4) < LA_EPS &&
          std::abs(x(2) - 1.2) < LA_EPS)) {
        report_error("lu decomposition solve produced wrong results");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
