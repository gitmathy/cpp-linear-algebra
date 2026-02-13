#include "includes/test_vector.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

vector_test::vector_test() : unit_test("vector test") {}

bool vector_test::execute()
{
    bool result = true;

    // construct with defaults
    LA::vector<double> *v = new LA::vector<double>(3, 2.0);
    bool construct_result = true;
    for (LA::size_type i = 0; i < v->size(); ++i)
    {
        if ((*v)(i)-2.0 > 1e-16)
        {
            construct_result = false;
        }
    }
    if (!construct_result)
    {
        p_errors.push_back("vector: Invalid value by constructor");
        p_logger.log("== Invalid value by constructor", ERROR);
    }
    // destruct
    delete v;
    return result = construct_result;
}

} // namespace la_test
