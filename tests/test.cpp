#include "includes/test_collection.hpp"
#include "includes/test_log.hpp"
#include "includes/test_vector.hpp"
#include "includes/unit_test.hpp"
#include <iostream>
#include <memory>

int main()
{
    la_test::logger::get().set_level(la_test::DEBUG);
    la_test::test_collection tests;
    tests.transfer(std::make_unique<la_test::vector_test>());
    bool result = tests.run();
    return result ? 0 : 1;
}
