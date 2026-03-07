/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_dense_algorithm.cpp
/// @brief Definition of testing dense algorithm
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_dense_algorithm.hpp"
#include "la/dense"
#include "tests/includes/collection.hpp"
#include <memory>

namespace la {
namespace test {

void add_all_dense_algorithm(unit_test_collection &collection)
{
    collection.transfer("dense_algorithm", std::make_unique<lu_decomposition_test>());
}

int lu_decomposition_test::execute()
{
    matrix<double, ROW_WISE> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});

    la::algorithm::lu_decomposition<double, ROW_WISE> lu(A);
    vector<double> x = lu.solve(b);

    if (x.rows() != 3) {
        report_error("wrong size of LU decomposition solve");
    }

    if (!(std::abs(x(0) - 2.2) < util::EPS && std::abs(x(1) - 1.4) < util::EPS &&
          std::abs(x(2) - 1.2) < util::EPS)) {
        report_error("lu decomposition solve (row) produced wrong results");
    }

    matrix<double, COLUMN_WISE> A_col({{0, 1, 2}, {2, 1, 1}, {1, 2, 1}});

    la::algorithm::lu_decomposition<double, COLUMN_WISE> lu_col(A_col);
    x = lu.solve(b);

    if (x.rows() != 3) {
        report_error("wrong size of LU decomposition solve");
    }

    if (!(std::abs(x(0) - 2.2) < util::EPS && std::abs(x(1) - 1.4) < util::EPS &&
          std::abs(x(2) - 1.2) < util::EPS)) {
        report_error("lu decomposition (col) solve produced wrong results");
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

} // namespace test
} // namespace la
