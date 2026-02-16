#ifndef LA_TEST_ASSIGN_TEST_H
#define LA_TEST_ASSIGN_TEST_H

#include "tests/includes/performance_test.hpp"

namespace la
{
namespace test
{

/// @brief Test a+=b for vectors
class vector_assign_add : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    void run_single_test();

public:
    /// @brief Set me up
    vector_assign_add(const size_type runs, const size_type dim)
        : vector_performance_test("vector_assign_add", runs, dim)
    {
    }
};

} // namespace test
} // namespace la
#endif
