#include "tests/includes/performance_tests/decompose.hpp"
#include <numeric>

namespace la {
namespace test {

void decompose_row_solve_row_matrix::setup()
{
    p_a.resize(p_size, p_size);
    p_rhs.resize(p_size);
    init(p_a);
    init(p_rhs);
}

void decompose_row_solve_row_matrix::tear_down()
{
    p_a.resize(0, 0);
    p_rhs.resize(0);
}

void decompose_row_solve_row_matrix::run_single_test()
{
    la::algorithm::lu_decomposition<double, ROW_WISE> decomposition(p_a);
    vector<double> x = decomposition.solve(p_rhs);
}

void decompose_row_solve_col_matrix::setup()
{
    p_a.resize(p_size, p_size);
    p_rhs.resize(p_size);
    init(p_a);
    init(p_rhs);
}

void decompose_row_solve_col_matrix::tear_down()
{
    p_a.resize(0, 0);
    p_rhs.resize(0);
}

void decompose_row_solve_col_matrix::run_single_test()
{
    la::algorithm::lu_decomposition<double, ROW_WISE> decomposition(p_a);
    vector<double> x = decomposition.solve(p_rhs);
}

void decompose_col_solve_col_matrix::setup()
{
    p_a.resize(p_size, p_size);
    p_rhs.resize(p_size);
    init(p_a);
    init(p_rhs);
}

void decompose_col_solve_col_matrix::tear_down()
{
    p_a.resize(0, 0);
    p_rhs.resize(0);
}

void decompose_col_solve_col_matrix::run_single_test()
{
    la::algorithm::lu_decomposition<double, COLUMN_WISE> decomposition(p_a);
    vector<double> x = decomposition.solve(p_rhs);
}

} // namespace test
} // namespace la
