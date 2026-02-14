#include "includes/test_collection.hpp"
#include "includes/test_log.hpp"
#include "includes/unit_test.hpp"

#include "includes/test_vector_add_sub_assignment.hpp"
#include "includes/test_vector_add_sub_ops.hpp"
#include "includes/test_vector_const_iterator.hpp"
#include "includes/test_vector_construct.hpp"
#include "includes/test_vector_copy_assignment.hpp"
#include "includes/test_vector_iterator.hpp"
#include "includes/test_vector_move_assignment.hpp"
#include "includes/test_vector_move_ctor.hpp"
#include "includes/test_vector_resize.hpp"

#include <iostream>
#include <memory>

int main()
{
    la_test::logger::get().set_level(la_test::DEBUG);
    la_test::test_collection tests;

    tests.transfer(std::make_unique<la_test::vector_construct_test>());
    tests.transfer(std::make_unique<la_test::vector_resize_test>());
    tests.transfer(std::make_unique<la_test::vector_move_constructor_test>());
    tests.transfer(std::make_unique<la_test::vector_copy_assignment_test>());
    tests.transfer(std::make_unique<la_test::vector_move_assignment_test>());
    tests.transfer(std::make_unique<la_test::vector_add_sub_assignment_test>());
    tests.transfer(std::make_unique<la_test::vector_add_sub_ops_test>());
    tests.transfer(std::make_unique<la_test::vector_iterator_test>());
    tests.transfer(std::make_unique<la_test::vector_const_iterator_test>());

    bool result = tests.run();
    return result ? 0 : 1;
}
