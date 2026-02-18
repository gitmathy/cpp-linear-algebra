#include "tests/includes/unit_tests/test_copy_ctor.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_copy_ctor_test::execute()
{
    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 2 + 1);

    la::vector<double> dst(src); // copy-ctor
    if (dst.rows() != src.rows())
        report_error("Copy-constructed vector has incorrect size");
    for (la::size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - src(i)) > LA_EPS)
            report_error("Copy-constructed vector has incorrect value");
    }

    return (int)errors().size();
}

int matrix_copy_ctor_test::execute()
{
    la::matrix<float> src(2, 2);
    src(0, 0) = 1.0f;
    src(0, 1) = 2.0f;
    src(1, 0) = 3.0f;
    src(1, 1) = 4.0f;

    la::matrix<float> dst(src);
    if (dst.rows() != src.rows() || dst.cols() != src.cols())
        report_error("Copy-constructed matrix has incorrect size");

    if (std::abs(dst(1, 1) - src(1, 1)) > LA_EPS)
        report_error("Copy-constructed matrix has incorrect values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
