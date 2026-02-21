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

int matrix_mult_div_assignment_test::execute()
{
    la::matrix<int, ROW_WISE> A_row = {{1, 2}, {3, 4}, {5, 6}};
    la::matrix<int, ROW_WISE> B_row = {{1, 2, 3}, {4, 5, 6}};

    B_row *= A_row;
    if (!(B_row.rows() == 2 && B_row.cols() == 2)) {
        std::cout << "Result (row_wise): " << B_row << std::endl;
        report_error("Matrix multiplication (row_wise) assignment wrong size");
    }
    if (!(B_row(0, 0) == 22 && B_row(0, 1) == 28 && B_row(1, 0) == 49 && B_row(1, 1) == 64)) {
        report_error("Matrix multiplication (row_wise) assignment wrong values");
    }

    la::matrix<int, COLUMN_WISE> A_col = {{1, 3, 5}, {2, 4, 6}};
    la::matrix<int, COLUMN_WISE> B_col = {{1, 4}, {2, 5}, {3, 6}};

    B_col *= A_col;
    if (!(B_col.rows() == 2 && B_col.cols() == 2)) {
        report_error("Matrix multiplication (col_wise) assignment wrong size");
    }
    if (!(B_col(0, 0) == 22 && B_col(0, 1) == 28 && B_col(1, 0) == 49 && B_col(1, 1) == 64)) {
        report_error("Matrix multiplication (col_wise) assignment wrong values");
    }

    la::matrix<int, COLUMN_WISE> B_col_row = {{1, 4}, {2, 5}, {3, 6}};

    B_col_row *= A_row;
    if (!(B_col_row.rows() == 2 && B_col_row.cols() == 2)) {
        report_error("Matrix multiplication (col_wise) assignment wrong size");
    }
    if (!(B_col_row(0, 0) == 22 && B_col_row(0, 1) == 28 && B_col_row(1, 0) == 49 &&
          B_col_row(1, 1) == 64)) {
        report_error("Matrix multiplication (col_wise *= row_wise) assignment wrong values");
    }

    la::matrix<int, ROW_WISE> B_row_col = {{1, 2, 3}, {4, 5, 6}};

    B_row_col *= A_col;
    if (!(B_row_col.rows() == 2 && B_row_col.cols() == 2)) {
        report_error("Matrix multiplication (col_wise) assignment wrong size");
    }
    if (!(B_row_col(0, 0) == 22 && B_row_col(0, 1) == 28 && B_row_col(1, 0) == 49 &&
          B_row_col(1, 1) == 64)) {
        report_error("Matrix multiplication (col_wise *= row_wise) assignment wrong values");
    }

    matrix<int, ROW_WISE> C = {{1, 2}, {3, 4}};
    matrix<int, ROW_WISE> D = {{1, 2, 3}, {4, 5, 6}};
    C *= (D + D);
    if (!(C.rows() == 2 && C.cols() == 3)) {
        report_error("Matrix multiplication with expression assignment wrong size");
    }
    if (!(C(0, 0) == 18 && C(0, 1) == 24 && C(0, 2) == 30 && C(1, 0) == 38 && C(1, 1) == 52) &&
        C(1, 2) == 66) {
        report_error("Matrix multiplication assignment with expression wrong values");
    }

    matrix<int, ROW_WISE> E = {{1, 2}, {3, 4}};
    E *= 2;
    if (!(E.rows() == 2 && E.cols() == 2)) {
        report_error("Matrix multiplication with scalar assignment wrong size");
    }
    if (!(E(0, 0) == 2 && E(0, 1) == 4 && E(1, 0) == 6 && E(1, 1) == 8)) {
        report_error("Matrix multiplication assignment with scalar wrong values");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
