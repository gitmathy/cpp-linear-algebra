#include "includes/test_matrix_add_sub_assignment.hpp"
#include "../includes/la.hpp"
#include "../includes/matrix.hpp"
#include "../includes/types.hpp"

namespace la_test
{

bool matrix_add_sub_assignment_test::execute()
{
    bool result = true;

    la::matrix<double> a(2, 3), b(2, 3);
    for (la::size_type i = 0; i < a.rows(); ++i)
        for (la::size_type j = 0; j < a.cols(); ++j)
        {
            a(i, j) = static_cast<double>(i * a.cols() + j + 1);        // 1..6
            b(i, j) = static_cast<double>((i * a.cols() + j + 1) * 10); // 10,20,...
        }

    la::matrix<double> a_orig(a.rows(), a.cols());
    a_orig = a;
    la::matrix<double> b_orig(b.rows(), b.cols());
    b_orig = b;

    // basic += (matrix rhs)
    a += b;
    for (la::size_type i = 0; i < a.rows(); ++i)
        for (la::size_type j = 0; j < a.cols(); ++j)
        {
            if (double(a(i, j) - (a_orig(i, j) + b_orig(i, j))) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+= produced incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }
        }
    // RHS must remain unchanged
    for (la::size_type i = 0; i < b.rows(); ++i)
        for (la::size_type j = 0; j < b.cols(); ++j)
            if (double(b(i, j) - b_orig(i, j)) != 0.0)
            {
                result = false;
                p_logger.log("Right-hand side modified by +=", ERROR);
                break;
            }

    // basic -= (matrix rhs)
    la::matrix<double> c(a_orig.rows(), a_orig.cols());
    c = a_orig;
    c -= b_orig;
    for (la::size_type i = 0; i < c.rows(); ++i)
        for (la::size_type j = 0; j < c.cols(); ++j)
        {
            if (double(c(i, j) - (a_orig(i, j) - b_orig(i, j))) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "-= produced incorrect value at (" << i << "," << j << ")";
                p_logger.log(ss.str(), ERROR);
            }
        }

    // -------------------------
    // RHS is an expression (temporaries/operants)
    // -------------------------

    // operator+= with RHS = (a_orig - b_orig)  (matrix temporary)
    a = a_orig; // reset lhs
    {
        la::matrix<double> rhs = a_orig - b_orig;
        a += rhs;
        for (la::size_type i = 0; i < a.rows(); ++i)
            for (la::size_type j = 0; j < a.cols(); ++j)
            {
                double expected = a_orig(i, j) + rhs(i, j);
                if (double(a(i, j) - expected) != 0.0)
                {
                    result = false;
                    std::stringstream ss;
                    ss << "+= with expression (matrix temporary) produced incorrect value at (" << i << "," << j << ")";
                    p_logger.log(ss.str(), ERROR);
                }
            }
        // rhs must remain unchanged
        for (la::size_type i = 0; i < rhs.rows(); ++i)
            for (la::size_type j = 0; j < rhs.cols(); ++j)
                if (double(rhs(i, j) - (a_orig(i, j) - b_orig(i, j))) != 0.0)
                {
                    result = false;
                    p_logger.log("Right-hand side modified by += (matrix temporary)", ERROR);
                    break;
                }
    }

    // operator+= with RHS = (a_orig + b_orig)  (expression -> converted to matrix temporary)
    a = a_orig; // reset lhs
    {
        a += a_orig + b_orig; // RHS is an expression
        for (la::size_type i = 0; i < a.rows(); ++i)
            for (la::size_type j = 0; j < a.cols(); ++j)
            {
                double expected = a_orig(i, j) + (a_orig(i, j) + b_orig(i, j));
                if (double(a(i, j) - expected) != 0.0)
                {
                    result = false;
                    std::stringstream ss;
                    ss << "+= with expression (operant) produced incorrect value at (" << i << "," << j << ")";
                    p_logger.log(ss.str(), ERROR);
                }
            }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.rows(); ++i)
            for (la::size_type j = 0; j < a_orig.cols(); ++j)
                if (double(a_orig(i, j) - static_cast<double>(i * a_orig.cols() + j + 1)) != 0.0 ||
                    double(b_orig(i, j) - static_cast<double>((i * b_orig.cols() + j + 1) * 10)) != 0.0)
                {
                    result = false;
                    p_logger.log("An operand was modified by +=(expression)", ERROR);
                    break;
                }
    }

    // operator-= with RHS = (a_orig + b_orig)
    c = a_orig; // reset
    {
        c -= a_orig + b_orig;
        for (la::size_type i = 0; i < c.rows(); ++i)
            for (la::size_type j = 0; j < c.cols(); ++j)
            {
                double expected = a_orig(i, j) - (a_orig(i, j) + b_orig(i, j));
                if (double(c(i, j) - expected) != 0.0)
                {
                    result = false;
                    std::stringstream ss;
                    ss << "-= with expression (operant) produced incorrect value at (" << i << "," << j << ")";
                    p_logger.log(ss.str(), ERROR);
                }
            }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.rows(); ++i)
            for (la::size_type j = 0; j < a_orig.cols(); ++j)
                if (double(a_orig(i, j) - static_cast<double>(i * a_orig.cols() + j + 1)) != 0.0 ||
                    double(b_orig(i, j) - static_cast<double>((i * b_orig.cols() + j + 1) * 10)) != 0.0)
                {
                    result = false;
                    p_logger.log("An operand was modified by -=(expression)", ERROR);
                    break;
                }
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "matrix<> error in add/sub assignment";
        p_errors.push_back(strs.str());
    }
    return result;
}

} // namespace la_test
