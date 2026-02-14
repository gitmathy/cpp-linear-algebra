#include "includes/test_vector_construct.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

bool vector_construct_test::execute()
{
    bool result = true;
    // construct with defaults
    la::vector<double> *v = new la::vector<double>(3, double(2));
    for (la::size_type i = 0; i < v->size(); ++i)
    {
        if (double((*v)(i)-2) > 1e-16)
        {
            result = false;
        }
    }
    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(double()).name() << "> error in constructor";
        p_errors.push_back(strs.str());
        p_logger.log(strs.str(), ERROR);
    }
    delete v;

    // repeat for float
    result = result && true; // keep previous result
    la::vector<float> *vf = new la::vector<float>(3, float(2));
    for (la::size_type i = 0; i < vf->size(); ++i)
    {
        if (double((*vf)(i)-2) > 1e-6)
        {
            result = false;
        }
    }
    delete vf;

    // repeat for int
    la::vector<int> *vi = new la::vector<int>(3, int(2));
    for (la::size_type i = 0; i < vi->size(); ++i)
    {
        if (double((*vi)(i)-2) != 0.0)
        {
            result = false;
        }
    }
    delete vi;

    return result;
}

} // namespace la_test
