/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_vector.cpp
/// @brief Definition of testing vector data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_vector.hpp"
#include "la/dense"
#include "tests/includes/collection.hpp"
#include <memory>

namespace la {
namespace test {

void add_all_vector(unit_test_collection &collection)
{
    collection.transfer("vector", std::make_unique<vector_add_sub_assignment_test>());
    collection.transfer("vector", std::make_unique<vector_add_sub_ops_test>());
    collection.transfer("vector", std::make_unique<vector_apply_func_test>());
    collection.transfer("vector", std::make_unique<vector_construct_test>());
    collection.transfer("vector", std::make_unique<vector_copy_assignment_test>());
    collection.transfer("vector", std::make_unique<vector_copy_ctor_test>());
    collection.transfer("vector", std::make_unique<vector_inner_product_test>());
    collection.transfer("vector", std::make_unique<vector_iterator_test>());
    collection.transfer("vector", std::make_unique<vector_move_ctor_test>());
    collection.transfer("vector", std::make_unique<vector_mult_assignment_test>());
    collection.transfer("vector", std::make_unique<vec_vec_mult_test>());
    collection.transfer("vector", std::make_unique<vector_norms_test>());
    collection.transfer("vector", std::make_unique<vector_read_write_test>());
    collection.transfer("vector", std::make_unique<vector_resize_test>());
    collection.transfer("vector", std::make_unique<vector_unary_assignment_test>());
}

int vector_add_sub_assignment_test::execute()
{
    vector<double> a(3, 1.0);
    vector<double> b(3, 2.0);

    a += b;
    if (std::abs(a(0) - 3.0) > util::EPS || std::abs(a(1) - 3.0) > util::EPS ||
        std::abs(a(2) - 3.0) > util::EPS)
        report_error("vector += vector produced wrong values");

    a -= b;
    if (!check_values(a, 1.0))
        report_error("vector -= vector produced wrong values");

    return (int)errors().size();
}

int vector_add_sub_ops_test::execute()
{
    vector<double> a(3, 1.0);
    vector<double> b(3, 2.0);

    // use operator+ / - (operants) instead of in-place ops
    vector<double> c = a + b;
    if (!check_values(c, 3.0)) {
        report_error("vector add (via +) produced wrong values");
    }

    vector<double> d = b - a;
    if (!check_values(d, 1.0)) {
        report_error("vector sub (via -) produced wrong values");
    }

    // scalar + vector and vector + scalar
    vector<double> s1 = a + 2.0;
    if (!check_values(s1, 3.0)) {
        report_error("vector add scalar (vector + scalar) produced wrong values");
    }

    vector<double> s2 = 2.0 + a;
    if (!check_values(s2, 3.0)) {
        report_error("vector add scalar (scalar + vector) produced wrong values");
    }

    // adding/subtracting operants with vector
    vector<double> op1 = a + (a + b); // vector + operant
    if (!check_values(op1, 4.0)) {
        report_error("vector add operant (vector + operant) produced wrong values");
    }

    vector<double> op2 = (a + b) + a; // operant + vector
    if (!check_values(op2, 4.0)) {
        report_error("vector add operant (operant + vector) produced wrong values");
    }

    vector<double> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0.0)) {
        report_error("vector sub operant (vector - operant) produced wrong values");
    }

    return (int)errors().size();
}

int vector_apply_func_test::execute()
{
    la::vector<double> v(5, 2.0);
    v.apply_func([](double x) { return x * 3.0; });
    if (!check_values(v, 6.0)) {
        report_error("vector apply_func produced wrong values");
    }
    return (int)errors().size();
}

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
    if (!check_values(vector_non_trivial_type(0), 2)) {
        report_error("Wrong values in vector of non-trivial type");
    }

    return (int)errors().size();
}

int vector_copy_assignment_test::execute()
{
    // double
    vector<double> src(4);
    for (size_type i = 0; i < src.rows(); ++i) {
        src(i) = static_cast<double>(i * 3 + 2);
    }

    vector<double> dst(2, double(0));
    dst = src; // copy-assign

    if (dst.rows() != src.rows()) {
        report_error("Copy-assigned vector has incorrect size");
    }

    for (size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - src(i)) > util::EPS) {
            std::stringstream ss;
            ss << "Copy-assigned vector has incorrect value at " << i;
            report_error(ss.str());
        }
    }

    // source must remain unchanged
    for (size_type i = 0; i < src.rows(); ++i) {
        if (std::abs(src(i) - static_cast<double>(i * 3 + 2)) > util::EPS) {
            report_error("Source vector changed after copy-assignment");
            break;
        }
    }

    // float & int quick checks
    vector<float> srcf(3);
    for (size_type i = 0; i < srcf.rows(); ++i) {
        srcf(i) = static_cast<float>(i + 1);
    }
    vector<float> dstf(1);
    dstf = srcf;
    if (dstf.rows() != srcf.rows()) {
        report_error("Copy-assigned float vector has incorrect size");
    }

    vector<int> srci(2);
    srci(0) = 5;
    srci(1) = 6;
    vector<int> dsti(1);
    dsti = srci;
    if (dsti.rows() != srci.rows()) {
        report_error("Copy-assigned int vector has incorrect size");
    }

    return (int)errors().size();
}

int vector_copy_ctor_test::execute()
{
    vector<double> src(4);
    for (size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 2 + 1);

    vector<double> dst(src); // copy-ctor
    if (dst.rows() != src.rows())
        report_error("Copy-constructed vector has incorrect size");
    for (size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - src(i)) > util::EPS) {
            report_error("Copy-constructed vector has incorrect value");
        }
    }

    return (int)errors().size();
}

