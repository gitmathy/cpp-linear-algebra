/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_dense_matrix.hpp
/// @brief Declaration of testing dense matrix data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_DENSE_MATRIX_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_DENSE_MATRIX_HPP

#include "tests/includes/unit_test.hpp"
#include "tests/includes/unit_tests/unit_test_collection.hpp"

namespace la {
namespace test {

/// @brief Add all dense tests to the test_collection
void add_all_dense_matrix(unit_test_collection &collection);

/// @brief Test add and sub assignment of matrices
class matrix_add_sub_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_add_sub_assignment_test() : unit_test("matrix_add_sub_assignment", "Testing +0 and -=")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub of matrices
class matrix_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_add_sub_ops_test() : unit_test("matrix_add_sub_ops", "Testing - and +") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test apply_func on matrix
class matrix_apply_func_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_apply_func_test() : unit_test("matrix apply_func", "Testing apply member") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test construction of matrices
class matrix_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    matrix_construct_test() : unit_test("matrix_construct", "Testing constructor") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy assignment of matrices
class matrix_copy_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_copy_assignment_test() : unit_test("matrix_copy_assignment", "Testing A=B") {}
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

/// @brief Test iterating of matrices
class matrix_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_iterator_test() : unit_test("matrix_iterator", "Testing iterators") {}
    /// @brief Run the test
    int execute();
};

/// @brief Test add and sub and multiplications of matrices and vector
class mixed_operations : public unit_test
{
public:
    /// @brief Constructing the test
    mixed_operations() : unit_test("mixed_operations", "Testing x = -a+b+2*b+(A+B)*a+(2*B)*b") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test move constructor of matrices
class matrix_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_move_ctor_test() : unit_test("matrix_move_ctor", "Test move in constructor") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test multiplication assignment of matrices
class matrix_mult_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_mult_assignment_test() : unit_test("matrix_mult_assignment_test", "Testing A*=B") {}
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

/// @brief Simple matrix norm sanity test (keeps vector-focused file paired)
class matrix_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_norms_test() : unit_test("matrix_norms", "Testing 1, 2, 3, and max-norm") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test writing and reading matrices
class matrix_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_read_write_test() : unit_test("matrix_read_write", "Test reading and writing to files")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test resizing of matrices
class matrix_resize_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_resize_test() : unit_test("matrix_resize", "Test resizing") {}
    /// @brief Run the test
    int execute();
};

/// @brief Test add and sub assignment of matrices
class matrix_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_unary_assignment_test() : unit_test("matrix_unary_assignment", "Testing B -= A") {}
    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
