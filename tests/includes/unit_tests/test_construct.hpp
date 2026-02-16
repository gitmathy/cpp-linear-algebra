#ifndef LA_TEST_UNIT_TEST_CONSTRUCT_H
#define LA_TEST_UNIT_TEST_CONSTRUCT_H

#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

/// @brief Test construction of vectors
class vector_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    vector_construct_test() : unit_test("vector construct test") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test construction of matrices
class matrix_construct_test : public unit_test
{
public:
    /// @brief Construct the test
    matrix_construct_test() : unit_test("matrix construct test") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
