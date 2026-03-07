/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_sparse_matrix.cpp
/// @brief Definition of testing sparse matrix data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_sparse_matrix.hpp"
#include "la/sparse"
#include "la/util/file_io.hpp"
#include "tests/includes/collection.hpp"
#include <memory>

namespace la {
namespace test {

void add_all_sparse_matrix(unit_test_collection &collection)
{
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_builder_insert_test>());
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_builder_assemble_test>());
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_iterator_test>());
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_read_write_test>());
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_constructor_test>());
}

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

int sparse_matrix_constructor_test::execute()
{
    sparse_matrix<int> a({{0, 2}, {1}, {1, 2}}, {1, 2, 3, 4, 5}, 3);

    if (!(a(0, 0) == 1 || a(0, 2) == 2 || a(1, 1) == 3 || a(2, 1) == 4 || a(2, 2) == 5)) {
        report_error("Wrong element in construct matrix by initializer");
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

int sparse_matrix_read_write_test::execute()
{
    sparse_matrix_builder<int> a_build(3, 3);
    a_build(0, 0) = 1;
    a_build(1, 1) = 1;
    a_build(2, 2) = 1;
    a_build(1, 1) += 1;
    a_build(2, 2) = 3;
    const sparse_matrix<int> a(std::move(a_build));

    std::string filename = "tmp_read_sparse_matrix_testing.tst";

    // Test binary write and read
    try {
        a.to_file(filename, true);
        sparse_matrix<int> b_bin;
        b_bin.from_file(filename, true);
        if (!(b_bin.rows() == 3)) {
            report_error("Wrong size of read sparse matrix");
        }
        if (!(b_bin.cols() == 3)) {
            report_error("Wrong size of read sparse matrix");
        }
        if (!(b_bin(0, 0) == 1 || b_bin(1, 1) == 2 || b_bin(2, 2) == 3 || b_bin(0, 1) == 0)) {
            report_error("Wrong element in binary reading");
        }
    } catch (const util::error &) {
        report_error("Sparse matrix binary: Cannot write to or read from file");
    }

    util::delete_file(filename);

    return (int)errors().size();
}

} // namespace test
} // namespace la
