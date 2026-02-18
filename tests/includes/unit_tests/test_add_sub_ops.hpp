#ifndef LA_TEST_UNIT_TEST_MATRIX_ADD_SUB_OPS_H
#define LA_TEST_UNIT_TEST_MATRIX_ADD_SUB_OPS_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub of vectors
class vector_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_add_sub_ops_test() : unit_test("vector add/sub ops") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test add and sub of matrices
class matrix_add_sub_ops_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_add_sub_ops_test() : unit_test("matrix add/sub ops") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
