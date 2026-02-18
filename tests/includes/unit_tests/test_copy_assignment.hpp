#ifndef LA_TEST_UNIT_TEST_MATRIX_COPY_ASSIGNMENT_H
#define LA_TEST_UNIT_TEST_MATRIX_COPY_ASSIGNMENT_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test copy assignment of vectors
class vector_copy_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_copy_assignment_test() : unit_test("vector copy assignment") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy assignment of matrices
class matrix_copy_assignment_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_copy_assignment_test() : unit_test("matrix copy assignment") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
