#include "la/data_structure/matrix.hpp"
#include "pch.h"
#include <gtest/gtest.h>

namespace la {

TEST(matrix, default_constructor)
{
    matrix<int> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}

} // namespace la
