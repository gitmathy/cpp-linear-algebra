#include "tests/includes/unit_tests/test_construct.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"

namespace la {
namespace test {

int vector_construct_test::execute()
{
    // test with double
    // ----------------
    la::vector<double> *vd = new la::vector<double>(2, 3.14);
    if (vd->rows() != 2) {
        report_error("Constructor set wrong sizes of double vector");
    }
    if (!check_values(*vd, 3.14)) {
        report_error("Values not correct after constructing a double vector");
    }
    delete vd;

    // test with float
    // ----------------
    la::vector<float> *vf = new la::vector<float>(2, 3.14f);
    if (vf->rows() != 2) {
        report_error("Constructor set wrong sizes of float matrix");
    }
    if (!check_values(*vf, 3.14)) {
        report_error("Values not correct after constructing a float vector");
    }
    delete vf;
    return (int)errors().size();

    // test with initializer list
    // ----------------
    la::vector<int> *vi = new la::vector<int>({1, 2});
    if (vi->rows() != 2) {
        report_error("Constructor by initializer lis set wrong size of vector");
    }
    if (!((*vi)(0) == 1 && (*vi)(1) == 2)) {
        report_error("Values set by initializer list are not correct");
    }

    delete vi;
}

int matrix_construct_test::execute()
{
    // test with double
    // ----------------
    la::matrix<double> *md = new la::matrix<double>(2, 3, 3.14);
    if (md->rows() != 2 || md->cols() != 3) {
        report_error("Constructor set wrong sizes of double matrix");
    }
    if (!check_values(*md, 3.14)) {
        report_error("Values not correct after constructing a double matrix");
    }
    delete md;

    // test with float
    // ----------------
    la::matrix<float> *mf = new la::matrix<float>(2, 3, 3.14f);
    if (mf->rows() != 2 || mf->cols() != 3) {
        report_error("Constructor set wrong sizes of float matrix");
    }
    if (!check_values(*mf, 3.14)) {
        report_error("Values not correct after constructing a float matrix");
    }
    delete mf;

    // test with initializer list
    // ----------------
    la::matrix<int> *mi = new la::matrix<int>({{1, 2}, {3, 4}});
    if (mi->rows() != 2 || mi->cols() != 2) {
        report_error("Constructor by initializer lis set wrong size of matrix");
    }
    if (!((*mi)(0, 0) == 1 && (*mi)(0, 1) == 2) && (*mi)(1, 0) == 3 && (*mi)(1, 1) == 4) {
        report_error("Matrix values set by initializer list are not correct");
    }
    delete mi;

    la::matrix<int, COLUMN_WISE> *mi_col = new la::matrix<int, COLUMN_WISE>({{1, 2}, {3, 4}});
    if (mi_col->rows() != 2 || mi_col->cols() != 2) {
        report_error("Constructor by initializer lis set wrong size of matrix");
    }
    if (!((*mi_col)(0, 0) == 1 && (*mi_col)(0, 1) == 2) && (*mi_col)(1, 0) == 3 &&
        (*mi_col)(1, 1) == 4) {
        report_error("Matrix values set by initializer list are not correct");
    }
    delete mi_col;

    return (int)errors().size();
}

} // namespace test
} // namespace la
