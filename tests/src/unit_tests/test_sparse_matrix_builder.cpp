/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_sparse_matrix_builder.cpp
/// @brief Implementation of test of copy constructor
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_sparse_matrix_builder.hpp"
#include "la/sparse"

namespace la {
namespace test {

int sparse_matrix_builder_insert_test::execute()
{
    sparse_matrix_builder<int> a_build(3, 3);

    a_build(0, 0) = 1;
    a_build(1, 1) = 1;
    a_build(2, 2) = 1;
    a_build(1, 1) += 1;
    a_build(2, 2) = 3;

    if (!(a_build(0, 0) == 1 || a_build(1, 1) == 2 || a_build(2, 2) == 3 || a_build(0, 1) == 0)) {
        report_error("Wrong element in builder");
    }

    return (int)errors().size();
}

int sparse_matrix_builder_assemble_test::execute()
{
    sparse_matrix_builder<int> a_build(3, 3);

    a_build(0, 0) = 1;
    a_build(1, 1) = 1;
    a_build(2, 2) = 1;
    a_build(1, 1) += 1;
    a_build(2, 2) = 3;

    sparse_matrix<int> a;
    a_build.assemble(a);

    if (!(a(0, 0) == 1 || a(1, 1) == 2 || a(2, 2) == 3 || a(0, 1) == 0)) {
        report_error("Wrong element in matrix");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
