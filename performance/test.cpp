#include "../includes/vector.hpp"
#include "includes/timing.hpp"
#include <iostream>

void time_constructor(const la::size_type n = 10000)
{
    TIMEME;
    la::vector<double> v(n);
}

int main()
{
    la_perf::time_report &timings = la_perf::time_report::get();

    std::cout << "Running performance tests" << std::endl;

    for (int i = 0; i < 1000; ++i)
    {
        time_constructor();
    }

    timings.report();
    return 0;
}
