/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_static.hpp
/// @brief Declaration of testing static data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_STATIC_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_STATIC_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

// forward declaration
class unit_test_collection;

/// @brief Add all dense tests to the test_collection
void add_all_static(unit_test_collection &collection);

/// @brief Test add and sub assignment of static_vectors
class static_vector_add_sub_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_add_sub_assignment_test()
        : unit_test("static_vector_add_sub_assignment_test", "Testing += and -=")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub of static_vectors
class static_vector_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_add_sub_ops_test()
        : unit_test("static_vector_add_sub_ops_test", "Testing - and +")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test construction of static_vectors
class static_vector_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    static_vector_construct_test()
        : unit_test("static_vector_construct_test", "Testing constructor")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy assignment of static_vectors
class static_vector_copy_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_copy_assignment_test()
        : unit_test("static_vector_copy_assignment_test", "Testing a=b")
    {}
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

/// @brief Test inner product of a static_vector
class static_vector_inner_product_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_inner_product_test()
        : unit_test("static_vector_inner_product_test", "Testing inner product")
    {}
    /// @brief Run the test
    int execute() override;
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

/// @brief Test move constructor of static_vectors
class static_vector_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_move_ctor_test()
        : unit_test("static_vector_move_ctor_test", "Test move in constructor")
    {}
    /// @brief Run the test
    int execute() override;
};

/// @brief Test multiplication and div assignment of static_vector
class static_vector_mult_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_mult_assignment_test()
        : unit_test("static_vector_mult_assignment_test", "Testing y*=x")
    {}
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

/// @brief Test add and sub assignment of static_vectors
class static_vector_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    static_vector_unary_assignment_test()
        : unit_test("static_vector_unary_assignment_test", "Testing b -= a")
    {}
    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