int vector_inner_product_test::execute()
{
    vector<int> a({1, 2, 3});
    vector<int> b({4, 5, 6});

    int alpha = inner_product(a, b);

    if (alpha != 32) {
        report_error("inner_product produced wrong value");
    }
    return (int)errors().size();
}

int vector_iterator_test::execute()
{
    vector<size_type> v(6);
    for (size_type i = 0; i < v.rows(); ++i)
        v(i) = i + 1; // 1..6

    const vector<size_type> cv = v; // use copy / const access
    // iterate with const-iterator and verify values
    size_type pos = 0;
    for (vector<size_type>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Vector const-iterator reads incorrect value");

    // test algorithm on const-iterators (std::accumulate)
    size_type sum = std::accumulate(cv.begin(), cv.end(), size_type(0));
    const size_type expect = 1 + 2 + 3 + 4 + 5 + 6;
    if (sum != expect)
        report_error("std::accumulate over const-iterator produced wrong sum");

    return (int)errors().size();
}

int vector_move_ctor_test::execute()
{
    vector<double> src(4);
    for (size_type i = 0; i < src.rows(); ++i) {
        src(i) = static_cast<double>(i * 10 + 1);
    }

    vector<double> dst(std::move(src));
    if (dst.rows() != 4) {
        report_error("Moved-to vector has incorrect size");
    }

    for (size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - static_cast<double>(i * 10 + 1)) > util::EPS) {
            report_error("Moved-to vector has incorrect value");
        }
    }

    if (src.rows() != 0)
        report_error("Moved-from vector not left in empty state (expected size==0)");

    return (int)errors().size();
}

int vector_mult_assignment_test::execute()
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

    x *= (y * 2);
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying vector with operant");
    }
    if (!(x(0) == 48 && x(1) == 72)) {
        report_error("Wrong element for multiplying vector with a operant");
    }

    return (int)errors().size();
}

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

int vector_norms_test::execute()
{
    vector<double> v(4);
    v(0) = -1.0;
    v(1) = 2.0;
    v(2) = -2.0;
    v(3) = 3.0;

    // 1-norm = sum abs = 1+2+2+3 = 8
    if (std::abs(norm<1>(v) - 8.0) > util::EPS)
        report_error("vector 1-norm is incorrect");

    // 2-norm = sqrt(1+4+4+9) = sqrt(18)
    if (std::abs(norm<2>(v) - std::sqrt(18.0)) > util::EPS)
        report_error("vector 2-norm is incorrect");

    // 3-norm = (1+8+8+27)^(1/3) = (44)^(1/3)
    if (std::abs(norm<3>(v) - std::pow(44.0, 1.0 / 3.0)) > util::EPS)
        report_error("vector 3-norm is incorrect");

    // max-norm = 3
    if (std::abs(norm<SIZE_TYPE_MAX>(v) - 3.0) > util::EPS)
        report_error("vector max-norm is incorrect");

    return (int)errors().size();
}

int vector_read_write_test::execute()
{
    la::vector<double> v({1., 2., 3., 4.});

    std::string filename = "tmp_read_vector_testing.tst";

    // Test binary write and read
    try {
        v.to_file(filename, true);
        la::vector<double> v_bin;
        v_bin.from_file(filename, true);
        if (!(v_bin.rows() == 4)) {
            report_error("Wrong size of read vector");
        }
        if (!(std::abs(v_bin(0) - 1.) < util::EPS && std::abs(v_bin(1) - 2.) < util::EPS &&
              std::abs(v_bin(2) - 3.) < util::EPS && std::abs(v_bin(3) - 4.) < util::EPS)) {
            report_error("Wrong elements read");
        }
    } catch (const util::error &) {
        report_error("Vector binary: Cannot write to or read from file");
    }

    util::delete_file(filename);

    // Test ascii write and read
    v.to_file(filename, false);
    la::vector<double> v_txt;
    try {
        v_txt.from_file(filename, false);
        if (!(v_txt.rows() == 4)) {
            report_error("Wrong size of read vector");
        }
        if (!(std::abs(v_txt(0) - 1.) < util::EPS && std::abs(v_txt(1) - 2.) < util::EPS &&
              std::abs(v_txt(2) - 3.) < util::EPS && std::abs(v_txt(3) - 4.) < util::EPS)) {
            report_error("Wrong elements read");
        }
    } catch (const util::error &) {
        report_error("Vector ascii: Cannot write to or read from file");
    }
    util::delete_file(filename);

    return (int)errors().size();
}

int vector_resize_test::execute()
{
    // test with double
    // ----------------
    vector<double> v_double(3);
    v_double.resize(5, double(100));

    // make the structure bigger
    if (v_double.rows() != 5) {
        report_error("Resize does not set new size");
    }
    if (!check_values(v_double, double(100))) {
        report_error("Values not correct after increase size of vector");
    }

    // make the structure smaller
    v_double.resize(4);
    if (v_double.rows() != 4) {
        report_error("Resize does not set new size");
    }
    if (!check_values(v_double, double(100))) {
        report_error("Values not correct after increase size of vector");
    }

    // test with float
    // ----------------
    vector<float> v_float(3);
    v_float.resize(5, float(100));

    // make the structure bigger
    if (v_float.rows() != 5) {
        report_error("Resize does not set new size");
    }
    if (!check_values(v_float, float(100))) {
        report_error("Values not correct after increase size of vector");
    }

    // make the structure smaller
    v_float.resize(4);
    if (v_float.rows() != 4) {
        report_error("Resize does not set new size");
    }
    if (!check_values(v_float, float(100))) {
        report_error("Values not correct after increase size of vector");
    }

    return (int)errors().size();
}

int vector_unary_assignment_test::execute()
{
    vector<int> a(3, 1);
    vector<int> b = -a;

    if (!check_values(b, -1)) {
        report_error("vector = -vector produced wrong values");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
