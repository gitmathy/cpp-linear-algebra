#include "includes/test_vector_resize.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_resize_test::execute()
{
    bool result = true;

    // double
    la::vector<double> v(3);
    v.resize(5, double(100));
    if (double(v(4) - 100) > 1e-12)
    {
        result = false;
        p_logger.log("Default value not set when making vector bigger", ERROR);
    }
    if (v.size() != 5)
    {
        result = false;
        p_logger.log("Incorrect size when making vector bigger", ERROR);
    }
    v.resize(4);
    if (double(v(3) - 100) > 1e-12)
    {
        result = false;
        p_logger.log("Value not kept when making vector smaller", ERROR);
    }
    if (v.size() != 4)
    {
        result = false;
        p_logger.log("Incorrect size when making vector smaller", ERROR);
    }

    // float
    la::vector<float> vf(3);
    vf.resize(5, float(100));
    if (double(vf(4) - 100) > 1e-6)
        result = false;
    vf.resize(2);
    if (vf.size() != 2)
        result = false;

    // int
    la::vector<int> vi(3);
    vi.resize(5, int(100));
    if (double(vi(4) - 100) != 0.0)
        result = false;
    vi.resize(4);
    if (vi.size() != 4)
        result = false;

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<> error in resize";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
