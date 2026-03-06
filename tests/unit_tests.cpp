/// Part of the project "cpp-linear-algebra"
///
/// @file tests/unit_tests.cpp
/// @brief Implementation of unit test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/unit_tests/test_add_sub_assignment.hpp"
#include "tests/includes/unit_tests/test_add_sub_ops.hpp"
#include "tests/includes/unit_tests/test_apply_func.hpp"
#include "tests/includes/unit_tests/test_construct.hpp"
#include "tests/includes/unit_tests/test_copy_assignment.hpp"
#include "tests/includes/unit_tests/test_copy_ctor.hpp"
#include "tests/includes/unit_tests/test_inner_product.hpp"
#include "tests/includes/unit_tests/test_iterator.hpp"
#include "tests/includes/unit_tests/test_lu_decomp.hpp"
#include "tests/includes/unit_tests/test_mixed_operations.hpp"
#include "tests/includes/unit_tests/test_move_assignment.hpp"
#include "tests/includes/unit_tests/test_move_ctor.hpp"
#include "tests/includes/unit_tests/test_mult_div_assignment.hpp"
#include "tests/includes/unit_tests/test_mult_ops.hpp"
#include "tests/includes/unit_tests/test_norms.hpp"
#include "tests/includes/unit_tests/test_read_write.hpp"
#include "tests/includes/unit_tests/test_resize.hpp"
#include "tests/includes/unit_tests/test_sparse_matrix_builder.hpp"

using namespace la::test;

int main()
{
    logger::get().set_level(DEBUG);
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
    tests.transfer("vector", std::make_unique<vector_norms_test>());
    tests.transfer("vector", std::make_unique<vector_apply_func_test>());
    tests.transfer("vector", std::make_unique<vector_read_write_test>());
    tests.transfer("vector", std::make_unique<vector_mult_div_assignment_test>());
    tests.transfer("vector", std::make_unique<vec_vec_mult_test>());
    tests.transfer("vector", std::make_unique<vector_inner_product_test>());

    tests.transfer("static_vector", std::make_unique<static_vector_construct_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_iterator_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_copy_assignment_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_copy_ctor_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_move_assignment_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_move_ctor_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_add_sub_assignment_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_add_sub_ops_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_norms_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_mult_div_assignment_test>());
    tests.transfer("static_vector", std::make_unique<static_vec_vec_mult_test>());
    tests.transfer("static_vector", std::make_unique<static_vector_inner_product_test>());

    tests.transfer("matrix", std::make_unique<matrix_resize_test>());
    tests.transfer("matrix", std::make_unique<matrix_construct_test>());
    tests.transfer("matrix", std::make_unique<matrix_iterator_test>());
    tests.transfer("matrix", std::make_unique<matrix_copy_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_copy_ctor_test>());
    tests.transfer("matrix", std::make_unique<matrix_move_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_move_ctor_test>());
    tests.transfer("matrix", std::make_unique<matrix_add_sub_assignment_test>());
    tests.transfer("matrix", std::make_unique<matrix_add_sub_ops_test>());
    tests.transfer("matrix", std::make_unique<matrix_norms_test>());
    tests.transfer("matrix", std::make_unique<matrix_apply_func_test>());
    tests.transfer("matrix", std::make_unique<matrix_read_write_test>());
    tests.transfer("matrix", std::make_unique<mat_vec_mult_test>());

    tests.transfer("matrix_vector", std::make_unique<mat_vec_mult_test>());
    tests.transfer("matrix_vector", std::make_unique<lu_decomposition_test>());
    tests.transfer("matrix_vector", std::make_unique<mixed_operations>());

    tests.transfer("sparse_matrix", std::make_unique<sparse_matrix_builder_insert_test>());
    tests.transfer("sparse_matrix", std::make_unique<sparse_matrix_builder_assemble_test>());

    int result = tests.run(std::set<std::string>({"sparse_matrix"}));

    return result > 0 ? 1 : 0;
}
