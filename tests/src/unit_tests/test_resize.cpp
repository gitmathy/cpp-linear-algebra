#include "tests/includes/unit_tests/test_resize.hpp"
#include "includes/matrix.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"

namespace la
{
namespace test
{

int vector_resize_test::execute()
{
    // test with double
    // ----------------
    la::vector<double> v_double(3);
    v_double.resize(5, double(100));

    // make the structure bigger
    if (v_double.rows() != 5)
        report_error("Resize does not set new size");
    if (!check_values(v_double, double(100)))
        report_error("Values not correct after increase size of vector");

    // make the structure smaller
    v_double.resize(4);
    if (v_double.rows() != 4)
        report_error("Resize does not set new size");
    if (!check_values(v_double, double(100)))
        report_error("Values not correct after increase size of vector");

    // test with float
    // ----------------
    la::vector<float> v_float(3);
    v_float.resize(5, float(100));

    // make the structure bigger
    if (v_float.rows() != 5)
        report_error("Resize does not set new size");
    if (!check_values(v_float, float(100)))
        report_error("Values not correct after increase size of vector");

    // make the structure smaller
    v_float.resize(4);
    if (v_float.rows() != 4)
        report_error("Resize does not set new size");
    if (!check_values(v_float, float(100)))
        report_error("Values not correct after increase size of vector");

    return (int)errors().size();
}

int matrix_resize_test::execute()
{
    // test with double
    // ----------------
    la::matrix<double> a_double(1, 1);
    a_double.resize(5, 4, double(100));

    // make the structure bigger
    if (a_double.rows() != 5)
        report_error("Resize does not set new rows");
    if (a_double.cols() != 4)
        report_error("Resize does not set new columns");
    if (!check_values(a_double, double(100)))
        report_error("Values not correct after increase size of matrix");

    // make the structure smaller
    a_double.resize(4, 3);
    if (a_double.rows() != 4)
        report_error("Resize does not set new rows");
    if (a_double.cols() != 3)
        report_error("Resize does not set new columns");
    if (!check_values(a_double, double(100)))
        report_error("Values not correct after increase size of matrix");

    // test with float
    // ----------------
    la::matrix<float> a_float(1, 1);
    a_float.resize(5, 4, float(100));

    // make the structure bigger
    if (a_float.rows() != 5)
        report_error("Resize does not set new rows");
    if (a_float.cols() != 4)
        report_error("Resize does not set new columns");
    if (!check_values(a_float, float(100)))
        report_error("Values not correct after increase size of matrix");

    // make the structure smaller
    a_float.resize(4, 3);
    if (a_float.rows() != 4)
        report_error("Resize does not set new rows");
    if (a_float.cols() != 3)
        report_error("Resize does not set new columns");
    if (!check_values(a_float, float(100)))
        report_error("Values not correct after increase size of matrix");

    return (int)errors().size();
}

} // namespace test
} // namespace la
