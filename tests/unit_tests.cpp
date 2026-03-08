/// Part of the project "cpp-linear-algebra"
///
/// @file tests/unit_tests.cpp
/// @brief Implementation of unit test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_dense_algorithm.hpp"
#include "tests/includes/unit_tests/test_dense_matrix.hpp"
#include "tests/includes/unit_tests/test_sparse_matrix.hpp"
#include "tests/includes/unit_tests/test_static.hpp"
#include "tests/includes/unit_tests/test_vector.hpp"
#include "tests/includes/unit_tests/unit_test_collection.hpp"
#include <memory>

using namespace la::test;

int main()
{
    logger::get().set_level(DEBUG);
    unit_test_collection tests;

    add_all_vector(tests);
    add_all_dense_matrix(tests);
    add_all_static(tests);
    add_all_dense_algorithm(tests);
    add_all_sparse_matrix(tests);

    int result = tests.run(std::set<std::string>());

    return result > 0 ? 1 : 0;
}
