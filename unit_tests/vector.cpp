/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/vector.cpp
/// @brief Unit tests for the vector class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/dense"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <utility>

namespace la {

/// @brief Testing the default constructor
TEST(vector, default_constructor)
{
    vector<int> v_int;
    EXPECT_EQ(v_int.rows(), 0);
    vector<double> v_double;
    EXPECT_EQ(v_double.rows(), 0);
    EXPECT_THROW(v_int(1), util::error);
    EXPECT_THROW(v_double(1), util::error);
}

/// @brief Testing the constructor with a given size
TEST(vector, constructor_with_size)
{
    vector<int> v_int(2);
    EXPECT_EQ(v_int.rows(), 2);
    EXPECT_EQ(v_int(0), 0);
    EXPECT_EQ(v_int(1), 0);
}

/// @brief Testing the constructor with given size and default values
TEST(vector, constructor_with_size_and_value)
{
    vector<int> v_int(2, 1);
    EXPECT_EQ(v_int.rows(), 2);
    EXPECT_EQ(v_int(0), 1);
    EXPECT_EQ(v_int(1), 1);
    vector<double> v_double(2, 1.1);
    EXPECT_EQ(v_int.rows(), 2);
    EXPECT_DOUBLE_EQ(v_double(0), 1.1);
    EXPECT_EQ(v_double(1), 1.1);
}

/// @brief Testing the constructor from static vector
TEST(vector, constructor_from_static)
{
    static_vector<int, 3> v_static(1);
    vector<int> v(v_static);
    EXPECT_EQ(v.rows(), 3);
    EXPECT_EQ(v(0), 1);
    EXPECT_EQ(v(1), 1);
    EXPECT_EQ(v(2), 1);
}

/// @brief Testing the constructor from initializer list
TEST(vector, constructor_from_initializer)
{
    vector<float> v({3.14f, 2.72f});
    EXPECT_EQ(v.rows(), 2);
    EXPECT_FLOAT_EQ(v(0), 3.14f);
    EXPECT_FLOAT_EQ(v(1), 2.72f);
}

/// @brief Testing the move constructor
TEST(vector, constructor_move)
{
    vector<size_type> v({3, 2});
    vector<size_type> v_dest(std::move(v));
    EXPECT_EQ(v_dest.rows(), 2);
    EXPECT_EQ(v_dest(0), 3);
    EXPECT_EQ(v_dest(1), 2);
    EXPECT_EQ(v.rows(), 0);
    EXPECT_EQ(v.non_zeros(), 0);
}

/// @brief Testing the copy constructor
TEST(vector, constructor_copy)
{
    vector<size_type> v({3, 2});
    vector<size_type> v_dest(v);
    EXPECT_EQ(v_dest.rows(), 2);
    EXPECT_EQ(v.rows(), 2);
    EXPECT_EQ(v_dest(0), 3);
    EXPECT_EQ(v_dest(1), 2);
    EXPECT_EQ(v(0), 3);
    EXPECT_EQ(v(1), 2);
}

/// @brief Testing the constructor form expression
TEST(vector, constructor_expression)
{
    expressions::operant<expressions::literal<int>> expr(1);
    vector<int> v(expr);
    EXPECT_EQ(v.rows(), 1);
    EXPECT_EQ(v(0), 1);
}

/// @brief Testing the destructor
TEST(vector, destructor)
{
    vector<int> *v = new vector<int>(3);
    delete v;
}

/// @brief Testing allocate
TEST(vector, allocate)
{
    vector<long int> v({3, 2});
    v.allocate(3);
    EXPECT_EQ(v.rows(), 3);
}

/// @brief Testing resize
TEST(vector, resize)
{
    vector<size_type> v({3, 2});
    v.resize(1, 1);
    EXPECT_EQ(v.rows(), 1);
    EXPECT_EQ(v(0), 1);
}

// rows is tested in nearly all other tests

/// @brief Testing cols
TEST(vector, cols)
{
    vector<size_type> v;
    EXPECT_EQ(v.rows(), 0);
    EXPECT_EQ(v.cols(), 1);
}

/// @brief Testing non zeros
TEST(vector, non_zeros)
{
    vector<size_type> v(1);
    EXPECT_EQ(v.non_zeros(), 1);
}

/// @brief Testing read and write elements
TEST(vector, read_write)
{
    const size_type n = 6;
    vector<size_type> v(n);
    for (size_type i = 0; i < n; ++i) {
        v(i) = i;
    }
    for (size_type i = 0; i < n; ++i) {
        EXPECT_EQ(v(i), i);
    }
}

/// @brief Testing evaluate
TEST(vector, evaluate)
{
    const size_type n = 6;
    vector<size_type> v(n);
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
TEST(vector, constant_iterators)
{
    const vector<size_type> v({0, 1, 2, 3, 4, 5});
    size_type i = 0;
    size_type const *val_ptr = v.vals();
    for (vector<size_type>::citerator it = v.begin(); it != v.end(); ++it, ++i, ++val_ptr) {
        EXPECT_EQ(*val_ptr, i);
        EXPECT_EQ(*it, i);
    }
}

/// @brief Testing iterators
TEST(vector, iterators)
{
    vector<size_type> v(6);
    for (vector<size_type>::iterator it = v.begin(); it != v.end(); ++it) {
        *it = 2;
    }
    EXPECT_EQ(std::find_if(v.begin(), v.end(), [](auto a) { return a != 2; }), v.end());
}

// Assign is already tested via the constructors (as they just call the assign)

/// @brief Testing move assign
TEST(vector, move_assign)
{
    vector<size_type> v(2, 1);
    vector<size_type> v_dest;
    v_dest = std::move(v);
    EXPECT_EQ(v.rows(), 0);
    EXPECT_EQ(v_dest.rows(), 2);
    EXPECT_EQ(v_dest(0), 1);
    EXPECT_EQ(v_dest(1), 1);
}

/// @brief Testing += vector
TEST(vector, add_assign_vector)
{
    vector<size_type> v({1, 2}), w({3, 4});
    w += v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 4);
    EXPECT_EQ(w(1), 6);
    EXPECT_THROW(v += vector<size_type>(6), util::error);
}

/// @brief Testing += expression
TEST(vector, add_assign_expr)
{
    vector<size_type> v(2, 1);
    expressions::operant<vector<size_type>> expr(v);
    vector<size_type> w({1, 2});
    w += expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 2);
    EXPECT_EQ(w(1), 3);
}

