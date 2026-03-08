/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/performance_test.cpp
/// @brief Implementation of basic performance test
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/performance_test.hpp"
#include <numeric>

namespace la {
namespace test {

performance_test::performance_test(const std::string &name, const std::string &description,
                                   const size_type runs,
                                   std::shared_ptr<sample_la_structures<double>> samples)
    : base_test(name, description), p_timer(), p_timings(), p_runs(runs), p_samples(samples),
      p_a_vec(samples->vec(0)), p_b_vec(samples->vec(1)), p_c_vec(samples->vec(2)),
      p_A(samples->mat(0)), p_B(samples->mat(1)), p_C(samples->mat(2))
{}

duration_type performance_test::total_time() const
{
    return std::accumulate(p_timings.begin(), p_timings.end(), duration_type());
}

void performance_test::setup() { p_samples->reset(); }

int performance_test::execute()
{
    for (size_type i = 0; i < p_runs; ++i) {
        start_single_test();
        run_single_test();
        stop_single_test();
    }
    return 0;
}

void performance_test::tear_down() {}

} // namespace test
} // namespace la
