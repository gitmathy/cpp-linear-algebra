#ifndef LA_TEST_UNIT_TEST_READ_WRITE_H
#define LA_TEST_UNIT_TEST_READ_WRITE_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test writing and reading vectors
class vector_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_read_write_test() : unit_test("vector_read_write", "Test reading and writing to files")
    {}

    /// @brief Run the test
    int execute() override;
};

/// @brief Test writing and reading matrices
class matrix_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_read_write_test() : unit_test("matrix_read_write", "Test reading and writing to files")
    {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
