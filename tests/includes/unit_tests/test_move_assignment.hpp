#ifndef LA_TEST_UNIT_TEST_MATRIX_MOVE_ASSIGNMENT_H
#define LA_TEST_UNIT_TEST_MATRIX_MOVE_ASSIGNMENT_H

#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

/// @brief Test move assignment of vectors
class vector_move_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_move_assignment_test() : unit_test("vector move assignment") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test move assignment of matrices
class matrix_move_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_move_assignment_test() : unit_test("matrix move assignment") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
