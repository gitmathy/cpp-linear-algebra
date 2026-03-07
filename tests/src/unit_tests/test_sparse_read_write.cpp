/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_sparse_read_write.cpp
/// @brief Implementation of test of write and read sparse matrices
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_sparse_read_write.hpp"
#include "la/sparse"
#include "la/util/file_io.hpp"

namespace la {
namespace test {

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
