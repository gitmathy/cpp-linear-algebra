/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_mult_ops.hpp
/// @brief Definition of multiplication tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MULT_OPS_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MULT_OPS_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test elementwise multiplication of vectors
class vec_vec_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    vec_vec_mult_test() : unit_test("vec_vec_mult", "Testing x*y and (x*y)*alpha") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test elementwise multiplication of static_vectors
class static_vec_vec_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vec_vec_mult_test()
        : unit_test("static_vec_vec_mult_test", "Testing x*y and (x*y)*alpha")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Matrix-matrix multiplication
class mat_mat_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    mat_mat_mult_test() : unit_test("mat_mat_mult", "Testing A*B and A*alpha") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test multiply matrix and vector
class mat_vec_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    mat_vec_mult_test() : unit_test("mat_vec_mult", "Testing A*b") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
