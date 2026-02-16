#ifndef LA_TEST_UNIT_TEST_MATRIX_MOVE_CTOR_H
#define LA_TEST_UNIT_TEST_MATRIX_MOVE_CTOR_H

#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

/// @brief Test move constructor of vectors
class vector_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_move_ctor_test() : unit_test("vector move ctor") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test move constructor of matrices
class matrix_move_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_move_ctor_test() : unit_test("matrix move ctor") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
