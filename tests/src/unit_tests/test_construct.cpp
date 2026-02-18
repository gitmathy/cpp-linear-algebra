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
    if (vd->rows() != 2)
        report_error("Constructor set wrong sizes of double vector");
    if (!check_values(*vd, 3.14))
        report_error("Values not correct after constructing a double vector");
    delete vd;

    // test with float
    // ----------------
    la::vector<float> *vf = new la::vector<float>(2, 3.14f);
    if (vf->rows() != 2)
        report_error("Constructor set wrong sizes of float matrix");
    if (!check_values(*vf, 3.14))
        report_error("Values not correct after constructing a float vector");
    delete vf;
    return (int)errors().size();
}

int matrix_construct_test::execute()
{
    // test with double
    // ----------------
    la::matrix<double> *md = new la::matrix<double>(2, 3, 3.14);
    if (md->rows() != 2 || md->cols() != 3)
        report_error("Constructor set wrong sizes of double matrix");
    if (!check_values(*md, 3.14))
        report_error("Values not correct after constructing a double matrix");
    delete md;

    // test with float
    // ----------------
    la::matrix<float> *mf = new la::matrix<float>(2, 3, 3.14f);
    if (mf->rows() != 2 || mf->cols() != 3)
        report_error("Constructor set wrong sizes of float matrix");
    if (!check_values(*mf, 3.14))
        report_error("Values not correct after constructing a float matrix");
    delete mf;
    return (int)errors().size();
}

} // namespace test
} // namespace la
