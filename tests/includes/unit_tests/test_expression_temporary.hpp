#ifndef LA_TEST_UNIT_TEST_VECTOR_EXPRESSION_TEMPORARY_H
#define LA_TEST_UNIT_TEST_VECTOR_EXPRESSION_TEMPORARY_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test vector expression temporary
class vector_expression_temporary_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_expression_temporary_test() : unit_test("vector expression temporary") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test matrix expression temporary (companion to the vector test)
class matrix_expression_temporary_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_expression_temporary_test() : unit_test("matrix expression temporary") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
