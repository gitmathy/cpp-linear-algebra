/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_mixed_operations.hpp
/// @brief Definition of mixed operations tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MIXED_OPERATIONS_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MIXED_OPERATIONS_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub assignment of matrices
class mixed_operations : public unit_test
{
public:
    /// @brief Constructing the test
    mixed_operations() : unit_test("mixed_operations", "Testing x = -a+b+2*b+(A+B)*a+(2*B)*b") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
