/// Part of the project "cpp-linear-algebra"
///
/// @file unit_tests/util.cpp
/// @brief Unit tests for utils
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "pch.h"

#include "la/util/block_helper.hpp"
#include "la/util/error.hpp"
#include "la/util/macros.hpp"

namespace la {
namespace util {

/// @brief shape assert
TEST(util, shape_assert)
{
    EXPECT_THROW(la_assert(false, "dummy", __FUNCTION_NAME__, SHAPE), shape_error);
}

/// @brief shape assert
TEST(util, boundary_assert)
{
    EXPECT_THROW(la_assert(false, "dummy", __FUNCTION_NAME__, BOUNDARY), boundary_error);
}

/// @brief shape assert
TEST(util, layout_assert)
{
    EXPECT_THROW(la_assert(false, "dummy", __FUNCTION_NAME__, LAYOUT), layout_error);
}

/// @brief shape assert
TEST(util, non_zero_assert)
{
    EXPECT_THROW(la_assert(false, "dummy", __FUNCTION_NAME__, NON_ZERO), non_zero_error);
}

/// @brief shape assert
TEST(util, file_error_assert)
{
    EXPECT_THROW(la_assert(false, "dummy", __FUNCTION_NAME__, FILE_ERROR), file_error);
}

/// @brief create_block_indices
TEST(util, create_block_indices)
{
    std::vector<size_type> block_indices = create_block_indices(5, 20, 4);
    EXPECT_EQ(block_indices.size(), 4);
    EXPECT_EQ(block_indices[0], 5);
    EXPECT_EQ(block_indices[1], 9);
    EXPECT_EQ(block_indices[2], 13);
    EXPECT_EQ(block_indices[3], 17);
    EXPECT_THROW(create_block_indices(10, 0, 4), layout_error);
}

/// @brief create_range_indices
TEST(util, create_range_indices)
{
    std::vector<size_type> range = create_range_indices(5, 10);
    EXPECT_EQ(range.size(), 5);
    for (size_type i = 0; i < 5; ++i) {
        EXPECT_EQ(range[i], i + 5);
    }

    EXPECT_EQ(create_range_indices(10, 0).size(), 0);
}

} // namespace util
} // namespace la
