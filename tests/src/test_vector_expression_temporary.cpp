#include "includes/test_vector_expression_temporary.hpp"
#include "../includes/la.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_expression_temporary_test::execute()
{
    bool result = true;

    // prepare operands
    la::vector<double> a(3), b(3), c(3);
    for (la::size_type i = 0; i < a.rows(); ++i)
    {
        a(i) = static_cast<double>(i + 1);         // 1,2,3
        b(i) = static_cast<double>((i + 1) * 10);  // 10,20,30
        c(i) = static_cast<double>((i + 1) * 100); // 100,200,300
    }

    la::vector<double> a_orig = a;
    la::vector<double> b_orig = b;
    la::vector<double> c_orig = c;

    // 1) nested temporary on right-hand side: a + (b + c)
    la::vector<double> res1 = a + (b + c);
    for (la::size_type i = 0; i < res1.rows(); ++i)
    {
        double expected = a_orig(i) + b_orig(i) + c_orig(i);
        if (double(res1(i) - expected) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "a + (b + c) produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // 2) nested temporary on left-hand side: (a + b) + c
    la::vector<double> res2 = (a + b) + c;
    for (la::size_type i = 0; i < res2.rows(); ++i)
    {
        double expected = a_orig(i) + b_orig(i) + c_orig(i);
        if (double(res2(i) - expected) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "(a + b) + c produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // 3) chained operators producing temporaries: a + b + c
    la::vector<double> res3 = a + b + c;
    for (la::size_type i = 0; i < res3.rows(); ++i)
    {
        double expected = a_orig(i) + b_orig(i) + c_orig(i);
        if (double(res3(i) - expected) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "a + b + c produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // 4) operand that is a true temporary (created by factory lambda)
    auto make_tmp = []()
    {
        la::vector<double> t(3);
        for (la::size_type j = 0; j < t.rows(); ++j)
            t(j) = static_cast<double>((j + 1) * 7); // 7,14,21
        return t;
    };

    la::vector<double> dst(3);
    dst = a + make_tmp();
    for (la::size_type i = 0; i < dst.rows(); ++i)
    {
        double expected = a_orig(i) + static_cast<double>((i + 1) * 7);
        if (double(dst(i) - expected) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "a + make_tmp() produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // verify original operands were not modified by any expression
    for (la::size_type i = 0; i < a.rows(); ++i)
    {
        if (double(a(i) - a_orig(i)) != 0.0 || double(b(i) - b_orig(i)) != 0.0 || double(c(i) - c_orig(i)) != 0.0)
        {
            result = false;
            p_logger.log("An operand was modified by expression-temporary evaluation", ERROR);
            break;
        }
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in expression-temporary evaluation";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
