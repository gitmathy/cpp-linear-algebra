/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/performance_test.hpp
/// @brief Definition of performance tests
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_PERFORMANCE_TEST_H
#define LA_TEST_INCLUDES_PERFORMANCE_TEST_H

#include "la/dense"
#include "tests/includes/base_test.hpp"
#include "tests/includes/samples.hpp"
#include "tests/includes/timing.hpp"
#include <list>
#include <memory>

namespace la {
namespace test {

/// @brief Single performance test used as a base class
class performance_test : public base_test
{
private:
    /// @brief Timekeeping
    timer p_timer;

    /// @brief timings
    std::list<duration_type> p_timings;

    /// @brief Start the timing of a single test
    inline void start_single_test() { p_timer.restart(); }

    /// @brief Stop time and record the runtime
    inline void stop_single_test() { p_timings.push_back(p_timer.get()); }

protected:
    /// @brief Number of runs
    size_type p_runs;

    /// @brief Sample matrices and vectors for the test
    std::shared_ptr<sample_la_structures<double>> p_samples;

    // As a simplification in the implementation, we to store references to matrices and vectors
    // from the samples while assuming that the size of samples is >=3.
    //
    // I know, that this breaks a nice dependency management but it helps to not always follow the
    // pointers.

    /// @brief Reference to default vectors taking from samples
    vector<double> &p_a_vec, &p_b_vec, &p_c_vec;

    /// @brief Reference to matrices
    matrix<double> &p_A, &p_B, &p_C;

    /// @brief Run a single test
    virtual void run_single_test() = 0;

public:
    /// @brief Construct a performance test
    performance_test(const std::string &name, const std::string &description, const size_type runs,
                     std::shared_ptr<sample_la_structures<double>> samples = get_default_samples());

    /// @brief Destruct a performance test
    virtual ~performance_test() = default;

    /// @brief Setup the test to make sure, matrices and vectors are of default size
    virtual void setup() override;

    /// @brief Run the test num-runs times
    int execute() override;

    /// @brief Tear down the test (reset samples)
    virtual void tear_down() override;

    /// @brief Get total execution time
    duration_type total_time() const;

    /// @brief Get average execution time
    duration_type average_time() const { return total_time() / executions(); }

    /// @brief Get number of executions
    inline size_type executions() const { return p_timings.size(); }

    /// @brief Get number of rows used for testing
    size_type mat_rows() const { return p_samples->mat_rows(); }

    /// @brief Get number of columns used for testing
    size_type mat_cols() const { return p_samples->mat_rows(); }

    /// @brief Get number of vector size
    size_type vec_rows() const { return p_samples->vec_rows(); };
};

} // namespace test
} // namespace la
#endif
