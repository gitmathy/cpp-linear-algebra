#include "tests/includes/unit_tests/test_read_write.hpp"
#include "includes/assert.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include <cmath>
#include <filesystem>
#include <iostream>

namespace la {
namespace test {

bool delete_file(const std::string &filename)
{
    try {
        if (!std::filesystem::remove(filename)) {
            throw error("Cannot delete temporary file", "file_error");
        }
        return false;
    } catch (const std::filesystem::filesystem_error &) {
        LOG_ERROR("Failed to delete temporary file");
        throw error("Cannot delete temporary file", "file_error");
    }
}

int vector_read_write_test::execute()
{
    la::vector<double> v({1., 2., 3., 4.});

    std::string filename = "tmp_read_vector_testing.tst";

    // Test binary write and read
    try {
        v.to_file(filename, true);
        la::vector<double> v_bin;
        v_bin.from_file(filename, true);
        if (!(v_bin.rows() == 4)) {
            report_error("Wrong size of read vector");
        }
        if (!(std::abs(v_bin(0) - 1.) < LA_EPS && std::abs(v_bin(1) - 2.) < LA_EPS &&
              std::abs(v_bin(2) - 3.) < LA_EPS && std::abs(v_bin(3) - 4.) < LA_EPS)) {
            report_error("Wrong elements read");
        }
    } catch (const error &) {
        report_error("Vector binary: Cannot write to or read from file");
    }

    delete_file(filename);

    // Test ascii write and read
    v.to_file(filename, false);
    la::vector<double> v_txt;
    try {
        v_txt.from_file(filename, false);
        if (!(v_txt.rows() == 4)) {
            report_error("Wrong size of read vector");
        }
        if (!(std::abs(v_txt(0) - 1.) < LA_EPS && std::abs(v_txt(1) - 2.) < LA_EPS &&
              std::abs(v_txt(2) - 3.) < LA_EPS && std::abs(v_txt(3) - 4.) < LA_EPS)) {
            report_error("Wrong elements read");
        }
    } catch (const error &) {
        report_error("Vector ascii: Cannot write to or read from file");
    }
    delete_file(filename);

    return (int)errors().size();
}

int matrix_read_write_test::execute()
{
    la::matrix<float, ROW_WISE> A_row({{1., 2., 3.}, {4., 5., 6.}});
    std::string filename = "tmp_read_matrix_testing.tst";

    // Test binary write and read
    try {
        A_row.to_file(filename, true);
        la::matrix<float, ROW_WISE> A_row_bin;
        A_row_bin.from_file(filename, true);
        if (!(A_row_bin.rows() == 2 && A_row_bin.cols() == 3)) {
            report_error("Wrong size of read matrix");
        }
        if (!(std::abs(A_row_bin(0, 0) - 1.) < LA_EPS && std::abs(A_row_bin(0, 1) - 2.) < LA_EPS &&
              std::abs(A_row_bin(0, 2) - 3.) < LA_EPS && std::abs(A_row_bin(1, 0) - 4.) < LA_EPS &&
              std::abs(A_row_bin(1, 1) - 5.) < LA_EPS && std::abs(A_row_bin(1, 2) - 6.) < LA_EPS)) {
            report_error("Wrong elements read");
        }
        A_row_bin.resize(0, 0);
    } catch (const error &) {
        report_error("Matrix binary ascii: Cannot write to or read from file");
    }
    delete_file(filename);

    // Test ascii write and read
    try {
        A_row.to_file(filename, false);
        la::matrix<float, ROW_WISE> A_row_txt;
        A_row_txt.from_file(filename, false);
        if (!(A_row_txt.rows() == 2 && A_row_txt.cols() == 3)) {
            report_error("Wrong size of read matrix");
        }
        if (!(std::abs(A_row_txt(0, 0) - 1.) < LA_EPS && std::abs(A_row_txt(0, 1) - 2.) < LA_EPS &&
              std::abs(A_row_txt(0, 2) - 3.) < LA_EPS && std::abs(A_row_txt(1, 0) - 4.) < LA_EPS &&
              std::abs(A_row_txt(1, 1) - 5.) < LA_EPS && std::abs(A_row_txt(1, 2) - 6.) < LA_EPS)) {
            report_error("Wrong elements read");
        }
        A_row_txt.resize(0, 0);
    } catch (const error &) {
        report_error("Matrix row ascii: Cannot write to or read from file");
    }
    delete_file(filename);

    return (int)errors().size();
}

} // namespace test
} // namespace la
