#include "includes/test_vector_add_sub_assignment.hpp"
#include "../includes/la.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_add_sub_assignment_test::execute()
{
    bool result = true;

    // double
    la::vector<double> a(3), b(3);
    for (la::size_type i = 0; i < a.size(); ++i)
    {
        a(i) = static_cast<double>(i + 1);        // 1,2,3
        b(i) = static_cast<double>((i + 1) * 10); // 10,20,30
    }
    la::vector<double> a_orig(a.size());
    a_orig = a;
    la::vector<double> b_orig(b.size());
    b_orig = b;

    // basic += (vector rhs)
    a += b;
    for (la::size_type i = 0; i < a.size(); ++i)
    {
        if (double(a(i) - (a_orig(i) + b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "+= produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    for (la::size_type i = 0; i < b.size(); ++i)
    {
        if (double(b(i) - b_orig(i)) != 0.0)
        {
            result = false;
            p_logger.log("Right-hand side modified by +=", ERROR);
            break;
        }
    }

    // basic -= (vector rhs)
    la::vector<double> c(a_orig.size());
    c = a_orig;
    c -= b_orig;
    for (la::size_type i = 0; i < c.size(); ++i)
    {
        if (double(c(i) - (a_orig(i) - b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "-= produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // -------------------------
    // New: RHS is an expression
    // -------------------------

    // operator+= with RHS = (a_orig - b_orig)  (vector temporary)
    a = a_orig; // reset lhs
    {
        la::vector<double> rhs = a_orig - b_orig;
        a += rhs;
        for (la::size_type i = 0; i < a.size(); ++i)
        {
            double expected = a_orig(i) + rhs(i);
            if (double(a(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+= with expression (vector temporary) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // rhs must remain unchanged
        for (la::size_type i = 0; i < rhs.size(); ++i)
        {
            if (double(rhs(i) - (a_orig(i) - b_orig(i))) != 0.0)
            {
                result = false;
                p_logger.log("Right-hand side modified by += (vector temporary)", ERROR);
                break;
            }
        }
    }

    // operator+= with RHS = (a_orig + b_orig)  (expression -> operant -> converted to vector temporary)
    a = a_orig; // reset lhs
    {
        a += a_orig + b_orig; // RHS is an expression
        for (la::size_type i = 0; i < a.size(); ++i)
        {
            double expected = a_orig(i) + (a_orig(i) + b_orig(i));
            if (double(a(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+= with expression (operant) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.size(); ++i)
        {
            if (double(a_orig(i) - static_cast<double>(i + 1)) != 0.0 ||
                double(b_orig(i) - static_cast<double>((i + 1) * 10)) != 0.0)
            {
                result = false;
                p_logger.log("An operand was modified by +=(expression)", ERROR);
                break;
            }
        }
    }

    // operator-= with RHS = (a_orig + b_orig)
    c = a_orig; // reset
    {
        c -= a_orig + b_orig;
        for (la::size_type i = 0; i < c.size(); ++i)
        {
            double expected = a_orig(i) - (a_orig(i) + b_orig(i));
            if (double(c(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "-= with expression (operant) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.size(); ++i)
        {
            if (double(a_orig(i) - static_cast<double>(i + 1)) != 0.0 ||
                double(b_orig(i) - static_cast<double>((i + 1) * 10)) != 0.0)
            {
                result = false;
                p_logger.log("An operand was modified by -=(expression)", ERROR);
                break;
            }
        }
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in add/sub assignment";
        p_errors.push_back(strs.str());
    }
    return result;
}

} // namespace la_test
