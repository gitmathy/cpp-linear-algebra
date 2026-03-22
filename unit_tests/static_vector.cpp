/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/static_vector.cpp
/// @brief Unit tests for static vector
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/data_structure/static_vector.hpp"
#include "la/util/error.hpp"
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

} // namespace la
