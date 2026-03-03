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
template <storage_type StorageT>
class matrix_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_C_row = p_A_row + p_B_row;
        } else {
            p_C_col = p_A_col + p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_add(const size_type runs)
        : performance_test(std::string("matrix_add ") + (StorageT == ROW_WISE ? "row" : "col"),
                           "Testing c = a+b", runs)
    {}
};

/// @brief Test c=a+b+a+b for matrices
template <storage_type StorageT>
class matrix_multiple_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_C_row = p_A_row + p_B_row + p_A_row + p_B_row;
        } else {
            p_C_col = p_A_col + p_B_col + p_A_col + p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_multiple_add(const size_type runs)
        : performance_test(std::string("matrix_multiple_add ") +
                               (StorageT == ROW_WISE ? "row" : "col"),
                           "Testing c = a+b+a+b", runs)
    {}
};

/// @brief Test c = a - b - 2 + a - b + 2 for matrices
template <storage_type StorageT>
class matrix_mixed_add_sub : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_C_row = p_A_row - p_B_row - 2. + p_A_row - p_B_row + 2.;
        } else {
            p_C_col = p_A_col - p_B_col - 2. + p_A_col - p_B_col + 2.;
        }
    }

public:
    /// @brief Set me up
    matrix_mixed_add_sub(const size_type runs)
        : performance_test(std::string("matrix_mixed_add_sub ") +
                               (StorageT == ROW_WISE ? "row" : "col"),
                           "Testing  c = -a- b-2+a-b+2", runs)
    {}
};

/// @brief Test c= a*b (blocked) for row based matrices
template <storage_type StorageLeftT, storage_type StorageRightT>
class matrix_multiply_blocked_row : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageLeftT == ROW_WISE && StorageRightT == COLUMN_WISE) {
            p_C_row = algorithm::matrix_multiplication_row<double>::multiply(p_A_row, p_B_col);
        } else if constexpr (StorageLeftT == ROW_WISE && StorageRightT == ROW_WISE) {
            p_C_row = algorithm::matrix_multiplication_row<double>::multiply(p_A_row, p_B_row);
        } else if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == ROW_WISE) {
            p_C_row = algorithm::matrix_multiplication_row<double>::multiply(p_A_col, p_B_row);
        } else {
            p_C_row = algorithm::matrix_multiplication_row<double>::multiply(p_A_col, p_B_col);
        }
    }

public:
    /// @brief Set me up
    matrix_multiply_blocked_row(const size_type runs, size_type size)
        : performance_test(std::string("matrix_multiply_blocked_row ") +
                               std::string(StorageLeftT == ROW_WISE ? "row * " : "col * ") +
                               std::string(StorageRightT == ROW_WISE ? "row" : "col"),
                           "Testing  C = A*B", runs),
          p_size(size)
    {}

    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

/// @brief Test c= a*b (blocked) for column based matrices
template <storage_type StorageLeftT, storage_type StorageRightT>
class matrix_multiply_blocked_col : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageLeftT == ROW_WISE && StorageRightT == COLUMN_WISE) {
            p_C_col = p_A_row * p_B_col;
        } else if constexpr (StorageLeftT == ROW_WISE && StorageRightT == ROW_WISE) {
            p_C_col = p_A_row * p_B_row;
        } else if constexpr (StorageLeftT == COLUMN_WISE && StorageRightT == ROW_WISE) {
            p_C_col = p_A_col * p_B_row;
        } else {
            p_C_col = p_A_col * p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_multiply_blocked_col(const size_type runs, size_type size)
        : performance_test(std::string("matrix_multiply_blocked_col ") +
                               std::string(StorageLeftT == ROW_WISE ? "row * " : "col * ") +
                               std::string(StorageRightT == ROW_WISE ? "row" : "col"),
                           "Testing  C = A*B", runs),
          p_size(size)
    {}

    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

/// @brief Testing c = a + b where a is row-wise, b is column-wise and c is row-wise
class matrix_add_sub_mixed_storage : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_C_row = p_A_row + p_B_col; }

public:
    /// @brief Set me up
    matrix_add_sub_mixed_storage(const size_type runs)
        : performance_test("matrix_add_sub_mixed_storage", "Testing c = a + b", runs)
    {}
};

} // namespace test
} // namespace la
#endif
