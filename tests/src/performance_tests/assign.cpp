#include "tests/includes/performance_tests/assign.hpp"
#include <numeric>

namespace la
{
namespace test
{

void matrix_assign_storage_missmatch::setup()
{
    p_a.resize(p_rows, p_cols);
    p_x.resize(p_rows, p_cols);
    init(p_x);
}

void matrix_assign_storage_missmatch::tear_down()
{
    p_a.resize(0, 0);
    p_x.resize(0, 0);
}

void vector_assign_matrix_vector_mult::setup()
{
    p_a.resize(p_rows, p_cols);
    init(p_a);
    p_x.resize(p_cols);
    init(p_x);
    p_y.resize(p_rows);
}

void vector_assign_matrix_vector_mult::tear_down()
{
    p_a.resize(0, 0);
    p_x.resize(0);
    p_y.resize(0);
}

} // namespace test
} // namespace la
