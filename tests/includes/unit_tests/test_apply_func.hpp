#ifndef LA_TEST_UNIT_TEST_APPLY_FUNC_H
#define LA_TEST_UNIT_TEST_APPLY_FUNC_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test apply_func on vector
class vector_apply_func_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_apply_func_test() : unit_test("vector_apply_func", "Testing apply member") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test apply_func on matrix
class matrix_apply_func_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_apply_func_test() : unit_test("matrix apply_func", "Testing apply member") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
