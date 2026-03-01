/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_lu_decomp.cpp
/// @brief Implementation of test of lu decomposition
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_lu_decomp.hpp"
#include "la/dense"
#include "la/util/constants.hpp"

namespace la {
namespace test {

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

} // namespace test
} // namespace la
