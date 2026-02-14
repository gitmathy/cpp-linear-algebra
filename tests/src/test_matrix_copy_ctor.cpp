#include "includes/test_matrix_copy_ctor.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_copy_constructor_test::execute()
{
    bool result = true;

    la::matrix<double> src(2, 3);
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            src(i, j) = static_cast<double>(i * src.cols() + j + 1);

    la::matrix<double> dst(src); // copy ctor
    if (dst.rows() != src.rows() || dst.cols() != src.cols())
    {
        p_logger.log("Copy-constructed matrix has incorrect dimensions", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
        for (la::size_type j = 0; j < dst.cols(); ++j)
            if (dst(i, j) != src(i, j))
            {
                p_logger.log("Copy-constructed matrix contains incorrect values", ERROR);
                result = false;
                break;
            }

    // ensure source unchanged
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            if (src(i, j) != static_cast<double>(i * src.cols() + j + 1))
            {
                p_logger.log("Source changed after copy-construction", ERROR);
                result = false;
                break;
            }

    // other types
    la::matrix<int> si(2, 2, int(3));
    la::matrix<int> di(si);
    if (di(1, 1) != 3)
    {
        p_logger.log("Copy-constructed matrix<int> incorrect", ERROR);
        result = false;
    }

    if (!result)
        p_errors.push_back("matrix<> error in copy constructor");

    return result;
}

} // namespace la_test
