#include "includes/test_matrix_move_ctor.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_move_constructor_test::execute()
{
    bool result = true;

    la::matrix<double> src(2, 3);
    for (la::size_type i = 0; i < src.rows(); ++i)
        for (la::size_type j = 0; j < src.cols(); ++j)
            src(i, j) = static_cast<double>(i * src.cols() + j + 1);

    la::matrix<double> dst(std::move(src));
    if (dst.rows() != 2 || dst.cols() != 3)
    {
        p_logger.log("Moved-to matrix has incorrect dimensions", ERROR);
        result = false;
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
        for (la::size_type j = 0; j < dst.cols(); ++j)
            if (dst(i, j) != static_cast<double>(i * dst.cols() + j + 1))
            {
                p_logger.log("Moved-to matrix has incorrect value", ERROR);
                result = false;
                break;
            }

    // moved-from should be left in empty state
    if (src.rows() != 0 || src.cols() != 0)
    {
        p_logger.log("Moved-from matrix not left empty after move-constructor", ERROR);
        result = false;
    }

    // other types
    la::matrix<int> srci(1, 2, int(9));
    la::matrix<int> dsti(std::move(srci));
    if (dsti.rows() != 1 || dsti.cols() != 2 || dsti(0, 1) != 9)
    {
        p_logger.log("Move-constructed matrix<int> incorrect", ERROR);
        result = false;
    }

    if (!result)
        p_errors.push_back("matrix<> error in move constructor");

    return result;
}

} // namespace la_test
