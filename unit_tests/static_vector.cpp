/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/static_vector.cpp
/// @brief Unit tests for static vector
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include <gtest/gtest.h>

namespace la {

/// @brief Testing the default constructor
TEST(static_vector, default_constructor)
{
    static_vector<int, 3> v_int(2);
    EXPECT_EQ(v_int.rows(), 3);
    EXPECT_EQ(v_int(0), 2);
    EXPECT_EQ(v_int(1), 2);
    EXPECT_EQ(v_int(2), 2);
    static_vector<double, 4> v_double;
    EXPECT_EQ(v_double.rows(), 4);
    EXPECT_THROW(v_int(3), util::boundary_error);
    EXPECT_THROW(v_double(4), util::boundary_error);
}

/// @brief Testing the constructor from vector
TEST(static_vector, constructor_from_vector)
{
    vector<float> vec(4, 2.0f);
    static_vector<float, 3> v(vec);
    EXPECT_EQ(v.rows(), 3);
    EXPECT_EQ(v.non_zeros(), 3);
    EXPECT_FLOAT_EQ(v(0), 2.0f);
    EXPECT_FLOAT_EQ(v(1), 2.0f);
    EXPECT_FLOAT_EQ(v(2), 2.0f);
    EXPECT_THROW((static_vector<float, 5>(vec)), util::boundary_error);
}

/// @brief Testing the constructor from initializer list
TEST(static_vector, constructor_from_initializer)
{
    static_vector<float, 2> v({3.14f, 2.72f});
    EXPECT_EQ(v.rows(), 2);
    EXPECT_FLOAT_EQ(v(0), 3.14f);
    EXPECT_FLOAT_EQ(v(1), 2.72f);
}

/// @brief Testing the constructor from array of values
TEST(static_vector, constructor_from_array)
{
    vector<float> vec(4, 2.0f);
    static_vector<float, 3> v(vec.vals());
    EXPECT_EQ(v.rows(), 3);
    EXPECT_FLOAT_EQ(v(0), 2.0f);
    EXPECT_FLOAT_EQ(v(1), 2.0f);
    EXPECT_FLOAT_EQ(v(2), 2.0f);
}

/// @brief Testing the constructor from expression
TEST(static_vector, constructor_expression)
{
    expressions::operant<expressions::literal<int>> expr(1);
    static_vector<int, 1> v(expr);
    EXPECT_EQ(v.rows(), 1);
    EXPECT_EQ(v(0), 1);
}

/// @brief Testing destructor
TEST(static_vector, destructor)
{
    static_vector<int, 1> *v = new static_vector<int, 1>(1);
    delete v;
}

// rows is tested in nearly all other tests

/// @brief Testing read and write elements
TEST(static_vector, read_write)
{
    const size_type n = 6;
    static_vector<size_type, 6> v;
    for (size_type i = 0; i < n; ++i) {
        v(i) = i;
    }
    for (size_type i = 0; i < n; ++i) {
        EXPECT_EQ(v(i), i);
    }
}

/// @brief Testing evaluate
TEST(static_vector, evaluate)
{
    const size_type n = 6;
    static_vector<size_type, 6> v;
    for (size_type i = 0; i < n; ++i) {
        v(i) = i;
    }
    for (size_type i = 0; i < n; ++i) {
        EXPECT_EQ(v.evaluate(i), i);
        EXPECT_EQ(v.evaluate(i, i), i);
    }
    EXPECT_THROW(v(6), util::error);
}

/// @brief Testing constant iterators
TEST(static_vector, constant_iterators)
{
    const static_vector<size_type, 6> v({0, 1, 2, 3, 4, 5});
    size_type i = 0;
    size_type const *val_ptr = v.vals();
    for (static_vector<size_type, 6>::citerator it = v.begin(); it != v.end();
         ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*val_ptr, i);
        EXPECT_EQ(*it, i);
    }
}

/// @brief Testing iterators
TEST(static_vector, iterators)
{
    static_vector<size_type, 6> v;
    for (static_vector<size_type, 6>::iterator it = v.begin(); it != v.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(v.begin(), v.end(), [](auto a) { return a != 2; }), v.end());
}

// Assign is already tested via the constructors (as they just call the assign)

/// @brief Testing += vector
TEST(static_vector, add_assign_vector)
{
    static_vector<size_type, 2> v({1, 2}), w({3, 4});
    w += v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 4);
    EXPECT_EQ(w(1), 6);
}

/// @brief Testing += expression
TEST(static_vector, add_assign_expr)
{
    vector<size_type> v(2, 1);
    expressions::operant<vector<size_type>> expr(v);
    static_vector<size_type, 2> w({1, 2});
    w += expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 2);
    EXPECT_EQ(w(1), 3);
}

/// @brief Testing *= scalar
TEST(static_vector, mult_assign_scalar)
{
    static_vector<int, 2> w({3, 1});
    w *= -3;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), -9);
    EXPECT_EQ(w(1), -3);
}

/// @brief Testing *= vector
TEST(static_vector, mult_assign_vector)
{
    static_vector<int, 2> v({1, 2}), w({3, 1});
    w *= v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 3);
    EXPECT_EQ(w(1), 2);
}

/// @brief Testing *= expression
TEST(static_vector, mult_assign_expr)
{
    vector<size_type> v(2, 4);
    expressions::operant<vector<size_type>> expr(v);
    static_vector<size_type, 2> w({1, 2});
    w *= expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 4);
    EXPECT_EQ(w(1), 8);
}

/// @brief Testing -= vector
TEST(static_vector, sub_assign_vector)
{
    static_vector<int, 2> v({1, 2}), w({3, 1});
    w -= v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 2);
    EXPECT_EQ(w(1), -1);
}

/// @brief Testing -= expression
TEST(static_vector, sub_assign_expr)
{
    vector<size_type> v(2, 1);
    expressions::operant<vector<size_type>> expr(v);
    static_vector<size_type, 2> w({1, 2});
    w -= expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 0);
    EXPECT_EQ(w(1), 1);
}

} // namespace la
