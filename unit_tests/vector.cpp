#include "la/data_structure/vector.hpp"
#include <gtest/gtest.h>

namespace la {

TEST(vector, default_constructor)
{
    vector<int> v;
    EXPECT_EQ(v.rows(), 0);
}

TEST(vector, constructor_with_size)
{
    vector<int> v(2);
    EXPECT_EQ(v.rows(), 2);
    EXPECT_TRUE(v(0) == 0 && v(1) == 0);
}

TEST(vector, constructor_with_size_and_value)
{
    vector<int> v(2, 1);
    EXPECT_EQ(v.rows(), 2);
    EXPECT_TRUE(v(0) == 1 && v(1) == 1);
}

} // namespace la
