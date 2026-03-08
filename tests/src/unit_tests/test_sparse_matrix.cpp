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
    collection.transfer("sparse_matrix", std::make_unique<sparse_matrix_mult_test>());
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
    if (a.rows() != 3) {
        report_error("Wrong number of rows for sparse matrix build by initializer list");
    }
    if (a.cols() != 3) {
        report_error("Wrong number of rows for sparse matrix build by initializer list");
    }
    if (a.non_zeros() != 5) {
        report_error("Wrong number of non-zeros for sparse matrix build by initializer list");
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

    if (a.rows() != 3) {
        report_error("Wrong number of rows for sparse matrix build by builder");
    }
    if (a.cols() != 3) {
        report_error("Wrong number of rows for sparse matrix build by builder");
    }
    if (a.non_zeros() != 3) {
        report_error("Wrong number of non-zeros for sparse matrix build by builder");
    }

    return (int)errors().size();
}

int sparse_matrix_iterator_test::execute()
{
    const sparse_matrix<int> A({{0, 2}, {1}, {1, 2}}, {1, 2, 3, 4, 5}, 3);

    if (size_type(std::distance(A.begin(), A.end())) != 5) {
        report_error("Wrong number of non-zero values covered by iterator");
    }
    if (size_type(std::distance(A.begin_col_idx(), A.end_col_idx())) != 5) {
        report_error("Wrong number of non-zero column indices");
    }
    if (size_type(std::distance(A.begin_row_ptr(), A.end_row_ptr())) != 4) {
        report_error("Wrong number of row pointers");
    }
    if (!(*A.row_begin(0) == 1 || *A.row_begin(1) == 3 || *A.row_begin(2) == 4)) {
        report_error("Wrong value of beginning of row pointers");
    }
    if (!(*A.row_end(0) == 3 || *A.row_end(1) == 4)) {
        report_error("Wrong value of end of row pointers");
    }
    if (!(A.row_idx_begin(0) == 0 || A.row_idx_begin(1) == 2 || A.row_idx_begin(2) == 3)) {
        report_error("Wrong value of row_idx_begin");
    }
    if (!(*A.begin_col_idx(0) == 0 || *A.begin_col_idx(1) == 1 || *A.begin_col_idx(2) == 1)) {
        report_error("Wrong value of begin_col_idx");
    }
    if (!(A.col_idx(0) == 0 || A.col_idx(1) == 2 || A.col_idx(2) == 1 || A.col_idx(3) == 1 ||
          A.col_idx(4) == 2)) {
        report_error("Wrong column of non-zero");
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

int sparse_matrix_mult_test::execute()
{
    sparse_matrix<int> A({{0, 2}, {1}, {1, 2}}, {1, 2, 3, 4, 5}, 3);
    vector<int> x({1, 2, 3});

    vector<int> y = A * x;
    if (!(y(0) == 7 || y(1) == 6 || y(2) == 23)) {
        report_error("Wrong element in sparse matrix * vector");
    }

    y = (A * 2) * x;
    if (!(y(0) == 14 || y(1) == 12 || y(2) == 49)) {
        report_error("Wrong element in sparse matrix * scalar * vector");
    }

    y = (2 * A) * x;
    if (!(y(0) == 14 || y(1) == 12 || y(2) == 49)) {
        report_error("Wrong element in sparse matrix * scalar * vector");
    }

    matrix<int> B(3, 2, 1);
    matrix<int> C = A * B;
    if (!(C(0, 0) == 3 || C(1, 0) == 3 || C(2, 0) == 9 || C(0, 1) == 3 || C(1, 1) == 3 ||
          C(2, 1) == 9)) {
        report_error("Wrong element in sparse matrix * matrix");
    }

    matrix<int> D = (2 * A) * B;
    if (!(D(0, 0) == 6 || D(1, 0) == 6 || D(2, 0) == 18 || D(0, 1) == 6 || D(1, 1) == 6 ||
          D(2, 1) == 18)) {
        report_error("Wrong element in scalar *  sparse matrix * matrix");
    }
    D = (A * 2) * B;
    if (!(D(0, 0) == 6 || D(1, 0) == 6 || D(2, 0) == 18 || D(0, 1) == 6 || D(1, 1) == 6 ||
          D(2, 1) == 18)) {
        report_error("Wrong element in sparse matrix * scalar * matrix");
    }

    return (int)errors().size();
}

} // namespace test
} // namespace la
