#ifndef LA_TEST_UNIT_TEST_NORMS_H
#define LA_TEST_UNIT_TEST_NORMS_H

#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

/// @brief Test norms for vectors (and simple matrix sanity)
class vector_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_norms_test() : unit_test("vector norms") {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Simple matrix norm sanity test (keeps vector-focused file paired)
class matrix_norms_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_norms_test() : unit_test("matrix norms") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
