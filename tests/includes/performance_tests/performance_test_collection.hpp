/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/performance_tests/performance_test_collection.hpp
/// @brief Declaration of performance test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_PERFORMANCE_TEST_COLLECTION_HPP
#define LA_TEST_INCLUDES_PERFORMANCE_TEST_COLLECTION_HPP

#include "la/util/types.hpp"
#include "tests/includes/collection.hpp"
#include "tests/includes/samples.hpp"
#include <memory>

namespace la {
namespace test {

/// @brief Dedicated class for collection of performance tests
class performance_test_collection : public test_collection
{
private:
    /// @brief Sample matrices and vectors for the test
    std::shared_ptr<sample_la_structures<double>> p_samples;

    /// @brief Number of runs
    size_type p_runs;

    /// @brief Report all timings
    void report(const std::set<std::string> &label_filter) override;

public:
    /// @brief Constructor using dependency injection for the samples
    performance_test_collection(
        const size_type runs,
        std::shared_ptr<sample_la_structures<double>> samples = get_default_samples());

    /// @brief Default destructor
    ~performance_test_collection() = default;
};

} // namespace test
} // namespace la
#endif
