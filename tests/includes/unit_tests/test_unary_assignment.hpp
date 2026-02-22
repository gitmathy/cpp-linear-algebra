#ifndef LA_TEST_UNIT_TEST_UNARY_ASSIGNMENT_H
#define LA_TEST_UNIT_TEST_UNARY_ASSIGNMENT_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub assignment of vectors
class vector_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_unary_assignment_test() : unit_test("vector_unary_assignment", "Testing b -= a") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub assignment of matrices
class matrix_unary_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_unary_assignment_test() : unit_test("matrix_unary_assignment", "Testing B -= A") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
