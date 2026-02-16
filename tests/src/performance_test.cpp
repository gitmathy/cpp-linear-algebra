#include "tests/includes/performance_test.hpp"
#include <numeric>

namespace la
{
namespace test
{

int performance_test::execute()
{
    for (size_type i = 0; i < p_runs; ++i)
    {
        start_single_test();
        run_single_test();
        stop_single_test();
    }
    return 0;
}

vector_performance_test::vector_performance_test(const std::string &name, const size_type runs, const size_type rows)
    : performance_test(name, runs), p_rows(rows), p_a(), p_b(), p_c()
{
}

void vector_performance_test::setup()
{
    p_a.resize(p_rows);
    init(p_a);
    p_b.resize(p_rows);
    init(p_b);
    p_c.resize(p_rows);
    init(p_c);
}

void vector_performance_test::tear_down()
{
    p_a.resize(0);
    p_b.resize(0);
    p_c.resize(0);
}

matrix_performance_test::matrix_performance_test(const std::string &name, const size_type runs, const size_type m,
                                                 const size_type n)
    : performance_test(name, runs), p_rows(m), p_cols(n), p_a(0, 0), p_b(0, 0), p_c(0, 0)
{
}

void matrix_performance_test::setup()
{
    p_a.resize(p_rows, p_cols);
    init(p_a);
    p_b.resize(p_rows, p_cols);
    init(p_b);
    p_c.resize(p_rows, p_cols);
    init(p_c);
}

void matrix_performance_test::tear_down()
{
    p_a.resize(0, 0);
    p_b.resize(0, 0);
    p_c.resize(0, 0);
}

} // namespace test
} // namespace la
