#include "includes/test_matrix_resize.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_resize_test::execute()
{
    bool result = true;

    la::matrix<double> m(2, 3, 1.0);
    m.resize(3, 4, 2.0);
    if (m.rows() != 3 || m.cols() != 4)
    {
        p_logger.log("Incorrect dimensions after resize (double)", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < m.rows(); ++i)
        for (la::size_type j = 0; j < m.cols(); ++j)
            if (m(i, j) != 2.0)
            {
                p_logger.log("Resize did not set all values to provided default (double)", ERROR);
                result = false;
                break;
            }

    // shrink
    m.resize(1, 1, 3.0);
    if (m.rows() != 1 || m.cols() != 1 || m(0, 0) != 3.0)
    {
        p_logger.log("Resize (shrink) did not set dimensions/value correctly", ERROR);
        result = false;
    }

    // other types
    la::matrix<float> mf(2, 2, float(4));
    mf.resize(3, 3, float(1));
    for (la::size_type i = 0; i < mf.rows(); ++i)
        for (la::size_type j = 0; j < mf.cols(); ++j)
            if (mf(i, j) != 1.0f)
            {
                p_logger.log("Resize did not set all values to provided default (float)", ERROR);
                result = false;
                break;
            }

    la::matrix<int> mi(1, 2, int(9));
    mi.resize(2, 2, int(5));
    for (la::size_type i = 0; i < mi.rows(); ++i)
        for (la::size_type j = 0; j < mi.cols(); ++j)
            if (mi(i, j) != 5)
            {
                p_logger.log("Resize did not set all values to provided default (int)", ERROR);
                result = false;
                break;
            }

    if (!result)
        p_errors.push_back("matrix<> error in resize");

    return result;
}

} // namespace la_test
