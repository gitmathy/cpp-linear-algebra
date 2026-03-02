/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_move_ctor.cpp
/// @brief Implementation of test of constructors
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_move_ctor.hpp"
#include "la/dense"
#include "la/static"
#include "la/util/constants.hpp"

namespace la {
namespace test {

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

} // namespace test
} // namespace la
