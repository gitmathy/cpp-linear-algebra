/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_sparse_read_write.hpp
/// @brief Definition of testing file io for sparse matrices
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_READ_WRITE_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_SPARSE_MATRIX_READ_WRITE_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test writing and reading sparse matrices
class sparse_matrix_read_write_test : public unit_test
{
public:
    /// @brief Constructing the test
    sparse_matrix_read_write_test()
        : unit_test("sparse_matrix_read_write_test", "Writing and reading sparse matrices")
    {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
