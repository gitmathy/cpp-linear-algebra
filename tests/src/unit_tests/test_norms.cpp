#include "tests/includes/unit_tests/test_norms.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include <cmath>

namespace la
{
namespace test
{

int vector_norms_test::execute()
{
    la::vector<double> v(4);
    v(0) = -1.0;
    v(1) = 2.0;
    v(2) = -2.0;
    v(3) = 3.0;

    // 1-norm = sum abs = 1+2+2+3 = 8
    if (std::abs(la::norm<1>(v) - 8.0) > LA_EPS)
        report_error("vector 1-norm is incorrect");

    // 2-norm = sqrt(1+4+4+9) = sqrt(18)
    if (std::abs(la::norm<2>(v) - std::sqrt(18.0)) > LA_EPS)
        report_error("vector 2-norm is incorrect");

    // 3-norm = (1+8+8+27)^(1/3) = (44)^(1/3)
    if (std::abs(la::norm<3>(v) - std::pow(44.0, 1.0 / 3.0)) > LA_EPS)
        report_error("vector 3-norm is incorrect");

    // max-norm = 3
    if (std::abs(la::norm<LA_UINT_MAX>(v) - 3.0) > LA_EPS)
        report_error("vector max-norm is incorrect");

    return (int)errors().size();
}

int matrix_norms_test::execute()
{
    // quick sanity check for matrix norms using uniform values
    la::matrix<double> A(2, 3, -2.0);

    // 1-norm = sum abs = 6 * 2 = 12
    if (std::abs(la::norm<1>(A) - 12.0) > LA_EPS)
        report_error("matrix 1-norm is incorrect");

    // max-norm = 2
    if (std::abs(la::norm<LA_UINT_MAX>(A) - 2.0) > LA_EPS)
        report_error("matrix max-norm is incorrect");

    return (int)errors().size();
}

} // namespace test
} // namespace la
