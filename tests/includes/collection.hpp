#ifndef TEST_LA_TEST_COLLECTION_H
#define TEST_LA_TEST_COLLECTION_H

#include "includes/test_log.hpp"
#include "includes/unit_test.hpp"
#include <list>
#include <memory>

namespace la_test
{

/// @brief Handling a collection of unit tests
class test_collection
{
private:
    /// @brief All tests
    std::list<std::unique_ptr<unit_test>> p_tests;

    /// @brief Logger used for logging
    logger &p_logger;

public:
    test_collection();
    ~test_collection() = default;

    /// @brief Move the unit test to the collection
    /// @param new_test The new unit test
    void transfer(std::unique_ptr<unit_test> new_test);

    /// @brief Execute all tests
    /// @return True if all tests ran fine
    bool run();
};

} // namespace la_test

#endif
