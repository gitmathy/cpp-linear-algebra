
#include "pch.h"

#include "la/data_structure/sparse_matrix.hpp"
#include <gtest/gtest.h>

namespace la {

TEST(sparse_matrix, default_constructor)
{
    sparse_matrix<int> a;
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}

} // namespace la
