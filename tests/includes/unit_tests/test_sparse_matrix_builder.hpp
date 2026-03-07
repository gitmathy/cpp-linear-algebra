/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_sparse_matrix_builder.hpp
/// @brief Definition of testing sparse matrix builder
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_BUILDER_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_BUILDER_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test accessing elements in a sparse matrix builder
class sparse_matrix_builder_insert_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_builder_insert_test()
        : unit_test("sparse_matrix_builder_insert_test", "Test access elements")
    {}

    /// @brief Run the test
    int execute();
};

class sparse_matrix_builder_assemble_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_builder_assemble_test()
        : unit_test("sparse_matrix_builder_assemble_test", "Test move sparse matrix")
    {}

    /// @brief Run the test
    int execute();
};

class sparse_matrix_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_iterator_test()
        : unit_test("sparse_matrix_iterator_test", "Test iterators of sparse matrix")
    {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
