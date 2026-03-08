/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/performance_tests/resize.hpp
/// @brief Definition of resize performance tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_PERFORMANCE_TESTS_RESIZE_TEST_HPP
#define LA_TEST_INCLUDES_PERFORMANCE_TESTS_RESIZE_TEST_HPP

#include "la/dense"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Test resize a vector (free memory, allocate memory, and assign default value)
class vector_resize : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a_vec.resize(p_a_vec.rows() + 1); }

public:
    /// @brief Set me up
    vector_resize(const size_type runs)
        : performance_test("vector_resize", "Testing a.resize()", runs)
    {}
};

/// @brief Test resize a matrix (free memory, allocate memory, and assign default value)
class matrix_resize : public performance_test
{
protected:
    /// @brief Execute a single test
    /// We resize to one larger than the normal size, to enforce resizing and resetting when tearing
    /// down the test
    inline void run_single_test() override { p_A.resize(p_A.rows() + 1, p_A.cols() + 1); }

public:
    /// @brief Set me up
    matrix_resize(const size_type runs)
        : performance_test("matrix_resize", "Testing A.resize()", runs)
    {}
};

} // namespace test
} // namespace la
#endif
