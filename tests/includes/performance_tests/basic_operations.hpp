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
#include "la/sparse"
#include "tests/includes/performance_test.hpp"
#include <random>

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

    inline void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

// ===============================================
// S P A R S E   M A T R I C E S
// ===============================================

class sparse_matrix_build : public performance_test
{
private:
    sparse_matrix_builder<double> p_a_build;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        sparse_matrix<double> a = std::move(p_a_build.assemble());
    }

public:
    /// @brief Set me up
    sparse_matrix_build(const size_type runs)
        : performance_test("sparse_matrix_build", "Assemble sparse matrix", runs),
          p_a_build(SPARSE_SIZE, SPARSE_SIZE)
    {}

    inline void setup() override
    {
        std::mt19937 gen(42);
        std::uniform_int_distribution<size_type> rand_nnz_row(1, SPARSE_MAX_NNZ_ROW);
        std::uniform_int_distribution<size_type> rand_col_idx(1, SPARSE_SIZE);
        for (size_type i = 0; i < p_a_build.rows(); ++i) {
            for (size_type nnz = 0; nnz < rand_nnz_row(gen); ++nnz) {
                p_a_build(i, rand_col_idx(gen)) = get_random<double>();
            }
        }
    }
};

class sparse_matrix_mult : public performance_test
{
private:
    vector<double> p_x;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_A_sparse *p_x; }

public:
    /// @brief Set me up
    sparse_matrix_mult(const size_type runs)
        : performance_test("sparse_matrix_mult", "Multiply with a sparse matrix", runs),
          p_x(SPARSE_SIZE)
    {}

    inline void setup() override
    {
        p_x.resize(p_A_sparse.cols());
        init(p_x);
    }
};

} // namespace test
} // namespace la
#endif
