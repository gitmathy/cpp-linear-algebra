#ifndef LA_TEST_ASSIGN_TEST_H
#define LA_TEST_ASSIGN_TEST_H

#include "includes/la.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

// ===============================================
// V E C T O R
// ===============================================

/// @brief Test a=b for vectors
class vector_assign : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a_vec = p_b_vec; }

public:
    /// @brief Set me up
    vector_assign(const size_type runs) : performance_test("vector_assign", runs) {}
};

/// @brief Test a+=b for vectors
class vector_add_assign : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a_vec += p_b_vec; }

public:
    /// @brief Set me up
    vector_add_assign(const size_type runs) : performance_test("vector_add_assign", runs) {}
};

/// @brief Test c += (a+b) for vectors
class vector_sum_add_assign : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_c_vec += (p_a_vec + p_b_vec); }

public:
    /// @brief Set me up
    vector_sum_add_assign(const size_type runs) : performance_test("vector_sum_add_assign", runs) {}
};

// ===============================================
// M A T R I C E S
// ===============================================

/// @brief Test a=b for matrices
template <storage_type StorageT>
class matrix_assign : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_A_row = p_B_row;
        } else {
            p_A_col = p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_assign(const size_type runs)
        : performance_test(std::string("matrix_assign ") + (StorageT == ROW_WISE ? "row" : "col"),
                           runs)
    {}
};

/// @brief Test a += b for matrices
template <storage_type StorageT>
class matrix_assign_add : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_A_row += p_B_row;
        } else {
            p_A_col += p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_assign_add(const size_type runs)
        : performance_test(
              std::string("matrix_assign_add ") + (StorageT == ROW_WISE ? "row" : "col"), runs)
    {}
};

/// @brief Test c += (a+b) for matrices
template <storage_type StorageT>
class matrix_assign_add_sum : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_A_row += p_B_row;
        } else {
            p_A_col += p_B_col;
        }
    }

public:
    /// @brief Set me up
    matrix_assign_add_sum(const size_type runs)
        : performance_test(
              std::string("matrix_assign_add_sum ") + (StorageT == ROW_WISE ? "row" : "col"), runs)
    {}
};

/// @brief Test y = A*x for matrix*vector
template <storage_type StorageT>
class vector_assign_matrix_vector_mult : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_a_vec = p_A_row * p_b_vec;
        } else {
            p_a_vec = p_A_col * p_b_vec;
        }
    }

public:
    /// @brief Set me up
    vector_assign_matrix_vector_mult(const size_type runs)
        : performance_test(std::string("vector_assign_matrix_vector_mult ") +
                               (StorageT == ROW_WISE ? "row" : "col"),
                           runs)
    {}
    /// @brief Allocate memory
    void setup() override
    {
        p_samples->adjust(p_samples->mat_cols(), p_samples->mat_rows(), p_samples->mat_cols());
    }
};

/// @brief Test a=b for matrices of different StorageT layout
class matrix_assign_storage_mismatch : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_A_row = p_A_col; }

public:
    /// @brief Set me up
    matrix_assign_storage_mismatch(const size_type runs)
        : performance_test("matrix_assign_storage_mismatch", runs)
    {}
};

} // namespace test
} // namespace la
#endif
