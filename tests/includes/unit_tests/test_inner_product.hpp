/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/test_inner_product.hpp
/// @brief Definition of testing inner product
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_INNER_PRODUCT_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_INNER_PRODUCT_HPP

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test inner product of a vector
class vector_inner_product_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_inner_product_test() : unit_test("vector_inner_product_test", "Testing inner product") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
