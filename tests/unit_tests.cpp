#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/unit_tests/test_construct.hpp"
#include "tests/includes/unit_tests/test_iterator.hpp"
#include "tests/includes/unit_tests/test_resize.hpp"

using namespace la::test;

int main()
{
    logger::get().set_level(INFO);
    unit_test_collection tests;

    tests.transfer("vector", std::make_unique<vector_resize_test>());
    tests.transfer("vector", std::make_unique<vector_construct_test>());
    tests.transfer("vector", std::make_unique<vector_iterator_test>());

    tests.transfer("matrix", std::make_unique<matrix_resize_test>());
    tests.transfer("matrix", std::make_unique<matrix_construct_test>());
    tests.transfer("matrix", std::make_unique<matrix_iterator_test>());
    int result = tests.run();

    return result ? 0 : 1;
}
