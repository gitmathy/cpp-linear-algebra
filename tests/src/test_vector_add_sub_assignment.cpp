#include "includes/test_vector_add_sub_assignment.hpp"
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

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in add/sub assignment";
        p_errors.push_back(strs.str());
    }
    return result;
}

} // namespace la_test
