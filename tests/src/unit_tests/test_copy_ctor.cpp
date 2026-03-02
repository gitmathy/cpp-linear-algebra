/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_copy_ctor.cpp
/// @brief Implementation of test of copy constructor
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_copy_ctor.hpp"
#include "la/dense"
#include "la/static"
#include "la/util/constants.hpp"

namespace la {
namespace test {

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

} // namespace test
} // namespace la
