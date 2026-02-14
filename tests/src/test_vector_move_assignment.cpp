#include "includes/test_vector_move_assignment.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_move_assignment_test::execute()
{
    bool result = true;

    la::vector<double> src(4);
    for (la::size_type i = 0; i < src.size(); ++i)
        src(i) = static_cast<double>(i * 5 + 7);

    la::vector<double> dst(2, double(9));
    dst = std::move(src);

    if (dst.size() != 4)
    {
        result = false;
        p_logger.log("Move-assigned vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.size(); ++i)
    {
        if (double(dst(i) - static_cast<double>(i * 5 + 7)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Move-assigned vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    if (src.size() != 0)
    {
        result = false;
        p_logger.log("Moved-from vector not left empty after move-assignment", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in move assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
