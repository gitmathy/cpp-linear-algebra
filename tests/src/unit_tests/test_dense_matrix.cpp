/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_dense.cpp
/// @brief Definition of testing dense matrix data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_dense_matrix.hpp"
#include "la/dense"
#include <memory>

namespace la {
namespace test {

void add_all_dense_matrix(unit_test_collection &collection)
{
    collection.transfer("dense_matrix", std::make_unique<matrix_add_sub_assignment_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_add_sub_ops_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_apply_func_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_construct_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_copy_assignment_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_copy_ctor_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_iterator_test>());
    collection.transfer("dense_matrix", std::make_unique<mixed_operations>());
    collection.transfer("dense_matrix", std::make_unique<matrix_move_ctor_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_mult_assignment_test>());
    collection.transfer("dense_matrix", std::make_unique<mat_vec_mult_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_norms_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_read_write_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_resize_test>());
    collection.transfer("dense_matrix", std::make_unique<matrix_unary_assignment_test>());
}

int matrix_add_sub_assignment_test::execute()
{
    matrix<double> a(2, 2, 1.0);
    matrix<double> b(2, 2, 2.0);

    a += b;
    if (!check_values(a, 3.0))
        report_error("matrix += matrix produced wrong values");

    a -= b;
    if (!check_values(a, 1.0))
        report_error("matrix -= matrix produced wrong values");

    return (int)errors().size();
}

int matrix_add_sub_ops_test::execute()
{
    matrix<double> a(2, 2, 1.0);
    matrix<double> b(2, 2, 2.0);

    // use operator+ / - (operants)
    matrix<double> c = a + b;
    if (!check_values(c, 3.0)) {
        report_error("matrix add (via +) produced wrong values");
    }

    matrix<double> d = b - a;
    if (!check_values(d, 1.0)) {
        report_error("matrix sub (via -) produced wrong values");
    }

    // scalar + matrix and matrix + scalar
    matrix<double> s1 = a + 2.0; // matrix + scalar
    if (!check_values(s1, 3.0)) {
        report_error("matrix add scalar (matrix + scalar) produced wrong values");
    }

    matrix<double> s2 = 2.0 + a; // scalar + matrix
    if (!check_values(s2, 3.0)) {
        report_error("matrix add scalar (scalar + matrix) produced wrong values");
    }

    // adding/subtracting operants with matrix
    matrix<double> op1 = a + (a + b); // matrix + operant
    if (!check_values(op1, 4.0)) {
        report_error("matrix add operant (matrix + operant) produced wrong values");
    }

    matrix<double> op2 = (a + b) + a; // operant + matrix
    if (!check_values(op2, 4.0)) {
        report_error("matrix add operant (operant + matrix) produced wrong values");
    }

    matrix<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0)) {
        report_error("matrix sub operant (matrix - operant) produced wrong values");
    }

    return (int)errors().size();
}

int matrix_apply_func_test::execute()
{
    la::matrix<double> A(2, 2, 1.5);
    A.apply_func([](double x) { return x + 0.5; });
    if (!check_values(A, 2.0)) {
        report_error("matrix apply_func produced wrong values");
    }
    return (int)errors().size();
}

int matrix_construct_test::execute()
{
    // test with double
    // ----------------
    matrix<double> *md = new matrix<double>(2, 3, 3.14);
    if (md->rows() != 2 || md->cols() != 3 || md->non_zeros() != 6) {
        report_error("Constructor set wrong sizes of double matrix");
    }
    if (!check_values(*md, 3.14)) {
        report_error("Values not correct after constructing a double matrix");
    }
    delete md;

    // test with float
    // ----------------
    matrix<float> *mf = new matrix<float>(2, 3, 3.14f);
    if (mf->rows() != 2 || mf->cols() != 3) {
        report_error("Constructor set wrong sizes of float matrix");
    }
    if (!check_values(*mf, 3.14f)) {
        report_error("Values not correct after constructing a float matrix");
    }
    delete mf;

    // test with initializer list
    // ----------------
    matrix<int> *mi = new matrix<int>({{1, 2}, {3, 4}});
    if (mi->rows() != 2 || mi->cols() != 2) {
        report_error("Constructor by initializer lis set wrong size of matrix");
    }
    if (!((*mi)(0, 0) == 1 && (*mi)(0, 1) == 2 && (*mi)(1, 0) == 3 && (*mi)(1, 1) == 4)) {
        report_error("Matrix(row-wise) values set by initializer list are not correct");
    }
    delete mi;

    return (int)errors().size();
}

