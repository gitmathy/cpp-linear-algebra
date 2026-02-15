#include "includes/test_matrix_move_assignment.hpp"
#include "../includes/matrix.hpp"
#include "../includes/types.hpp"

namespace la_test
{

bool matrix_move_assignment_test::execute()
{
    bool result = true;

    la::matrix<double> src(2, 3);
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            src(i, j) = static_cast<double>(i * src.cols() + j + 1);

    la::matrix<double> dst(1, 1, double(9));
    dst = std::move(src);

    if (dst.rows() != 2 || dst.cols() != 3)
    {
        result = false;
        p_logger.log("Move-assigned matrix has incorrect dimensions", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
        for (la::size_type j = 0; j < dst.cols(); ++j)
            if (double(dst(i, j) - static_cast<double>(i * dst.cols() + j + 1)) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "Move-assigned matrix has incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }

    if (src.rows() != 0 || src.cols() != 0)
    {
        result = false;
        p_logger.log("Moved-from matrix not left empty after move-assignment", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "matrix<> error in move assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
