#ifndef LA_TEST_UNIT_TEST_MATRIX_COPY_CTOR_H
#define LA_TEST_UNIT_TEST_MATRIX_COPY_CTOR_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test copy constructor of vectors
class vector_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_copy_ctor_test() : unit_test("vector_copy_ctor", "Testing copy constructor") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test copy constructor of matrices
class matrix_copy_ctor_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_copy_ctor_test() : unit_test("matrix_copy_ctor", "Testing copy constructor") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
