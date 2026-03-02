/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_norms.hpp
/// @brief Definition of norm tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_NORMS_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_NORMS_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test norms for vectors
class vector_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_norms_test() : unit_test("vector_norms", "Testing 1, 2, 3, and max-norm") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test norms for static_vectors
class static_vector_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_norms_test()
        : unit_test("static_vector_norms_test", "Testing 1, 2, 3, and max-norm")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Simple matrix norm sanity test (keeps vector-focused file paired)
class matrix_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_norms_test() : unit_test("matrix_norms", "Testing 1, 2, 3, and max-norm") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
