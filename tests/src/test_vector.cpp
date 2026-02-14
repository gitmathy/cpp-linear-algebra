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

    p_logger.log("   Test copy-assignment operator", DEBUG);
    bool copy_assign_ok = true;
    copy_assign_ok = test_copy_assignment<double>() && copy_assign_ok;
    copy_assign_ok = test_copy_assignment<float>() && copy_assign_ok;
    copy_assign_ok = test_copy_assignment<int>() && copy_assign_ok;

    p_logger.log("   Test move-assignment operator", DEBUG);
    bool move_assign_ok = true;
    move_assign_ok = test_move_assignment<double>() && move_assign_ok;
    move_assign_ok = test_move_assignment<float>() && move_assign_ok;
    move_assign_ok = test_move_assignment<int>() && move_assign_ok;

    p_logger.log("   Test add/sub assignment operators (+=, -=)", DEBUG);
    bool add_sub_assign_ok = true;
    add_sub_assign_ok = test_add_sub_assignment<double>() && add_sub_assign_ok;
    add_sub_assign_ok = test_add_sub_assignment<float>() && add_sub_assign_ok;
    add_sub_assign_ok = test_add_sub_assignment<int>() && add_sub_assign_ok;

    p_logger.log("   Test add/sub operators (+, -)", DEBUG);
    bool add_sub_ops_ok = true;
    add_sub_ops_ok = test_add_sub_ops<double>() && add_sub_ops_ok;
    add_sub_ops_ok = test_add_sub_ops<float>() && add_sub_ops_ok;
    add_sub_ops_ok = test_add_sub_ops<int>() && add_sub_ops_ok;

    return construct_ok && resize_ok && move_ok && copy_assign_ok && move_assign_ok && add_sub_assign_ok &&
           add_sub_ops_ok;
}

} // namespace la_test
