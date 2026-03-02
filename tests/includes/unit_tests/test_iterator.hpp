/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_iterator.hpp
/// @brief Definition of iterator tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_ITERATOR_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_ITERATOR_HPP

#include "tests/includes/unit_test.hpp"
#include <list>
#include <string>

namespace la {
namespace test {

/// @brief Test iterating of vectors
class vector_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_iterator_test() : unit_test("vector_iterator", "Testing iterators") {}

    /// @brief Run the test
    int execute();
};

/// @brief Test iterating of static_vectors
class static_vector_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_iterator_test() : unit_test("static_vector_iterator_test", "Testing iterators") {}

    /// @brief Run the test
    int execute();
};

/// @brief Test iterating of matrices
class matrix_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_iterator_test() : unit_test("matrix_iterator", "Testing iterators") {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
