/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_mult_div_assignment.hpp
/// @brief Definition of multiplication assignment tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MULT_ASSIGNMENT_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MULT_ASSIGNMENT_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test multiplication and div assignment of vectors
class vector_mult_div_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_mult_div_assignment_test() : unit_test("vector_mult_div_assignment", "Testing y*=x") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test multiplication and div assignment of static_vector
class static_vector_mult_div_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_mult_div_assignment_test()
        : unit_test("static_vector_mult_div_assignment_test", "Testing y*=x")
    {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
