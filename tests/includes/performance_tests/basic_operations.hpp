/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/performance_tests/basic_operations.hpp
/// @brief Definition of basic operations performance tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_PERFORMANCE_TESTS_BASIC_OPERATIONS_HPP
#define LA_TEST_INCLUDES_PERFORMANCE_TESTS_BASIC_OPERATIONS_HPP

#include "la/dense"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

// ===============================================
// V E C T O R
// ===============================================

/// @brief Test c=a+b for vectors
class vector_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c_vec = p_a_vec + p_b_vec; }

public:
    /// @brief Set me up
    vector_add(const size_type runs) : performance_test("vector_add", "Testing c = a+b", runs) {}
};

/// @brief Test c=a+b+a+b
class vector_multiple_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c_vec = p_a_vec + p_b_vec + p_a_vec + p_b_vec; }

public:
    /// @brief Set me up
    vector_multiple_add(const size_type runs)
        : performance_test("vector_multiple_add", "Testing c = a+b+a+b", runs)
    {}
};

/// @brief Test c=a+b for vectors where c, a, and b are static_vectors<double,3>
class vector_add_vectors : public performance_test
{
private:
    vector<static_vector<double, 3>> p_a, p_b, p_c;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c_vec = p_a_vec + p_b_vec; }

public:
    /// @brief Set me up
    vector_add_vectors(const size_type runs)
        : performance_test("vector_add_static_vector", "Testing c = a+b", runs),
          p_a(p_a_vec.rows()), p_b(p_b_vec.rows()), p_c(p_b_vec.rows())
    {}
};

/// @brief Test c = -a - b - 2 + a - b + 2 for vector
class vector_mixed_add_sub : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        p_c_vec = -p_a_vec - p_b_vec - 2 + p_a_vec - p_b_vec + 2;
    }

public:
    /// @brief Set me up
    vector_mixed_add_sub(const size_type runs)
        : performance_test("vector_mixed_add_sub", "Testing  c = -a- b-2+a-b+2", runs)
    {}
};

// ===============================================
// M A T R I C E S
// ===============================================

/// @brief Test c=a+b for matrices
class matrix_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_C = p_A + p_B; }

public:
    /// @brief Set me up
    matrix_add(const size_type runs) : performance_test("matrix_add", "Testing c = a+b", runs) {}
};

/// @brief Test c=a+b+a+b for matrices
class matrix_multiple_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_C = p_A + p_B + p_A + p_B; }

public:
    /// @brief Set me up
    matrix_multiple_add(const size_type runs)
        : performance_test("matrix_multiple_add", "Testing c = a+b+a+b", runs)
    {}
};

/// @brief Test c = a - b - 2 + a - b + 2 for matrices
class matrix_mixed_add_sub : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_C = -p_A - p_B - 2. + p_A - p_B + 2.; }

public:
    /// @brief Set me up
    matrix_mixed_add_sub(const size_type runs)
        : performance_test("matrix_mixed_add_sub", "Testing  c = -a- b-2+a-b+2", runs)
    {}
};

/// @brief Test c= a*b (blocked) for matrices
class matrix_multiply_blocked : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        p_C = algorithm::matrix_multiplication<double>::multiply(p_A, p_B);
    }

public:
    /// @brief Set me up
    matrix_multiply_blocked(const size_type runs, size_type size)
        : performance_test("matrix_multiply_blocked", "Testing  C = A*B", runs), p_size(size)
    {}

    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

} // namespace test
} // namespace la
#endif
