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

vector_performance_test::vector_performance_test(const std::string &name, const size_type runs, const size_type dim)
    : performance_test(name, runs), p_a(dim), p_b(dim)
{
    init(p_a);
    init(p_b);
}

matrix_performance_test::matrix_performance_test(const std::string &name, const size_type runs, const size_type dim)
    : performance_test(name, runs), p_a(dim), p_b(dim)
{
    init(p_a);
    init(p_b);
}

} // namespace test
} // namespace la
