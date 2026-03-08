/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/performance_tests/performance_test_collection.cpp
/// @brief Definition of performance test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/performance_tests/performance_test_collection.hpp"
#include "tests/includes/performance_test.hpp"
#include <iomanip>

namespace la {
namespace test {

performance_test_collection::performance_test_collection(
    const size_type runs, std::shared_ptr<sample_la_structures<double>> samples)
    : test_collection("performance tests"), p_samples(std::move(samples)), p_runs(runs)
{}

void performance_test_collection::report(const std::set<std::string> &label_filter)
{
    std::stringstream strs;
    strs << '\n' << std::string(80, '=') << '\n';
    strs << "       REPORT: " << p_name << "\n\n";
    strs << "   # runs:              " << p_runs << '\n'
         << "   default vector size: " << p_samples->vec_rows() << '\n'
         << "   default matrix rows: " << p_samples->mat_rows() << '\n'
         << "   default matrix cols: " << p_samples->vec_rows() << '\n';
    strs << std::string(80, '=') << '\n';
    this->log(strs, INFO);

    const size_type name_length = max_name_length(label_filter),
                    label_length = max_label_length(label_filter), run_length = 4, time_length = 10;

    std::stringstream table_row_break;
    table_row_break << '+' << std::string(name_length + 2, '-') << '+'
                    << std::string(label_length + 2, '-') << '+' << "------+" << "------------+"
                    << "------------+";
    log(table_row_break.str(), INFO);
    strs << "| " << std::setw(name_length) << std::left << "test name" << " | ";
    strs << std::setw(label_length) << std::left << "label" << " | ";
    strs << std::setw(run_length) << std::left << "runs" << " | ";
    strs << std::setw(time_length) << std::left << "total[s]" << " | ";
    strs << std::setw(time_length) << std::left << "avg[s]" << " |";
    log(strs, INFO);
    log(table_row_break.str(), INFO);

    duration_type test_time = duration_type();

    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
            for (auto &test : labeled.second) {
                const performance_test *const perf_test_p =
                    dynamic_cast<performance_test *>(test.get());
                strs << "| " << std::setw(name_length) << std::left << test->name() << " | ";
                strs << std::setw(label_length) << std::left << labeled.first << " | ";
                strs << std::setw(run_length) << std::setprecision(4) << std::right
                     << perf_test_p->executions() << " | ";
                strs << std::setw(time_length) << std::setprecision(4) << std::right
                     << perf_test_p->total_time().count() << " | ";
                strs << std::setw(time_length) << std::setprecision(4) << std::right
                     << perf_test_p->average_time().count() << " |";
                log(strs, INFO);
                test_time += perf_test_p->total_time();
            }
        }
    }
    log(table_row_break.str(), INFO);
    strs << "| " << std::setw(name_length) << std::left << "total" << " | ";
    strs << std::setw(label_length) << std::left << ' ' << " | ";
    strs << std::setw(run_length) << std::left << " " << " | ";
    strs << std::setw(time_length) << std::setprecision(4) << std::right << test_time.count()
         << " | ";
    strs << std::setw(time_length) << std::left << ' ' << " |";
    log(strs, INFO);
    log(table_row_break.str(), INFO);
}

} // namespace test
} // namespace la
