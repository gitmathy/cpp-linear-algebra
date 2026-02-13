#include "includes/test_vector.hpp"
#include "../includes/types.hpp"

namespace la_test
{

vector_test::vector_test() : unit_test("vector test") {}

bool vector_test::execute()
{
    bool construct = true;
    construct = test_construct<double>() && construct;
    construct = test_construct<float>() && construct;
    construct = test_construct<int>() && construct;

    bool resize = true;
    resize = test_resize<double>() && resize;
    resize = test_resize<float>() && resize;
    resize = test_resize<int>() && resize;

    return construct && resize;
}

} // namespace la_test