int matrix_copy_assignment_test::execute()
{
    matrix<double> src(2, 3);
    for (size_type r = 0; r < src.rows(); ++r) {
        for (size_type c = 0; c < src.cols(); ++c) {
            src(r, c) = static_cast<double>(r * 10 + c);
        }
    }

    matrix<double> dst(1, 1);
    dst = src;
    if (dst.rows() != src.rows() || dst.cols() != src.cols()) {
        report_error("Copy-assigned matrix has incorrect size");
    }

    for (size_type r = 0; r < dst.rows(); ++r) {
        for (size_type c = 0; c < dst.cols(); ++c) {
            if (std::abs(dst(r, c) - src(r, c)) > util::EPS) {
                report_error("Copy-assigned matrix has incorrect values");
            }
        }
    }

    return (int)errors().size();
}

int matrix_copy_ctor_test::execute()
{
    matrix<float> src(2, 2);
    src(0, 0) = 1.0f;
    src(0, 1) = 2.0f;
    src(1, 0) = 3.0f;
    src(1, 1) = 4.0f;

    matrix<float> dst(src);
    if (dst.rows() != src.rows() || dst.cols() != src.cols()) {
        report_error("Copy-constructed matrix has incorrect size");
    }

    if (std::abs(dst(1, 1) - src(1, 1)) > util::EPS) {
        report_error("Copy-constructed matrix has incorrect values");
    }

    return (int)errors().size();
}

