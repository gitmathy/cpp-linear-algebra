#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/unit_tests/test_add_sub_assignment.hpp"
#include "tests/includes/unit_tests/test_add_sub_ops.hpp"
#include "tests/includes/unit_tests/test_apply_func.hpp"
#include "tests/includes/unit_tests/test_construct.hpp"
#include "tests/includes/unit_tests/test_copy_assignment.hpp"
#include "tests/includes/unit_tests/test_copy_ctor.hpp"
#include "tests/includes/unit_tests/test_expression_temporary.hpp"
#include "tests/includes/unit_tests/test_iterator.hpp"
#include "tests/includes/unit_tests/test_move_assignment.hpp"
#include "tests/includes/unit_tests/test_move_ctor.hpp"
#include "tests/includes/unit_tests/test_norms.hpp"
#include "tests/includes/unit_tests/test_resize.hpp"

using namespace la::test;

int main()
{
    logger::get().set_level(INFO);
    unit_test_collection tests;

    tests.transfer("vector", std::make_unique<vector_resize_test>());
    tests.transfer("vector", std::make_unique<vector_construct_test>());
    tests.transfer("vector", std::make_unique<vector_iterator_test>());
    tests.transfer("vector", std::make_unique<vector_copy_assignment_test>());
    tests.transfer("vector", std::make_unique<vector_copy_ctor_test>());
    tests.transfer("vector", std::make_unique<vector_move_assignment_test>());
    tests.transfer("vector", std::make_unique<vector_move_ctor_test>());
    tests.transfer("vector", std::make_unique<vector_add_sub_assignment_test>());
    tests.transfer("vector", std::make_unique<vector_add_sub_ops_test>());
    tests.transfer("vector", std::make_unique<vector_expression_temporary_test>());
    tests.transfer("vector", std::make_unique<vector_norms_test>());
    tests.transfer("vector", std::make_unique<vector_apply_func_test>());

    tests.transfer("matrix", std::make_unique<matrix_resize_test>());
    tests.transfer("matrix", std::make_unique<matrix_construct_test>());
    tests.transfer("matrix", std::make_unique<matrix_iterator_test>());
    tests.transfer("matrix", std::make_unique<matrix_copy_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_copy_ctor_test>());
    tests.transfer("matrix", std::make_unique<matrix_move_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_move_ctor_test>());
    tests.transfer("matrix", std::make_unique<matrix_add_sub_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_add_sub_ops_test>());
    tests.transfer("matrix", std::make_unique<matrix_expression_temporary_test>());
    tests.transfer("matrix", std::make_unique<matrix_norms_test>());
    tests.transfer("matrix", std::make_unique<matrix_apply_func_test>());

    int result = tests.run();

    return result > 0 ? 1 : 0;
}
