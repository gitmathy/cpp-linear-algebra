#include "includes/test_matrix_construct.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_construct_test::execute()
{
    bool result = true;

    // double
    la::matrix<double> *md = new la::matrix<double>(2, 3);
    if (md->rows() != 2 || md->cols() != 3)
    {
        p_logger.log("Incorrect dimensions from constructor (double)", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < md->rows(); ++i)
        for (la::size_type j = 0; j < md->cols(); ++j)
            if ((*md)(i, j) != 0.0)
            {
                p_logger.log("Default constructor did not initialize to zero (double)", ERROR);
                result = false;
                break;
            }
    delete md;

    la::matrix<double> *mdv = new la::matrix<double>(2, 3, double(2));
    if (mdv->rows() != 2 || mdv->cols() != 3)
    {
        p_logger.log("Incorrect dimensions from value-constructor (double)", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < mdv->rows(); ++i)
        for (la::size_type j = 0; j < mdv->cols(); ++j)
            if ((*mdv)(i, j) != 2.0)
            {
                p_logger.log("Value-constructor did not set provided value (double)", ERROR);
                result = false;
                break;
            }
    delete mdv;

    // float
    la::matrix<float> *mf = new la::matrix<float>(2, 2, float(5));
    if (mf->rows() != 2 || mf->cols() != 2)
    {
        p_logger.log("Incorrect dimensions from constructor (float)", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < mf->rows(); ++i)
        for (la::size_type j = 0; j < mf->cols(); ++j)
            if ((*mf)(i, j) != 5.0f)
            {
                p_logger.log("Value-constructor did not set provided value (float)", ERROR);
                result = false;
                break;
            }
    delete mf;

    // int
    la::matrix<int> *mi = new la::matrix<int>(3, 1, int(7));
    if (mi->rows() != 3 || mi->cols() != 1)
    {
        p_logger.log("Incorrect dimensions from constructor (int)", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < mi->rows(); ++i)
        for (la::size_type j = 0; j < mi->cols(); ++j)
            if ((*mi)(i, j) != 7)
            {
                p_logger.log("Value-constructor did not set provided value (int)", ERROR);
                result = false;
                break;
            }
    delete mi;

    if (!result)
        p_errors.push_back("matrix<> error in constructor");

    return result;
}

} // namespace la_test
