#include "includes/test_collection.hpp"
#include <sstream>

namespace la_test
{

test_collection::test_collection() : p_logger(logger::get()) {}

void test_collection::transfer(std::unique_ptr<unit_test> new_test)
{
    if (new_test)
    {
        p_tests.push_back(std::move(new_test));
    }
}

bool test_collection::run()
{

    std::stringstream strs;
    strs << "Running test collection with " << p_tests.size() << " tests\n" << "==========";
    p_logger.log(strs, INFO);
    bool result = true;
    int failed_results = 0;
    for (auto it = p_tests.begin(); it != p_tests.end(); ++it)
    {
        strs << "* Setup test: " << (*it)->name();
        p_logger.log(strs, INFO);
        (*it)->setup();
        strs << "* Execute test: " << (*it)->name();
        p_logger.log(strs, INFO);
        result = (*it)->execute() && result;
        if (!result)
        {
            ++failed_results;
        }
        strs << "* Tear down test: " << (*it)->name();
        p_logger.log(strs, INFO);
        (*it)->tear_down();
    }
    strs << "==========\n" << "FAILED results: " << failed_results << std::endl;
    p_logger.log(strs, INFO);
    return result;
}

} // namespace la_test
