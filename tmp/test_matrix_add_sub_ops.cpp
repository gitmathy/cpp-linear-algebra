#include "includes/test_matrix_add_sub_ops.hpp"
#include "../includes/la.hpp"
#include "../includes/matrix.hpp"
#include "../includes/types.hpp"

namespace la_test
{

bool matrix_add_sub_ops_test::execute()
{
    bool result = true;

    la::matrix<double> a(2, 3), b(2, 3);
    for (la::size_type i = 0; i < a.rows(); ++i)
        for (la::size_type j = 0; j < a.cols(); ++j)
        {
            a(i, j) = static_cast<double>(i * a.cols() + j + 2);       // some values
            b(i, j) = static_cast<double>((i * a.cols() + j + 1) * 5); // scaled values
        }

    la::matrix<double> a_orig(a.rows(), a.cols());
    a_orig = a;
    la::matrix<double> b_orig(b.rows(), b.cols());
    b_orig = b;

    la::matrix<double> sum = a + b;
    for (la::size_type i = 0; i < sum.rows(); ++i)
        for (la::size_type j = 0; j < sum.cols(); ++j)
            if (double(sum(i, j) - (a_orig(i, j) + b_orig(i, j))) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+ produced incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }

    if (double(a(0, 0) - a_orig(0, 0)) != 0.0 || double(b(0, 0) - b_orig(0, 0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by +", ERROR);
    }

    la::matrix<double> diff = a - b;
    for (la::size_type i = 0; i < diff.rows(); ++i)
        for (la::size_type j = 0; j < diff.cols(); ++j)
            if (double(diff(i, j) - (a_orig(i, j) - b_orig(i, j))) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "- produced incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }

    if (double(a(0, 0) - a_orig(0, 0)) != 0.0 || double(b(0, 0) - b_orig(0, 0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by -", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "matrix<> error in add/sub operators";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
