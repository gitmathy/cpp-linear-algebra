#ifndef LA_TEST_ASSIGN_TEST_H
#define LA_TEST_ASSIGN_TEST_H

#include "includes/la.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Test a=b for vectors
class vector_assign : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a = p_b; }

public:
    /// @brief Set me up
    vector_assign(const size_type runs, const size_type dim)
        : vector_performance_test("vector_assign", runs, dim)
    {}
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
    {}
};

/// @brief Test c=(a+b) for vectors
class vector_assign_add_sum : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c += (p_a + p_b); }

public:
    /// @brief Set me up
    vector_assign_add_sum(const size_type runs, const size_type dim)
        : vector_performance_test("vector_assign_add_sum", runs, dim)
    {}
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
    {}
};

/// @brief Test a=b for matrices of different StorageT layout
class matrix_assign_storage_missmatch : public matrix_performance_test
{
private:
    /// @brief Matrix of other StorageT layout
    la::matrix<double, COLUMN_WISE> p_x;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a = p_x; }

public:
    /// @brief Set me up
    matrix_assign_storage_missmatch(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("matrix_assign_storage_missmatch", runs, m, n), p_x(0, 0)
    {}
    /// @brief Allocate memory
    void setup() override;

    /// @brief Free memory
    void tear_down() override;
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
    {}
};

/// @brief Test c+=(a+b) for matrices
class matrix_assign_add_sum : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a += p_b; }

public:
    /// @brief Set me up
    matrix_assign_add_sum(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("matrix_assign_add_sum", runs, m, n)
    {}
};

/// @brief Test y=A*x for matrix*vector
class vector_assign_matrix_vector_mult : public matrix_performance_test
{
private:
    /// @brief Used vectors
    vector<double> p_x, p_y;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_y = p_a * p_x; }

public:
    /// @brief Set me up
    vector_assign_matrix_vector_mult(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("vector_assign_matrix_vector_mult", runs, m, n)
    {}
    /// @brief Allocate memory
    void setup() override;

    /// @brief Free memory
    void tear_down() override;
};

} // namespace test
} // namespace la
#endif
