/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/operations_inner_prod.cpp
/// @brief Unit tests for inner products
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/data_structure/expressions/iterator.hpp"
#include "la/dense"
#include "la/operation/multiplication.hpp"
#include "la/sparse"
#include <gtest/gtest.h>

namespace la {

/// \brief Testing inner product vector
TEST(ops_inner_prod, vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});

    EXPECT_EQ(inner_product(a, b), 32);
}

/// \brief Testing inner product static vector
TEST(ops_inner_prod, static_vector)
{
    const static_vector<int, 3> a({1, 2, 3});
    const static_vector<int, 3> b({4, 5, 6});

    EXPECT_EQ(inner_product(a, b), 32);
}

/// \brief Testing inner product vector operant
TEST(ops_inner_prod, vector_operant)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({1, 2, 3});
    EXPECT_EQ(inner_product(a, b + c), 46);
}

TEST(ops_inner_prod, operant_vector)
{
    const vector<int> a({1, 2, 3});
    const vector<int> b({4, 5, 6});
    const vector<int> c({1, 2, 3});
    EXPECT_EQ(inner_product(a + b, c), 46);
}

/// \brief Testing norm default
TEST(ops_inner_prod, vector_norm)
{
    const vector<double> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm(a), std::sqrt(18.0));
}

/// \brief Testing norm-1
TEST(ops_inner_prod, vector_norm_1)
{
    const vector<double> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<1>(a), 8.);
}

/// \brief Testing norm-2
TEST(ops_inner_prod, vector_norm_2)
{
    const vector<double> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<2>(a), std::sqrt(18.0));
}

/// \brief Testing norm-3
TEST(ops_inner_prod, vector_norm_3)
{
    const vector<double> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<3>(a), std::pow(44.0, 1.0 / 3.0));
}

/// \brief Testing norm-max
TEST(ops_inner_prod, vector_norm_max)
{
    const vector<double> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<SIZE_TYPE_MAX>(a), 3.);
}

/// \brief Testing norm default
TEST(ops_inner_prod, static_vector_norm)
{
    const static_vector<double, 4> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm(a), std::sqrt(18.0));
}

/// \brief Testing norm-1
TEST(ops_inner_prod, static_vector_norm_1)
{
    const static_vector<double, 4> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<1>(a), 8.);
}

/// \brief Testing norm-2
TEST(ops_inner_prod, static_vector_norm_2)
{
    const static_vector<double, 4> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<2>(a), std::sqrt(18.0));
}

/// \brief Testing norm-3
TEST(ops_inner_prod, static_vector_norm_3)
{
    const static_vector<double, 4> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<3>(a), std::pow(44.0, 1.0 / 3.0));
}

/// \brief Testing norm-max
TEST(ops_inner_prod, static_vector_norm_max)
{
    const static_vector<double, 4> a({-1., 2., -2., 3.});
    EXPECT_DOUBLE_EQ(norm<SIZE_TYPE_MAX>(a), 3.);
}

/// \brief Testing norm default
TEST(ops_inner_prod, matrix_norm)
{
    const matrix<double> a({{-1., 2., -2., 3.}});
    EXPECT_DOUBLE_EQ(norm(a), std::sqrt(18.0));
}

/// \brief Testing norm-1
TEST(ops_inner_prod, matrix_norm_1)
{
    const matrix<double> a({{-1., 2., -2., 3.}});
    EXPECT_DOUBLE_EQ(norm<1>(a), 8.);
}

/// \brief Testing norm-2
TEST(ops_inner_prod, matrix_norm_2)
{
    const matrix<double> a({{-1., 2., -2., 3.}});
    EXPECT_DOUBLE_EQ(norm<2>(a), std::sqrt(18.0));
}

/// \brief Testing norm-3
TEST(ops_inner_prod, matrix_norm_3)
{
    const matrix<double> a({{-1., 2., -2., 3.}});
    EXPECT_DOUBLE_EQ(norm<3>(a), std::pow(44.0, 1.0 / 3.0));
}

/// \brief Testing norm-max
TEST(ops_inner_prod, matrix_norm_max)
{
    const matrix<double> a({{-1., 2., -2., 3.}});
    EXPECT_DOUBLE_EQ(norm<SIZE_TYPE_MAX>(a), 3.);
}

/// \brief Testing norm default
TEST(ops_inner_prod, operator_norm_default)
{
    const vector<double> a({1., 2.}), b({2., 2.});
    EXPECT_DOUBLE_EQ(norm(a + b), 5.);
}

/// \brief Testing norm-1
TEST(ops_inner_prod, operator_norm_1)
{
    const static_vector<double, 2> a({1., 2.}), b({2., 2.});
    EXPECT_DOUBLE_EQ(norm<1>(a + b), 7.);
}

/// \brief Testing norm-2
TEST(ops_inner_prod, operator_norm_2)
{
    const static_vector<double, 2> a({1., 2.}), b({2., 2.});
    EXPECT_DOUBLE_EQ(norm<2>(a + b), 5.);
}

/// \brief Testing norm-3
TEST(ops_inner_prod, operator_norm_3)
{
    const vector<double> a({1., 2.}), b({2., 2.});
    EXPECT_DOUBLE_EQ(norm<3>(a + b), std::pow(91.0, 1.0 / 3.0));
}

/// \brief Testing norm-max
TEST(ops_inner_prod, operator_norm_max)
{
    const matrix<double> a({{-1., 2., -2., 3.}}), b({{-1., 2., -2., 4.}});
    EXPECT_DOUBLE_EQ(norm<SIZE_TYPE_MAX>(a + b), 7.);
}

} // namespace la
