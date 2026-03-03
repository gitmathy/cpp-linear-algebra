/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_construct.cpp
/// @brief Implementation of test of constructor
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_construct.hpp"
#include "la/dense"
#include "la/static"

namespace la {
namespace test {

int vector_construct_test::execute()
{
    // test with double
    // ----------------
    vector<double> *vd = new vector<double>(2, 3.14);
    if (vd->rows() != 2) {
        report_error("Constructor set wrong sizes of double vector");
    }
    if (!check_values(*vd, 3.14)) {
        report_error("Values not correct after constructing a double vector");
    }
    delete vd;

    // test with float
    // ----------------
    vector<float> *vf = new vector<float>(2, 3.14f);
    if (vf->rows() != 2) {
        report_error("Constructor set wrong sizes of float matrix");
    }
    if (!check_values(*vf, 3.14f)) {
        report_error("Values not correct after constructing a float vector");
    }
    delete vf;

    // test with initializer list
    // ----------------
    vector<int> *vi = new vector<int>({1, 2});
    if (vi->rows() != 2) {
        report_error("Constructor by initializer lis set wrong size of vector");
    }
    if (!((*vi)(0) == 1 && (*vi)(1) == 2)) {
        report_error("Values set by initializer list are not correct");
    }
    delete vi;

    static_vector<int, 3> v_static(2);
    vector<int> v_from_static(v_static);
    if (v_from_static.rows() != 3) {
        report_error("Vector constructor from static_vector produced wrong size");
    }
    if (!check_values(v_from_static, 2)) {
        report_error("Wrong values in vector constructed from static_vector");
    }

    vector<static_vector<int, 3>> vector_non_trivial_type(1, static_vector<int, 3>(2));
    if (vector_non_trivial_type.rows() != 1) {
        report_error("Vector constructor for non-trivial type produced wrong size");
    }
    if (!check_values(vector_non_trivial_type(1), 2)) {
        report_error("Wrong values in vector of non-trivial type");
    }

    return (int)errors().size();
}

int static_vector_construct_test::execute()
{
    // test with double
    // ----------------
    static_vector<double, 3> *vd = new static_vector<double, 3>(3.14);
    if (vd->rows() != 3) {
        report_error("Constructor set wrong sizes of double static_vector");
    }
    if (!check_values(*vd, 3.14)) {
        report_error("Values not correct after constructing a double static_vector");
    }
    delete vd;

    // test with float
    // ----------------
    static_vector<float, 3> *vf = new static_vector<float, 3>(3.14f);
    if (vf->rows() != 3) {
        report_error("Constructor set wrong sizes of float matrix");
    }
    if (!check_values(*vf, 3.14f)) {
        report_error("Values not correct after constructing a float static_vector");
    }
    delete vf;

    // test with initializer list
    // ----------------
    static_vector<int, 2> *vi = new static_vector<int, 2>({1, 2});
    if (vi->rows() != 2) {
        report_error("Constructor by initializer lis set wrong size of static_vector");
    }
    if (!((*vi)(0) == 1 && (*vi)(1) == 2)) {
        report_error("Values set by initializer list are not correct");
    }
    delete vi;

    vector<int> v_dynamic(10, 4);
    static_vector<int, 10> v_from_dynamic(v_dynamic);
    if (v_from_dynamic.rows() != 10) {
        report_error("Vector constructor from static_vector produced wrong size");
    }
    if (!check_values(v_from_dynamic, 4)) {
        report_error("Wrong values in vector constructed from static_vector");
    }

    return (int)errors().size();
}

int matrix_construct_test::execute()
{
    // test with double
    // ----------------
    matrix<double> *md = new matrix<double>(2, 3, 3.14);
    if (md->rows() != 2 || md->cols() != 3) {
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

    matrix<int, COLUMN_WISE> *mi_col = new matrix<int, COLUMN_WISE>({{1, 2}, {3, 4}});
    if (mi_col->rows() != 2 || mi_col->cols() != 2) {
        report_error("Constructor by initializer lis set wrong size of matrix");
    }
    if (!((*mi_col)(0, 0) == 1 && (*mi_col)(0, 1) == 3 && (*mi_col)(1, 0) == 2 &&
          (*mi_col)(1, 1) == 4)) {
        report_error("Matrix(column-wise) values set by initializer list are not correct");
    }
    delete mi_col;

    return (int)errors().size();
}

} // namespace test
} // namespace la
