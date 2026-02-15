#include "includes/test_matrix_copy_assignment.hpp"
#include "../includes/matrix.hpp"
#include "../includes/types.hpp"

namespace la_test
{

bool matrix_copy_assignment_test::execute()
{
    bool result = true;

    la::matrix<double> src(2, 3);
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            src(i, j) = static_cast<double>(i * src.cols() + j + 1);

    la::matrix<double> dst(1, 1, double(0));
    dst = src; // copy-assign

    if (dst.rows() != src.rows() || dst.cols() != src.cols())
    {
        result = false;
        p_logger.log("Copy-assigned matrix has incorrect dimensions", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
        for (la::size_type j = 0; j < dst.cols(); ++j)
            if (double(dst(i, j) - src(i, j)) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "Copy-assigned matrix has incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }

    // source must remain unchanged
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            if (double(src(i, j) - static_cast<double>(i * src.cols() + j + 1)) != 0.0)
            {
                result = false;
                p_logger.log("Source matrix changed after copy-assignment", ERROR);
                break;
            }

    // other types quick check
    la::matrix<int> si(2, 2, int(3));
    la::matrix<int> di(1, 1);
    di = si;
    if (di.rows() != si.rows() || di.cols() != si.cols() || di(1, 1) != 3)
        result = false;

    if (!result)
    {
        std::stringstream strs;
        strs << "matrix<> error in copy assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
