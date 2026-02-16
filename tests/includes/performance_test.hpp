#ifndef LA_TEST_PERFORMANCE_TEST_H
#define LA_TEST_PERFORMANCE_TEST_H

#include "includes/matrix.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"
#include "tests/includes/base_test.hpp"
#include "tests/includes/timing.hpp"
#include <list>
#include <numeric>

namespace la
{
namespace test
{

/// @brief Single performance test used as a base class
class performance_test : public base_test
{
protected:
    /// @brief Number of runs
    size_type p_runs;

    /// @brief Timekeeping
    timer p_timer;

    /// @brief timings
    std::list<duration_type> p_timings;

    /// @brief Start the timing of a single test
    inline void start_single_test() { p_timer.restart(); }

    /// @brief Stop time and record the runtime
    inline void stop_single_test() { p_timings.push_back(p_timer.get()); }

    /// @brief Run a single test
    virtual void run_single_test() = 0;

public:
    /// @brief Construct a performance test
    performance_test(const std::string &name, const size_type runs) : base_test(name), p_runs(runs), p_timings() {}

    /// @brief Destruct a performance test
    virtual ~performance_test() = default;

    /// @brief Setup the test
    virtual void setup() {};

    /// @brief Tear down the test
    virtual void tear_down() {};

    int execute();

    /// @brief Get total execution time
    duration_type total_time() const { return std::accumulate(p_timings.begin(), p_timings.end(), duration_type()); }

    /// @brief Get average execution time
    duration_type average_time() const { return total_time() / executions(); }

    /// @brief Get number of executions
    inline size_type executions() const { return p_timings.size(); }
};

template <typename T> inline double get_random() { return T((std::rand() / (T)RAND_MAX) * 2 - 1); }

/// @brief Initialize x with random values
template <typename la_struct> inline void init(la_struct &x)
{
    for (auto it = x.begin(); it != x.end(); ++it)
    {
        *it = get_random<typename la_struct::value_type>();
    }
}

/// @brief Base class for all vector performance tests
class vector_performance_test : public performance_test
{
protected:
    /// @brief Number of rows for the vector, i.e., size
    size_type p_rows;

    /// @brief Vectors used for performance tests
    la::vector<double> p_a, p_b, p_c;

public:
    /// @brief Setup the test
    vector_performance_test(const std::string &name, const size_type runs, const size_type rows);

    /// @brief Allocate memory
    void setup() override;

    /// @brief Free memory
    void tear_down() override;
};

/// @brief Base class for all matrix performance tests
class matrix_performance_test : public performance_test
{
protected:
    /// @brief matrix rows for testing
    size_type p_rows;

    /// @brief matrix columns for testing
    size_type p_cols;

    /// @brief Vectors used for performance tests
    la::matrix<double> p_a, p_b, p_c;

public:
    /// @brief Initialize p_a and p_b
    matrix_performance_test(const std::string &name, const size_type runs, const size_type m, const size_type n);

    /// @brief Allocate memory
    void setup() override;

    /// @brief Free memory
    void tear_down() override;
};

} // namespace test
} // namespace la
#endif
