#ifndef LA_TEST_UNIT_TEST_MAT_VECTOR_RESIZE_H
#define LA_TEST_UNIT_TEST_MAT_VECTOR_RESIZE_H

#include "includes/settings.hpp"
#include "includes/types.hpp"
#include "tests/includes/unit_test.hpp"
#include <list>
#include <string>

namespace la
{
namespace test
{

/// @brief Check if all values in a vector or matrix have the same given value
template <typename la_struct> inline bool check_values(const la_struct &x, const typename la_struct::value_type &value)
{
    for (auto it = x.begin(); it != x.end(); ++it)
    {
        if ((*it - value) > LA_EPS)
        {
            return false;
        }
    }
    return true;
}

/// @brief Test resizing of vectors
class vector_resize_test : public unit_test
{
protected:
public:
    /// @brief Constructing the test
    vector_resize_test() : unit_test("resize vectors") {}

    /// @brief Run the test
    int execute();
};

/// @brief Test resizing of matrices
class matrix_resize_test : public unit_test
{
protected:
public:
    /// @brief Constructing the test
    matrix_resize_test() : unit_test("resize matrices") {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
