#include "includes/test_vector_move_ctor.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_move_constructor_test::execute()
{
    bool result = true;

    // double
    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<double>(i * 10 + 1);
    la::vector<double> dst(std::move(src));
    if (dst.rows() != 4)
    {
        result = false;
        p_logger.log("Moved-to vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
    {
        if (double(dst(i) - static_cast<double>(i * 10 + 1)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Moved-to vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (src.rows() != 0)
    {
        result = false;
        p_logger.log("Moved-from vector not left in empty state (expected size==0)", ERROR);
    }

    // float
    la::vector<float> srcf(3);
    for (la::size_type i = 0; i < srcf.rows(); ++i)
        srcf(i) = static_cast<float>(i * 2 + 1);
    la::vector<float> dstf(std::move(srcf));
    if (dstf.rows() != 3)
        result = false;

    // int
    la::vector<int> srci(2);
    srci(0) = 7;
    srci(1) = 9;
    la::vector<int> dsti(std::move(srci));
    if (dsti.rows() != 2)
        result = false;

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in move constructor";
        p_errors.push_back(strs.str());
    }
    return result;
}

} // namespace la_test
