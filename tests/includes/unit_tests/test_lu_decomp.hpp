/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_lu_decomp.hpp
/// @brief Definition of lu decomposition tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_LU_DECOMP_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_LU_DECOMP_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub of vectors
class lu_decomposition_test : public unit_test
{
public:
    /// @brief Constructing the test
    lu_decomposition_test() : unit_test("lu_decomposition", "Testing LU decomposition") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
