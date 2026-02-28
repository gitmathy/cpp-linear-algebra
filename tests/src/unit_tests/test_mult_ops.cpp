#include "tests/includes/unit_tests/test_mult_ops.hpp"
#include "la/dense"

namespace la {
namespace test {

int vec_vec_mult_test::execute()
{
    vector<int> x = {3, 4};
    vector<int> y = {4, 3};
    vector<int> z = (x * y);
    vector<int> z_scalar = (x * y) * 2;

    if (!(z.rows() == 2)) {
        report_error("Wrong size of vector*vector");
    }
    if (!check_values(z, 12)) {
        report_error("Wrong elements for vector * vector");
    }

    if (!(z_scalar.rows() == 2)) {
        report_error("Wrong size of (vector+vector) * scalar");
    }
    if (!check_values(z, 24)) {
        report_error("Wrong elements for (vector+vector) * scalar");
    }

    return (int)errors().size();
}

template <storage_type StorageT>
bool check_values_mult(const matrix<int, StorageT> C)
{
    return C(0, 0) == 11 && C(0, 1) == 18 && C(1, 0) == 30 && C(1, 1) == 45;
}

int mat_mat_mult_test::execute()
{
    matrix<int, ROW_WISE> A_row = {{1, 2, 3}, {4, 5, 6}};
    matrix<int, ROW_WISE> B_row = {{2, 3}, {2, 3}, {2, 3}};
    matrix<int, COLUMN_WISE> A_col = {{1, 2, 3}, {4, 5, 6}};
    matrix<int, COLUMN_WISE> B_col = {{2, 3}, {2, 3}, {2, 3}};

    // row = row * row
    matrix<int, ROW_WISE> C_row_row_row = A_row * B_row;
    if (!(C_row_row_row.rows() == 2 && C_row_row_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_row_row_row)) {
        report_error("Wrong size of matrix*matrix");
    }

    // row = row * col
    matrix<int, ROW_WISE> C_row_row_col = (A_row * B_col);
    if (!(C_row_row_col.rows() == 2 && C_row_row_col.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_row_row_col)) {
        report_error("Wrong size of matrix*matrix");
    }

    // row = col * row
    matrix<int, ROW_WISE> C_row_col_row = (A_col * B_row);
    if (!(C_row_col_row.rows() == 2 && C_row_col_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_row_col_row)) {
        report_error("Wrong size of matrix*matrix");
    }

    // row = col * col
    matrix<int, ROW_WISE> C_row_col_col = (A_col * B_col);
    if (!(C_row_col_row.rows() == 2 && C_row_col_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_row_col_col)) {
        report_error("Wrong size of matrix*matrix");
    }

    // col = col * col
    matrix<int, COLUMN_WISE> C_col_col_col = (A_col * B_col);
    if (!(C_col_col_col.rows() == 2 && C_col_col_col.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_col_col_col)) {
        report_error("Wrong size of matrix*matrix");
    }

    // col = col * row
    matrix<int, COLUMN_WISE> C_col_col_row = (A_col * B_row);
    if (!(C_col_col_row.rows() == 2 && C_col_col_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_col_col_row)) {
        report_error("Wrong size of matrix*matrix");
    }

    // col = row * col
    matrix<int, COLUMN_WISE> C_col_row_col = (A_row * B_col);
    if (!(C_col_row_col.rows() == 2 && C_col_row_col.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_col_row_col)) {
        report_error("Wrong size of matrix*matrix");
    }

    // col = row * row
    matrix<int, COLUMN_WISE> C_col_row_row = (A_row * B_row);
    if (!(C_col_row_row.rows() == 2 && C_col_row_row.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!check_values_mult(C_col_row_row)) {
        report_error("Wrong size of matrix*matrix");
    }

    matrix<int, ROW_WISE> C_scalar = (A_row * 2);
    if (!(C_row_col_row.rows() == 2 && C_row_col_row.cols() == 3)) {
        report_error("Wrong size of matrix*scalar");
    }
    if (!(C_row_col_row(0, 0) == 2 && C_row_col_row(0, 1) == 4 && C_row_col_row(0, 2) == 6 &&
          C_row_col_row(1, 0) == 8 && C_row_col_row(1, 1) == 10 && C_row_col_row(1, 2) == 12)) {
        report_error("Wrong size of matrix*scalar");
    }

    return (int)errors().size();
}

int mat_vec_mult_test::execute()
{
    matrix<int> A(2, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    vector<int> x(3);
    x(0) = 1;
    x(1) = 2;
    x(2) = 3;
    vector<int> y = A * x;
    if (!(y(0) == 14 && y(1) == 32))
        report_error("matrix*vector produced wrong values");

    return (int)errors().size();
}

} // namespace test
} // namespace la
