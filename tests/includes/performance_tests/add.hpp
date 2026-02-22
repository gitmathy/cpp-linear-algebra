#ifndef LA_TEST_ADD_TEST_H
#define LA_TEST_ADD_TEST_H

#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
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
            p_C_row = p_A_row + p_B_row + p_A_row + p_B_row;
        } else {
            p_C_col = p_A_col + p_B_col + p_A_col + p_B_col;
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
