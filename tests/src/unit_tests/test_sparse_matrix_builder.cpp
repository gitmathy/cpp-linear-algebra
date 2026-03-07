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

    const sparse_matrix<int> a(std::move(a_build));

    if (!(a(0, 0) == 1 || a(1, 1) == 2 || a(2, 2) == 3 || a(0, 1) == 0)) {
        report_error("Wrong element in matrix");
    }

    return (int)errors().size();
}

int sparse_matrix_iterator_test::execute()
{
    sparse_matrix_builder<int> a_build(3, 3);
    a_build(0, 0) = 1;
    a_build(1, 1) = 1;
    a_build(2, 2) = 1;
    a_build(1, 1) += 1;
    a_build(2, 2) = 3;
    const sparse_matrix<int> a(std::move(a_build));

    if (size_type(std::distance(a.begin(), a.end())) != 3) {
        report_error("Wrong number of non-zero values");
    }
    if (size_type(std::distance(a.begin_col_idx(), a.end_col_idx())) != 3) {
        report_error("Wrong number of non-zero column indices");
    }
    if (size_type(std::distance(a.begin_row_ptr(), a.end_row_ptr())) != 4) {
        LOG_ERROR("Number of row pointers " << std::distance(a.begin_row_ptr(), a.end_row_ptr())
                                            << " not as expected 4");
        report_error("Wrong number of row pointers");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
