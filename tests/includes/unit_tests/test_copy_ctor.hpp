/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_copy_ctor.hpp
/// @brief Definition of copy constructor tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_MATRIX_COPY_CTOR_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_MATRIX_COPY_CTOR_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test copy constructor of vectors
class vector_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_copy_ctor_test() : unit_test("vector_copy_ctor", "Testing copy constructor") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy constructor of static_vectors
class static_vector_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_copy_ctor_test()
        : unit_test("static_vector_copy_ctor_test", "Testing copy constructor")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy constructor of matrices
class matrix_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_copy_ctor_test() : unit_test("matrix_copy_ctor", "Testing copy constructor") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
