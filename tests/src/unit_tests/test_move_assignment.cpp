#include "tests/includes/unit_tests/test_move_assignment.hpp"
#include "la/dense"
#include "la/util/constants.hpp"

namespace la {
namespace test {
int vector_move_assignment_test::execute()
{
    // double
    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 10 + 1);

    la::vector<double> dst(1);
    dst = std::move(src);
    if (dst.rows() != 4) {
        report_error("Moved-to vector has incorrect size");
    }

    // basic value checks
    for (la::size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - static_cast<double>(i * 10 + 1)) > util::EPS) {
            report_error("Moved-to vector has incorrect value");
        }
    }

    // moved-from should be empty (implementation detail expected by old tests)
    if (src.rows() != 0) {
        report_error("Moved-from vector not left in empty state (expected size==0)");
    }

    return (int)errors().size();
}

int matrix_move_assignment_test::execute()
{
    la::matrix<int> src(2, 2);
    src(0, 0) = 1;
    src(0, 1) = 2;
    src(1, 0) = 3;
    src(1, 1) = 4;

    la::matrix<int> dst(1, 1);
    dst = std::move(src);

    if (dst.rows() != 2 || dst.cols() != 2) {
        report_error("Moved-to matrix has incorrect size");
    }

    if (src.rows() != 0 || src.cols() != 0) {
        report_error("Moved-from matrix not left in empty state (expected size==0)");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
