#include "tests/includes/collection.hpp"
#include <memory>

// Include the tests
#include "tests/includes/unit_tests/test_resize.hpp"

using namespace la::test;

int main()
{
    logger::get().set_level(DEBUG);
    unit_test_collection tests();

    tests.transfer("vector", std::make_unique<vector_resize_test>());
    int result = tests.run();

    return result ? 0 : 1;
}