/// @brief Testing *= scalar
TEST(vector, mult_assign_scalar)
{
    vector<int> w({3, 1});
    w *= -3;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), -9);
    EXPECT_EQ(w(1), -3);
}

/// @brief Testing *= vector
TEST(vector, mult_assign_vector)
{
    vector<int> v({1, 2}), w({3, 1});
    w *= v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 3);
    EXPECT_EQ(w(1), 2);
    EXPECT_THROW(v += vector<int>(6), util::error);
}

/// @brief Testing *= expression
TEST(vector, mult_assign_expr)
{
    vector<size_type> v(2, 4);
    expressions::operant<vector<size_type>> expr(v);
    vector<size_type> w({1, 2});
    w *= expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 4);
    EXPECT_EQ(w(1), 8);
}

/// @brief Testing -= vector
TEST(vector, sub_assign_vector)
{
    vector<int> v({1, 2}), w({3, 1});
    w -= v;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 2);
    EXPECT_EQ(w(1), -1);
    EXPECT_THROW(v -= vector<int>(6), util::error);
}

/// @brief Testing -= expression
TEST(vector, sub_assign_expr)
{
    vector<size_type> v(2, 1);
    expressions::operant<vector<size_type>> expr(v);
    vector<size_type> w({1, 2});
    w -= expr;
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 0);
    EXPECT_EQ(w(1), 1);
}

/// @brief Testing apply func
TEST(vector, apply_func)
{
    vector<size_type> w({4, 5});
    w.apply_func([](auto x) { return x * x; });
    EXPECT_EQ(w.rows(), 2);
    EXPECT_EQ(w(0), 16);
    EXPECT_EQ(w(1), 25);
}

/// @brief Testing read and write to binary file
TEST(vector, read_write_bin)
{
    const std::string filename = "tmp_read_bin_vector.tst";
    vector<double> w({3.14, 2.718}), v;
    w.to_file(filename, true);
    v.from_file(filename, true);
    EXPECT_EQ(v.rows(), 2);
    EXPECT_DOUBLE_EQ(v(0), 3.14);
    EXPECT_DOUBLE_EQ(v(1), 2.718);
    util::delete_file(filename);
    EXPECT_THROW(v.to_file("/no_exist/dummy", true), util::error);
}

/// @brief Testing read and write to text file
TEST(vector, read_wite_txt)
{
    const std::string filename = "tmp_read_txt_vector.tst";
    vector<double> w({3.14, 2.718}), v;
    w.to_file(filename, false);
    v.from_file(filename, false);
    EXPECT_EQ(v.rows(), 2);
    EXPECT_DOUBLE_EQ(v(0), 3.14);
    EXPECT_DOUBLE_EQ(v(1), 2.718);
    util::delete_file(filename);
    EXPECT_THROW(v.to_file("/no_exist/dummy", false), util::error);
}

} // namespace la
