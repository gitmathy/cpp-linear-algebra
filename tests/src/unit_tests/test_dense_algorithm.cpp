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
    matrix<double> A({{0, 2, 1}, {1, 1, 2}, {2, 1, 1}});
    const vector<double> b({4, 6, 7});

    la::algorithm::lu_decomposition<double> lu(A);
    vector<double> x = lu.solve(b);

    if (x.rows() != 3) {
        report_error("wrong size of LU decomposition solve");
    }

    if (!(std::abs(x(0) - 2.2) < util::EPS && std::abs(x(1) - 1.4) < util::EPS &&
          std::abs(x(2) - 1.2) < util::EPS)) {
        report_error("lu decomposition solve (row) produced wrong results");
    }
    return (int)errors().size();
}

int mat_mat_mult_test::execute()
{
    matrix<int> A = {{1, 2, 3}, {4, 5, 6}};
    matrix<int> B = {{2, 3}, {2, 3}, {2, 3}};

    matrix<int> C = A * B;
    if (!(C.rows() == 2 && C.cols() == 2)) {
        report_error("Wrong size of matrix*matrix");
    }
    if (!(C(0, 0) == 11 && C(0, 1) == 18 && C(1, 0) == 30 && C(1, 1) == 45)) {
        report_error("Wrong size of matrix*matrix");
    }

    matrix<int> C_scalar = (A * 2);
    if (!(C_scalar.rows() == 2 && C_scalar.cols() == 3)) {
        report_error("Wrong size of matrix*scalar");
    }
    if (!(C_scalar(0, 0) == 2 && C_scalar(0, 1) == 4 && C_scalar(0, 2) == 6 &&
          C_scalar(1, 0) == 8 && C_scalar(1, 1) == 10 && C_scalar(1, 2) == 12)) {
        report_error("Wrong size of matrix*scalar");
    }

    C_scalar = (2 * A);
    if (!(C_scalar(0, 0) == 2 && C_scalar(0, 1) == 4 && C_scalar(0, 2) == 6 &&
          C_scalar(1, 0) == 8 && C_scalar(1, 1) == 10 && C_scalar(1, 2) == 12)) {
        report_error("Wrong size of scalar * matrix");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
