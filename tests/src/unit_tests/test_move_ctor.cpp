#include "tests/includes/unit_tests/test_move_ctor.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_move_ctor_test::execute()
{
    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 10 + 1);

    la::vector<double> dst(std::move(src));
    if (dst.rows() != 4)
        report_error("Moved-to vector has incorrect size");

    for (la::size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - static_cast<double>(i * 10 + 1)) > LA_EPS)
            report_error("Moved-to vector has incorrect value");
    }

    if (src.rows() != 0)
        report_error("Moved-from vector not left in empty state (expected size==0)");

    return (int)errors().size();
}

int matrix_move_ctor_test::execute()
{
    la::matrix<double> src(2, 2);
    src(0, 0) = 1.0;
    src(0, 1) = 2.0;
    src(1, 0) = 3.0;
    src(1, 1) = 4.0;

    la::matrix<double> dst(std::move(src));
    if (dst.rows() != 2 || dst.cols() != 2)
        report_error("Moved-to matrix has incorrect size");

    if (src.rows() != 0 || src.cols() != 0)
        report_error("Moved-from matrix not left in empty state (expected size==0)");

    return (int)errors().size();
}

} // namespace test
} // namespace la
