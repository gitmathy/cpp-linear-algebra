#include "includes/test_vector_add_sub_ops.hpp"
#include "../includes/la.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_add_sub_ops_test::execute()
{
    bool result = true;

    la::vector<double> a(3), b(3);
    for (la::size_type i = 0; i < a.size(); ++i)
    {
        a(i) = static_cast<double>(i + 2);       // 2,3,4
        b(i) = static_cast<double>((i + 1) * 5); // 5,10,15
    }

    la::vector<double> a_orig(a.size());
    a_orig = a;
    la::vector<double> b_orig(b.size());
    b_orig = b;

    la::vector<double> sum = a + b;
    for (la::size_type i = 0; i < sum.size(); ++i)
    {
        if (double(sum(i) - (a_orig(i) + b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "+ produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (double(a(0) - a_orig(0)) != 0.0 || double(b(0) - b_orig(0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by +", ERROR);
    }

    la::vector<double> diff = a - b;
    for (la::size_type i = 0; i < diff.size(); ++i)
    {
        if (double(diff(i) - (a_orig(i) - b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "- produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (double(a(0) - a_orig(0)) != 0.0 || double(b(0) - b_orig(0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by -", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in add/sub operators";
        p_errors.push_back(strs.str());
    }

    la::vector<double> a_2 = a + (double)2;
    if (a_2(0) - 4 > 1e-16)
    {
        std::stringstream strs;
        strs << "vector<> error in add/sub operators with scalar";
        p_errors.push_back(strs.str());
    }

    la::vector<double> a_3 = (double)1 + a + (double)2 + b;
    if (a_3(0) - 10 > 1e-16)
    {
        std::stringstream strs;
        strs << "vector<> error in add/sub operators with scalars";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
