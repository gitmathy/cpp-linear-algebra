#include "tests/includes/unit_tests/test_mult_ops.hpp"
#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vec_vec_mult_test::execute()
{
    la::vector<int> x = {3, 4};
    la::vector<int> y = {4, 3};
    la::vector<int> z = (x * y);
    la::vector<int> z_scalar = (x * y) * 2;

    if (!(z.rows() == 2)) {
        report_error("Wrong size of vector*vector");
    }
    if (!check_values(z, 12)) {
        report_error("Wrong elements for vector * vector");
    }

    if (!(z.rows() == 2)) {
        report_error("Wrong size of vector*vector");
    }
    if (!check_values(z, 24)) {
        report_error("Wrong elements for (vector+vector) * scalar");
    }

    return (int)errors().size();
}

int mat_mat_mult_test::execute()
{
    // Both row storage
    la::matrix<int> A_row = {{1, 2, 3}, {4, 5, 6}};
    la::matrix<int> B_row = {{2, 3}, {2, 3}, {2, 3}};
    la::matrix<int> C_row = (A_row * B_row);

    if (!(C_row.rows() == 2 && C_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!(C_row(0, 0) == 11 && C_row(0, 1) == 18 && C_row(1, 0) == 30 && C_row(1, 1) == 45)) {
        report_error("Wrong size of matrix*matrix");
    }

    // Both column storage
    la::matrix<int, COLUMN_WISE> A_col = {{1, 2, 3}, {4, 5, 6}};
    la::matrix<int, COLUMN_WISE> B_col = {{2, 3}, {2, 3}, {2, 3}};
    la::matrix<int, COLUMN_WISE> C_col = (A_col * B_col);

    if (!(C_col.rows() == 2 && C_col.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!(C_col(0, 0) == 11 && C_col(0, 1) == 18 && C_col(1, 0) == 30 && C_col(1, 1) == 45)) {
        report_error("Wrong size of matrix*matrix");
    }

    // Row * Col
    la::matrix<int> C_row_col = (A_row * B_col);

    if (!(C_row_col.rows() == 2 && C_row_col.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!(C_row_col(0, 0) == 11 && C_row_col(0, 1) == 18 && C_row_col(1, 0) == 30 &&
          C_row_col(1, 1) == 45)) {
        report_error("Wrong size of matrix*matrix");
    }

    // Col * Row
    la::matrix<int> C_col_row = (A_row * B_row);

    if (!(C_col_row.rows() == 2 && C_col_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!(C_col_row(0, 0) == 11 && C_col_row(0, 1) == 18 && C_col_row(1, 0) == 30 &&
          C_col_row(1, 1) == 45)) {
        report_error("Wrong size of matrix*matrix");
    }

    la::matrix<int> C_scalar = (A_row * 2);
    if (!(C_col_row.rows() == 2 && C_col_row.cols() == 3)) {
        report_error("Wrong size of matrix*scalar");
    }
    if (!(C_col_row(0, 0) == 2 && C_col_row(0, 1) == 4 && C_col_row(0, 2) == 6 &&
          C_col_row(1, 0) == 8 && C_col_row(1, 1) == 10 && C_col_row(1, 2) == 12)) {
        report_error("Wrong size of matrix*scalar");
    }

    return (int)errors().size();
}

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
