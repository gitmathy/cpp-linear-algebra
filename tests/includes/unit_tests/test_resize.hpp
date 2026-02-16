#ifndef LA_TEST_UNIT_TEST_RESIZE_H
#define LA_TEST_UNIT_TEST_RESIZE_H

#include "tests/includes/unit_test.hpp"
#include <list>
#include <string>

namespace la
{
namespace test
{

/// @brief Test resizing of vectors
class vector_resize_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_resize_test() : unit_test("resize vectors") {}

    /// @brief Run the test
    int execute();
};

/// @brief Test resizing of matrices
class matrix_resize_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_resize_test() : unit_test("resize matrices") {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
