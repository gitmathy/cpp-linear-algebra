#ifndef LA_TEST_DECOMPOSE_H
#define LA_TEST_DECOMPOSE_H

#include "includes/algorithms/decompositions.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Solve x= A^-1 * rhs for row wise stored matrix
class decompose_row_solve_row_matrix : public performance_test
{
protected:
    /// @brief Matrix to be decomposed
    matrix<double, ROW_WISE> p_a;

    /// @brief rhs
    vector<double> p_rhs;

    /// @brief Number of rows and columns
    size_type p_size;

    /// @brief Execute a single test
    void run_single_test() override;

public:
    /// @brief Set me up
    decompose_row_solve_row_matrix(const size_type runs, const size_type n)
        : performance_test("decompose_solve_row_matrix", runs), p_a(0, 0), p_rhs(0), p_size(n)
    {}

    /// @brief Setup the test
    void setup() override;

    /// @brief Tear down the test
    void tear_down() override;

    /// @brief Get number of rows used for testing
    inline size_type rows() const override { return p_size; }

    /// @brief Get number of columns used for testing
    inline size_type cols() const override { return p_size; }
};

/// @brief Solve x= A^-1 * rhs for column wise stored matrix but row wise lu decomposed matrix
class decompose_row_solve_col_matrix : public performance_test
{
protected:
    /// @brief Matrix to be decomposed
    matrix<double, COLUMN_WISE> p_a;

    /// @brief rhs
    vector<double> p_rhs;

    /// @brief Number of rows and columns
    size_type p_size;

    /// @brief Execute a single test
    void run_single_test() override;

public:
    /// @brief Set me up
    decompose_row_solve_col_matrix(const size_type runs, const size_type n)
        : performance_test("decompose_row_solve_col_matrix", runs), p_a(0, 0), p_rhs(0), p_size(n)
    {}

    /// @brief Setup the test
    void setup() override;

    /// @brief Tear down the test
    void tear_down() override;

    /// @brief Get number of rows used for testing
    inline size_type rows() const override { return p_size; }

    /// @brief Get number of columns used for testing
    inline size_type cols() const override { return p_size; }
};

/// @brief Solve x= A^-1 * rhs for column wise stored matrix and column wise lu decomposed matrix
class decompose_col_solve_col_matrix : public performance_test
{
protected:
    /// @brief Matrix to be decomposed
    matrix<double, COLUMN_WISE> p_a;

    /// @brief rhs
    vector<double> p_rhs;

    /// @brief Number of rows and columns
    size_type p_size;

    /// @brief Execute a single test
    void run_single_test() override;

public:
    /// @brief Set me up
    decompose_col_solve_col_matrix(const size_type runs, const size_type n)
        : performance_test("decompose_row_solve_col_matrix", runs), p_a(0, 0), p_rhs(0), p_size(n)
    {}

    /// @brief Setup the test
    void setup() override;

    /// @brief Tear down the test
    void tear_down() override;

    /// @brief Get number of rows used for testing
    inline size_type rows() const override { return p_size; }

    /// @brief Get number of columns used for testing
    inline size_type cols() const override { return p_size; }
};

} // namespace test
} // namespace la
#endif
