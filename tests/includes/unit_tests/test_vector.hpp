/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_vector.hpp
/// @brief Declaration of testing dense vector data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_VECTOR_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_VECTOR_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

// forward declaration
class unit_test_collection;

/// @brief Add all dense tests to the test_collection
void add_all_vector(unit_test_collection &collection);

/// @brief Test add and sub assignment of vectors
class vector_add_sub_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_add_sub_assignment_test() : unit_test("vector_add_sub_assignment", "Testing += and -=")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub of vectors
class vector_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_add_sub_ops_test() : unit_test("vector_add_sub_ops", "Testing - and +") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test apply_func on vector
class vector_apply_func_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_apply_func_test() : unit_test("vector_apply_func", "Testing apply member") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test construction of vectors
class vector_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    vector_construct_test() : unit_test("vector_construct", "Testing constructor") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy assignment of vectors
class vector_copy_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_copy_assignment_test() : unit_test("vector_copy_assignment", "Testing a=b") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy constructor of vectors
class vector_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_copy_ctor_test() : unit_test("vector_copy_ctor", "Testing copy constructor") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test inner product of a vector
class vector_inner_product_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_inner_product_test() : unit_test("vector_inner_product_test", "Testing inner product") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test iterating of vectors
class vector_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_iterator_test() : unit_test("vector_iterator", "Testing iterators") {}
    /// @brief Run the test
    int execute();
};

/// @brief Test move constructor of vectors
class vector_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_move_ctor_test() : unit_test("vector_move_ctor", "Test move in constructor") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test multiplication and div assignment of vectors
class vector_mult_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_mult_assignment_test() : unit_test("vector_mult_assignment_test", "Testing y*=x") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test elementwise multiplication of vectors
class vec_vec_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    vec_vec_mult_test() : unit_test("vec_vec_mult", "Testing x*y and (x*y)*alpha") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test norms for vectors
class vector_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_norms_test() : unit_test("vector_norms", "Testing 1, 2, 3, and max-norm") {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test writing and reading vectors
class vector_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_read_write_test() : unit_test("vector_read_write", "Test reading and writing to files")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test resizing of vectors
class vector_resize_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_resize_test() : unit_test("vector_resize", "Test resizing") {}
    /// @brief Run the test
    int execute();
};

/// @brief Test add and sub assignment of vectors
class vector_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_unary_assignment_test() : unit_test("vector_unary_assignment", "Testing b -= a") {}
    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
