#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/performance_tests/assign.hpp"

using namespace la;
using namespace la::test;

const size_type VECTOR_N = 100000000;
const size_type MATRIX_M = 1000;
const size_type MATRIX_N = 100000;
const size_type RUNS = 10;

int main()
{
    logger::get().set_level(DEBUG);
    performance_test_collection tests();

    tests.transfer("vector", std::make_unique<vector_assign_add>(N, RUNS));
    int result = tests.run();

    return result ? 0 : 1;
}
