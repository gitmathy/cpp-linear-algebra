#ifndef LA_TEST_ASSIGN_TEST_H
#define LA_TEST_ASSIGN_TEST_H

#include "tests/includes/performance_test.hpp"

namespace la
{
namespace test
{

/// @brief Test a=b for vectors
class vector_assign : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a = p_b; }

public:
    /// @brief Set me up
    vector_assign(const size_type runs, const size_type dim) : vector_performance_test("vector_assign", runs, dim) {}
};

/// @brief Test a+=b for vectors
class vector_assign_add : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a += p_b; }

public:
    /// @brief Set me up
    vector_assign_add(const size_type runs, const size_type dim)
        : vector_performance_test("vector_assign_add", runs, dim)
    {
    }
};

/// @brief Test a=b for matrices
class matrix_assign : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a = p_b; }

public:
    /// @brief Set me up
    matrix_assign(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("matrix_assign", runs, m, n)
    {
    }
};

/// @brief Test a+=b for matrices
class matrix_assign_add : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a += p_b; }

public:
    /// @brief Set me up
    matrix_assign_add(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("matrix_assign_add", runs, m, n)
    {
    }
};

} // namespace test
} // namespace la
#endif
