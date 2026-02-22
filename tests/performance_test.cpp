#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/performance_tests/add.hpp"
#include "tests/includes/performance_tests/assign.hpp"
#include "tests/includes/performance_tests/decompose.hpp"
#include "tests/includes/performance_tests/resize.hpp"

using namespace la;
using namespace la::test;

const size_type MATRIX_SOLVE = 1000;
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
    tests.transfer("row_matrix", std::make_unique<matrix_add<ROW_WISE>>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_multiple_add<ROW_WISE>>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_mixed_add_sub<ROW_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_add<COLUMN_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_multiple_add<COLUMN_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_mixed_add_sub<COLUMN_WISE>>(RUNS));
    tests.transfer("mixed_matrix", std::make_unique<matrix_add_sub_mixed_storage>(RUNS));

    // Resizing
    tests.transfer("vector", std::make_unique<vector_resize>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_resize<ROW_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_resize<COLUMN_WISE>>(RUNS));

    // Assigning
    tests.transfer("vector", std::make_unique<vector_assign>(RUNS));
    tests.transfer("vector", std::make_unique<vector_add_assign>(RUNS));
    tests.transfer("vector", std::make_unique<vector_sum_add_assign>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_assign<ROW_WISE>>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_assign_add<ROW_WISE>>(RUNS));
    tests.transfer("row_matrix", std::make_unique<matrix_assign_add_sum<ROW_WISE>>(RUNS));
    tests.transfer("row_matrix",
                   std::make_unique<vector_assign_matrix_vector_mult<ROW_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_assign<COLUMN_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_assign_add<COLUMN_WISE>>(RUNS));
    tests.transfer("col_matrix", std::make_unique<matrix_assign_add_sum<COLUMN_WISE>>(RUNS));
    tests.transfer("cols_matrix",
                   std::make_unique<vector_assign_matrix_vector_mult<COLUMN_WISE>>(RUNS));
    tests.transfer("mixed_matrix", std::make_unique<matrix_assign_storage_mismatch>(RUNS));

    tests.transfer("algorithms",
                   std::make_unique<decompose_solve_lu<ROW_WISE, ROW_WISE>>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms",
                   std::make_unique<decompose_solve_lu<ROW_WISE, COLUMN_WISE>>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms",
                   std::make_unique<decompose_solve_lu<COLUMN_WISE, ROW_WISE>>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms", std::make_unique<decompose_solve_lu<COLUMN_WISE, COLUMN_WISE>>(
                                     RUNS, MATRIX_SOLVE));

    std::cout << "Executing tests ..." << std::endl;
    int result = tests.run();

    return result > 0 ? 1 : 0;
}
