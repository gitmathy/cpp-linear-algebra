/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_apply_func.cpp
/// @brief Implementation of test of apply function
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_inner_product.hpp"
#include "la/dense"
#include "la/static"

namespace la {
namespace test {

int vector_inner_product_test::execute()
{
    vector<int> a({1, 2, 3});
    vector<int> b({4, 5, 6});

    int alpha = inner_product(a, b);

    if (alpha != 32) {
        report_error("inner_product produced wrong value");
    }
    return (int)errors().size();
}

int static_vector_inner_product_test::execute()
{
    static_vector<int, 3> a({1, 2, 3});
    static_vector<int, 3> b({4, 5, 6});

    int alpha = inner_product(a, b);

    if (alpha != 32) {
        report_error("inner_product produced wrong value for static vector");
    }
    return (int)errors().size();
}

} // namespace test
} // namespace la
