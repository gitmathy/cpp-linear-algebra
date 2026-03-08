/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_sparse_matrix.hpp
/// @brief Declaration of testing sparse matrix data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_HPP

#include "tests/includes/unit_test.hpp"
#include "tests/includes/unit_tests/unit_test_collection.hpp"

namespace la {
namespace test {

/// @brief Add all dense tests to the test_collection
void add_all_sparse_matrix(unit_test_collection &collection);

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

/// @brief Test constructing sparse matrices
class sparse_matrix_constructor_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_constructor_test()
        : unit_test("sparse_matrix_constructor_test", "Test constructors")
    {}
    /// @brief Run the test
    int execute();
};

/// @brief Test assembling a sparse matrix
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

/// @brief Test iterator a sparse matrix
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

/// @brief Test writing and reading sparse matrices
class sparse_matrix_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_read_write_test()
        : unit_test("sparse_matrix_read_write_test", "Writing and reading sparse matrices")
    {}
    /// @brief Run the test
    int execute();
};

/// @brief Test writing and reading sparse matrices
class sparse_matrix_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_mult_test() : unit_test("sparse_matrix_mult_test", "Multiplying sparse matrix") {}
    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
