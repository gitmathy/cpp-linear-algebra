#ifndef LA_TEST_UNIT_TEST_MIXED_OPERATIONS_H
#define LA_TEST_UNIT_TEST_MIXED_OPERATIONS_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub assignment of matrices
class mixed_operations : public unit_test
{
public:
    /// @brief Constructing the test
    mixed_operations() : unit_test("mixed operations") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
