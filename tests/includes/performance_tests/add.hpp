#ifndef LA_TEST_ADD_TEST_H
#define LA_TEST_ADD_TEST_H

#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Test c=a+b for vectors
class vector_add : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a + p_b; }

public:
    /// @brief Set me up
    vector_add(const size_type runs, const size_type dim)
        : vector_performance_test("vector_add", runs, dim)
    {}
};

/// @brief Test c=a+b+a+b
class vector_multiple_add : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a + p_b + p_a + p_b; }

public:
    /// @brief Set me up
    vector_multiple_add(const size_type runs, const size_type dim)
        : vector_performance_test("vector_multiple_add", runs, dim)
    {}
};

/// @brief Test c = a - b - 2 + a - b + 2 for vector
class vector_mixed_add_sub : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a - p_b - 2 + p_a - p_b + 2; }

public:
    /// @brief Set me up
    vector_mixed_add_sub(const size_type runs, const size_type dim)
        : vector_performance_test("vector_mixed_add_sub", runs, dim)
    {}
};

/// @brief Test c=a+b for matrices
class matrix_add : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a + p_b; }

public:
    /// @brief Set me up
    matrix_add(const size_type runs, const size_type m, const size_t n)
        : matrix_performance_test("matrix_add", runs, m, n)
    {}
};

/// @brief Test c=a+b+a+b
class matrix_multiple_add : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a + p_b + p_a + p_b; }

public:
    /// @brief Set me up
    matrix_multiple_add(const size_type runs, const size_type m, const size_t n)
        : matrix_performance_test("matrix_multiple_add", runs, m, n)
    {}
};

/// @brief Test c = a - b - 2 + a - b + 2 for matrices
class matrix_mixed_add_sub : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c = p_a + p_b + p_a + p_b; }

public:
    /// @brief Set me up
    matrix_mixed_add_sub(const size_type runs, const size_type m, const size_t n)
        : matrix_performance_test("matrix_mixed_add_sub", runs, m, n)
    {}
};

/// @brief Test c = a - b - 2 + a - b + 2 for vector

} // namespace test
} // namespace la
#endif
