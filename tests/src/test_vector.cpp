#include "includes/test_vector.hpp"
#include "../includes/types.hpp"

namespace la_test
{

vector_test::vector_test() : unit_test("vector test") {}

bool vector_test::execute()
{
    p_logger.log("   Test constructing a vector", DEBUG);
    bool construct_ok = true;
    construct_ok = test_construct<double>() && construct_ok;
    construct_ok = test_construct<float>() && construct_ok;
    construct_ok = test_construct<int>() && construct_ok;

    p_logger.log("   Test resizing a vector", DEBUG);
    bool resize_ok = true;
    resize_ok = test_resize<double>() && resize_ok;
    resize_ok = test_resize<float>() && resize_ok;
    resize_ok = test_resize<int>() && resize_ok;

    p_logger.log("   Test moving a vector", DEBUG);
    bool move_ok = true;
    move_ok = test_move_constructor<double>() && move_ok;
    move_ok = test_move_constructor<float>() && move_ok;
    move_ok = test_move_constructor<int>() && move_ok;

    return construct_ok && resize_ok && move_ok;
}

} // namespace la_test
