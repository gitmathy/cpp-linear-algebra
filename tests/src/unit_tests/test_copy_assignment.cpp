/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_copy_assignment.cpp
/// @brief Implementation of test of copy assignment
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_copy_assignment.hpp"
#include "la/dense"
#include "la/static"
#include "la/util/constants.hpp"

namespace la {
namespace test {

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

} // namespace test
} // namespace la
