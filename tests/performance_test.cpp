#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/performance_tests/add.hpp"
#include "tests/includes/performance_tests/assign.hpp"
#include "tests/includes/performance_tests/decompose.hpp"
#include "tests/includes/performance_tests/resize.hpp"

using namespace la;
using namespace la::test;

const size_type VECTOR_N = 100000000;
const size_type MATRIX_M = 1000;
const size_type MATRIX_N = 100000;
const size_type MATRIX_SOLVE = 1000;
const size_type RUNS = 10;

int main()
{
    logger::get().set_level(DEBUG);
    performance_test_collection tests(RUNS, VECTOR_N, MATRIX_M, MATRIX_N);

    tests.transfer("vector", std::make_unique<vector_resize>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_assign>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_assign_add>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_assign_add_sum>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_add>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_multiple_add>(RUNS, VECTOR_N));
    tests.transfer("vector", std::make_unique<vector_mixed_add_sub>(RUNS, VECTOR_N));

    tests.transfer("matrix", std::make_unique<matrix_resize>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_assign>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix",
                   std::make_unique<matrix_assign_storage_mismatch>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_assign_add>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_assign_add_sum>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_add>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_multiple_add>(RUNS, MATRIX_M, MATRIX_N));
    tests.transfer("matrix", std::make_unique<matrix_mixed_add_sub>(RUNS, MATRIX_M, MATRIX_N));

    tests.transfer("matrix_vector",
                   std::make_unique<vector_assign_matrix_vector_mult>(RUNS, MATRIX_M, MATRIX_N));

    tests.transfer("algorithms",
                   std::make_unique<decompose_row_solve_row_matrix>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms",
                   std::make_unique<decompose_row_solve_col_matrix>(RUNS, MATRIX_SOLVE));
    tests.transfer("algorithms",
                   std::make_unique<decompose_col_solve_col_matrix>(RUNS, MATRIX_SOLVE));

    int result = tests.run();

    return result > 0 ? 1 : 0;
}