int matrix_iterator_test::execute()
{
    matrix<size_type> m(2, 5);
    size_type cnt = 0;
    for (size_type i = 0; i < m.rows(); ++i)
        for (size_type j = 0; j < m.cols(); ++j)
            m(i, j) = ++cnt; // 1..10 row-major

    size_type pos = 0;
    for (matrix<size_type>::citerator it = m.begin(); it != m.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Iterator over row-wise matrix read incorrect value");

    pos = 5;
    for (matrix<size_type>::citerator it = m.row_begin(1); it != m.row_end(1); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Row iterator read incorrect value");

    if (!(m(m.row_idx_begin(0)) == 0 || m.row_idx_begin(1) == 5)) {
        report_error("Row index begin wrong value");
    }

    if (!(m.col_idx(0) == 0 || m.col_idx(1) == 1 || m.col_idx(2) == 3 || m.col_idx(3) == 3 ||
          m.col_idx(4) == 4 || m.col_idx(5) == 0 || m.col_idx(6) == 1 || m.col_idx(7) == 3 ||
          m.col_idx(8) == 3 || m.col_idx(9) == 4)) {
        report_error("Column index gave wrong column for a non-zero");
    }

    return (int)errors().size();
}

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

int matrix_move_ctor_test::execute()
{
    matrix<double> src(2, 2);
    src(0, 0) = 1.0;
    src(0, 1) = 2.0;
    src(1, 0) = 3.0;
    src(1, 1) = 4.0;

    matrix<double> dst(std::move(src));
    if (dst.rows() != 2 || dst.cols() != 2) {
        report_error("Moved-to matrix has incorrect size");
    }

    if (src.rows() != 0 || src.cols() != 0) {
        report_error("Moved-from matrix not left in empty state (expected size==0)");
    }

    return (int)errors().size();
}

int matrix_mult_assignment_test::execute()
{

    matrix<int> A(2, 2, 4);
    A *= 2;
    if (!check_values(A, 8)) {
        report_error("Matrix mult assignment results in wrong values");
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

int matrix_norms_test::execute()
{
    // quick sanity check for matrix norms using uniform values
    matrix<double> A(2, 3, -2.0);

    // 1-norm = sum abs = 6 * 2 = 12
    if (std::abs(norm<1>(A) - 12.0) > util::EPS)
        report_error("matrix 1-norm is incorrect");

    // max-norm = 2
    if (std::abs(norm<SIZE_TYPE_MAX>(A) - 2.0) > util::EPS)
        report_error("matrix max-norm is incorrect");

    return (int)errors().size();
}

int matrix_read_write_test::execute()
{
    la::matrix<float> A_row({{1., 2., 3.}, {4., 5., 6.}});
    std::string filename = "tmp_read_matrix_testing.tst";

    // Test binary write and read
    try {
        A_row.to_file(filename, true);
        la::matrix<float> A_bin;
        A_bin.from_file(filename, true);
        if (!(A_bin.rows() == 2 && A_bin.cols() == 3)) {
            report_error("Wrong size of read matrix");
        }
        if (!(std::abs(A_bin(0, 0) - 1.) < util::EPS && std::abs(A_bin(0, 1) - 2.) < util::EPS &&
              std::abs(A_bin(0, 2) - 3.) < util::EPS && std::abs(A_bin(1, 0) - 4.) < util::EPS &&
              std::abs(A_bin(1, 1) - 5.) < util::EPS && std::abs(A_bin(1, 2) - 6.) < util::EPS)) {
            report_error("Wrong elements read");
        }
        A_bin.resize(0, 0);
    } catch (const util::error &) {
        report_error("Matrix binary ascii: Cannot write to or read from file");
    }
    util::delete_file(filename);

    // Test ascii write and read
    try {
        A_row.to_file(filename, false);
        la::matrix<float> A_txt;
        A_txt.from_file(filename, false);
        if (!(A_txt.rows() == 2 && A_txt.cols() == 3)) {
            report_error("Wrong size of read matrix");
        }
        if (!(std::abs(A_txt(0, 0) - 1.) < util::EPS && std::abs(A_txt(0, 1) - 2.) < util::EPS &&
              std::abs(A_txt(0, 2) - 3.) < util::EPS && std::abs(A_txt(1, 0) - 4.) < util::EPS &&
              std::abs(A_txt(1, 1) - 5.) < util::EPS && std::abs(A_txt(1, 2) - 6.) < util::EPS)) {
            report_error("Wrong elements read");
        }
        A_txt.resize(0, 0);
    } catch (const util::error &) {
        report_error("Matrix row ascii: Cannot write to or read from file");
    }
    util::delete_file(filename);

    return (int)errors().size();
}

int matrix_resize_test::execute()
{
    // test with double
    // ----------------
    matrix<double> a_double(1, 1);
    a_double.resize(5, 4, double(100));

    // make the structure bigger
    if (a_double.rows() != 5) {
        report_error("Resize does not set new rows");
    }
    if (a_double.cols() != 4) {
        report_error("Resize does not set new columns");
    }
    if (!check_values(a_double, double(100))) {
        report_error("Values not correct after increase size of matrix");
    }

    // make the structure smaller
    a_double.resize(4, 3);
    if (a_double.rows() != 4) {
        report_error("Resize does not set new rows");
    }
    if (a_double.cols() != 3) {
        report_error("Resize does not set new columns");
    }
    if (!check_values(a_double, double(100))) {
        report_error("Values not correct after increase size of matrix");
    }

    // test with float
    // ----------------
    matrix<float> a_float(1, 1);
    a_float.resize(5, 4, float(100));

    // make the structure bigger
    if (a_float.rows() != 5) {
        report_error("Resize does not set new rows");
    }
    if (a_float.cols() != 4) {
        report_error("Resize does not set new columns");
    }
    if (!check_values(a_float, 100.f)) {
        report_error("Values not correct after increase size of matrix");
    }

    // make the structure smaller
    a_float.resize(4, 3);
    if (a_float.rows() != 4) {
        report_error("Resize does not set new rows");
    }
    if (a_float.cols() != 3) {
        report_error("Resize does not set new columns");
    }
    if (!check_values(a_float, float(100))) {
        report_error("Values not correct after increase size of matrix");
    }

    return (int)errors().size();
}

int matrix_unary_assignment_test::execute()
{
    matrix<int> a(2, 2, 1);
    matrix<int> b = -a;

    if (!check_values(b, -1)) {
        report_error("matrix = -matrix produced wrong values");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
