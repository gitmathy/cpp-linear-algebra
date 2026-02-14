#include "includes/test_vector_copy_assignment.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_copy_assignment_test::execute()
{
    bool result = true;

    // double
    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.size(); ++i)
        src(i) = static_cast<double>(i * 3 + 2);

    la::vector<double> dst(2, double(0));
    dst = src; // copy-assign

    if (dst.size() != src.size())
    {
        result = false;
        p_logger.log("Copy-assigned vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.size(); ++i)
    {
        if (double(dst(i) - src(i)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Copy-assigned vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // source must remain unchanged
    for (la::size_type i = 0; i < src.size(); ++i)
    {
        if (double(src(i) - static_cast<double>(i * 3 + 2)) != 0.0)
        {
            result = false;
            p_logger.log("Source vector changed after copy-assignment", ERROR);
            break;
        }
    }

    // float & int quick checks
    la::vector<float> srcf(3);
    for (la::size_type i = 0; i < srcf.size(); ++i)
        srcf(i) = static_cast<float>(i + 1);
    la::vector<float> dstf(1);
    dstf = srcf;
    if (dstf.size() != srcf.size())
        result = false;

    la::vector<int> srci(2);
    srci(0) = 5;
    srci(1) = 6;
    la::vector<int> dsti(1);
    dsti = srci;
    if (dsti.size() != srci.size())
        result = false;

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in copy assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
