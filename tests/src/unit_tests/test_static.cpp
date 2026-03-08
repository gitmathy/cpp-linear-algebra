/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_static.cpp
/// @brief Definition of testing static data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_static.hpp"
#include "la/static"
#include <memory>

namespace la {
namespace test {

void add_all_static(unit_test_collection &collection)
{
    collection.transfer("static_vector", std::make_unique<static_vector_add_sub_assignment_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_add_sub_ops_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_construct_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_copy_assignment_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_copy_ctor_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_inner_product_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_iterator_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_move_ctor_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_mult_assignment_test>());
    collection.transfer("static_vector", std::make_unique<static_vec_vec_mult_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_norms_test>());
    collection.transfer("static_vector", std::make_unique<static_vector_unary_assignment_test>());
}

int static_vector_add_sub_assignment_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b(2);

    a += b;
    if (!check_values(a, 3))
        report_error("static_vector += static_vector produced wrong values");

    a -= b;
    if (!check_values(a, 1))
        report_error("static_vector -= static_vector produced wrong values");

    return (int)errors().size();
}

int static_vector_add_sub_ops_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b(2);

    // use operator+ / - (operants) instead of in-place ops
    static_vector<int, 3> c = a + b;
    if (!check_values(c, 3)) {
        report_error("static_vector add (via +) produced wrong values");
    }

    static_vector<int, 3> d = b - a;
    if (!check_values(d, 1)) {
        report_error("static_vector sub (via -) produced wrong values");
    }

    // scalar + vector and vector + scalar
    static_vector<int, 3> s1 = a + 2;
    if (!check_values(s1, 3)) {
        report_error("static_vector add scalar (vector + scalar) produced wrong values");
    }

    static_vector<int, 3> s2 = 2 + a;
    if (!check_values(s2, 3)) {
        report_error("static_vector add scalar (scalar + vector) produced wrong values");
    }

    // adding/subtracting operants with vector
    static_vector<int, 3> op1 = a + (a + b); // vector + operant
    if (!check_values(op1, 4)) {
        report_error("static_vector add operant (vector + operant) produced wrong values");
    }

    static_vector<int, 3> op2 = (a + b) + a; // operant + vector
    if (!check_values(op2, 4)) {
        report_error("static_vector add operant (operant + vector) produced wrong values");
    }

    static_vector<int, 3> od = b - (a + a); // operant in subtraction
    if (!check_values(od, 0)) {
        report_error("static_vector sub operant (vector - operant) produced wrong values");
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

int static_vector_copy_assignment_test::execute()
{
    static_vector<int, 2> a = {2, 2};
    static_vector<int, 2> b;
    b = a;
    if (!check_values(b, 2)) {
        report_error("Copy assigned static_vector has incorrect values");
    }

    return (int)errors().size();
}

int static_vector_copy_ctor_test::execute()
{
    static_vector<double, 3> src;
    for (size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 2 + 1);

    static_vector<double, 3> dst(src); // copy-ctor
    if (dst.rows() != src.rows())
        report_error("Copy-constructed static_vector has incorrect size");
    for (size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - src(i)) > util::EPS) {
            report_error("Copy-constructed static_vector has incorrect value");
        }
    }

    return (int)errors().size();
}

int static_vector_inner_product_test::execute()
{
    static_vector<int, 3> a({1, 2, 3});
    static_vector<int, 3> b({4, 5, 6});

    int alpha = inner_product(a, b);

    if (alpha != 32) {
        report_error("inner_product produced wrong value for static vector");
    }
    return (int)errors().size();
}

int static_vector_iterator_test::execute()
{
    static_vector<size_type, 6> v;
    for (size_type i = 0; i < v.rows(); ++i)
        v(i) = i + 1; // 1..6

    const static_vector<size_type, 6> cv = v; // use copy / const access
    // iterate with const-iterator and verify values
    size_type pos = 0;
    for (static_vector<size_type, 6>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Vector const-iterator reads incorrect value");

    // test algorithm on const-iterators (std::accumulate)
    size_type sum = std::accumulate(cv.begin(), cv.end(), size_type(0));
    const size_type expect = 1 + 2 + 3 + 4 + 5 + 6;
    if (sum != expect)
        report_error("std::accumulate over const-iterator produced wrong sum");

    return (int)errors().size();
}

int static_vector_move_ctor_test::execute()
{
    static_vector<double, 4> src;
    for (size_type i = 0; i < src.rows(); ++i) {
        src(i) = static_cast<double>(i * 10 + 1);
    }

    static_vector<double, 4> dst(std::move(src));
    if (dst.rows() != 4) {
        report_error("Moved-to vector has incorrect size");
    }

    for (size_type i = 0; i < dst.rows(); ++i) {
        if (std::abs(dst(i) - static_cast<double>(i * 10 + 1)) > util::EPS) {
            report_error("Moved-to vector has incorrect value");
        }
    }

    return (int)errors().size();
}

int static_vector_mult_assignment_test::execute()
{

    static_vector<int, 2> x = {2, 3};
    static_vector<int, 2> y = {3, 2};
    y *= x;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector");
    }
    if (!check_values(y, 6)) {
        report_error("Wrong element for multiplying static_vectors");
    }

    y *= 2;
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector with scalar");
    }
    if (!check_values(y, 12)) {
        report_error("Wrong element for multiplying static_vector with a scalar");
    }

    x *= (y * 2);
    if (!(y.rows() == 2)) {
        report_error("Wrong size when multiplying static_vector with operant");
    }
    if (!(x(0) == 48 && x(1) == 72)) {
        report_error("Wrong element for multiplying static_vector with a operant");
    }

    return (int)errors().size();
}

int static_vec_vec_mult_test::execute()
{
    static_vector<int, 2> x = {3, 4};
    static_vector<int, 2> y = {4, 3};
    static_vector<int, 2> z = (x * y);
    static_vector<int, 2> z_scalar = (x * y) * 2;

    if (!(z.rows() == 2)) {
        report_error("Wrong size of static_vector*static_vector");
    }
    if (!check_values(z, 12)) {
        report_error("Wrong elements for static_vector * static_vector");
    }

    if (!(z_scalar.rows() == 2)) {
        report_error("Wrong size of (static_vector+static_vector) * scalar");
    }
    if (!check_values(z, 24)) {
        report_error("Wrong elements for (static_vector+static_vector) * scalar");
    }

    return (int)errors().size();
}

int static_vector_norms_test::execute()
{
    static_vector<double, 4> v = {-1.0, 2.0, -2.0, 3.0};

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

int static_vector_unary_assignment_test::execute()
{
    static_vector<int, 3> a(1);
    static_vector<int, 3> b = -a;

    if (!check_values(b, -1)) {
        report_error("static_vector = -static_vector produced wrong values");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
