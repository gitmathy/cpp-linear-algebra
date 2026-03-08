/// Part of the project "cpp-linear-algebra"
///
/// @file tests/performance_test.cpp
/// @brief Implementation of performance test suite
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/collection.hpp"
#include <memory>
#include <set>

// Include the tests
#include "tests/includes/performance_tests/assign.hpp"
#include "tests/includes/performance_tests/basic_operations.hpp"
#include "tests/includes/performance_tests/decompose.hpp"
#include "tests/includes/performance_tests/resize.hpp"

using namespace la;
using namespace la::test;

const size_type MATRIX_SOLVE = 1000;
const size_type MATRIX_MULTIPLY = 3000;
const size_type RUNS = 10;

int main()
{
    logger::get().set_level(DEBUG);

    std::cout << "Running performance tests for la suite..." << std::endl;
    performance_test_collection tests(RUNS);

    std::cout << "Adding performance tests..." << std::endl;

    // Performance test add/sub
    tests.transfer("vector", std::make_unique<vector_add>(RUNS));
    tests.transfer("vector", std::make_unique<vector_multiple_add>(RUNS));
    tests.transfer("vector", std::make_unique<vector_mixed_add_sub>(RUNS));
    tests.transfer("vector", std::make_unique<vector_add_vectors>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_add>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_multiple_add>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_mixed_add_sub>(RUNS));

    // Resizing
    tests.transfer("vector", std::make_unique<vector_resize>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_resize>(RUNS));

    // Assigning
    tests.transfer("vector", std::make_unique<vector_assign>(RUNS));
    tests.transfer("vector", std::make_unique<vector_add_assign>(RUNS));
    tests.transfer("vector", std::make_unique<vector_sum_add_assign>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_assign>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_assign_add>(RUNS));
    tests.transfer("matrix", std::make_unique<matrix_assign_add_sum>(RUNS));
    tests.transfer("matrix", std::make_unique<vector_assign_matrix_vector_mult>(RUNS));

    tests.transfer("algorithms", std::make_unique<lu_decompose>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms", std::make_unique<decompose_solve_lu>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms", std::make_unique<matrix_multiply_blocked>(RUNS, MATRIX_MULTIPLY));

    std::cout << "Executing tests ..." << std::endl;
    int result = tests.run(std::set<std::string>());

    return result > 0 ? 1 : 0;
}
