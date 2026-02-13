#include "includes/test_vector.hpp"
#include "../includes/types.hpp"
#include "../includes/vector.hpp"

namespace la_test
{

vector_test::vector_test() : unit_test("vector test") {}

bool vector_test::execute()
{
    bool result = true;
    bool construct = true;
    construct = test_construct<double>() && construct;
    construct = test_construct<float>() && construct;
    construct = test_construct<int>() && construct;

    return result;
}

} // namespace la_test
