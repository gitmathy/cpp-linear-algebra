#include "tests/includes/collection.hpp"
#include "tests/includes/performance_test.hpp"
#include "tests/includes/unit_test.hpp"
#include <iomanip>
#include <numeric>
#include <sstream>

namespace la {
namespace test {

size_type test_collection::numer_of_tests(const std::string &label) const
{
    size_type number = 0;
    if (label == "all") {
        for (auto &n : p_tests) {
            number += n.second.size();
        }
        return number;
    }
    auto fit = p_tests.find(label);
    return fit == p_tests.end() ? 0 : fit->second.size();
}

size_type test_collection::max_name_length(const std::string &label_filter) const
{
    size_type max_name_length = 0;
    for (auto &labeled : p_tests) {
        if (label_filter == "all" || labeled.first == label_filter) {
            size_type labeled_max_name = 0;
            for (auto &test : labeled.second) {
                labeled_max_name = std::max(labeled_max_name, test->name().size());
            }
            max_name_length = std::max(max_name_length, labeled_max_name);
        }
    }
    return max_name_length;
}

size_type test_collection::max_label_length(const std::string &label_filter) const
{
    size_type max_label_length = 0;
    for (auto &labeled : p_tests) {
        if (label_filter == "all" || labeled.first == label_filter) {
            max_label_length = std::max(max_label_length, labeled.first.size());
        }
    }
    return max_label_length;
}

void test_collection::transfer(const std::string &label, std::unique_ptr<base_test> new_test)
{
    if (new_test == nullptr)
        return;
    std::stringstream strs;
    strs << "* adding: " << new_test->name();
    log(strs, INFO);
    auto fit = p_tests.find(label);
    if (fit == p_tests.end()) {
        // the label does not exists so far, so create the label
        p_tests.emplace(std::make_pair(label, std::list<std::unique_ptr<base_test>>()));
    }

    p_tests[label].push_back(std::move(new_test));
}

int test_collection::run(const std::string &label_filter)
{
    timer execution_timer;
    std::stringstream strs;
    strs << "================================================================================\n";
    strs << "    TESTING: " << p_name << '\n';
    strs << "Label          : " << label_filter << '\n';
    strs << "Number of tests: " << numer_of_tests(label_filter) << '\n';
    strs << "================================================================================\n";
    log(strs, INFO);

    int result = 0, failed_tests = 0, test_result, performed_tests = 0;
    for (auto &labeled : p_tests) {
        if (label_filter == "all" || labeled.first == label_filter) {
            for (auto &test : labeled.second) {
                strs << "--------- Test " << test->name() << " (" << labeled.first
                     << ")  ---------";
                log(strs, INFO);
                strs << "Setup test: " << test->name();
                log(strs, DEBUG);
                test->setup();
                strs << "Execute test: " << test->name();
                log(strs, DEBUG);
                test_result = test->execute();
                ++performed_tests;
                failed_tests += test_result > 0 ? 1 : 0;
                result += test_result;
                strs << "Tear down test: " << test->name();
                log(strs, DEBUG);
                test->tear_down();
            }
        }
    }

    execution_timer.stop();
    report(label_filter);

    strs << "\n================================================================================\n";
    strs << "    SUMMARY: " << p_name << '\n';
    strs << "Performed tests     : " << performed_tests << '\n';
    strs << "Total test result   : " << result << '\n';
    strs << "Failed tests        : " << failed_tests << '\n';
    strs << "Total execution time: " << std::setprecision(4) << execution_timer.get().count()
         << "s\n";
    strs << "================================================================================\n";
    log(strs, INFO);
    return result;
}

void unit_test_collection::report(const std::string &label_filter)
{
    std::stringstream strs;
    strs << "\n----------------------------------------\n";
    strs << "    ERROR REPORT: " << p_name << '\n';
    strs << "----------------------------------------";
    this->log(strs, INFO);

    for (auto &labeled : p_tests) {
        if (label_filter == "all" || labeled.first == label_filter) {
            for (auto &test : labeled.second) {
                const unit_test *const unit_test_p = dynamic_cast<unit_test *>(test.get());
                if (unit_test_p->failed()) {
                    for (auto &error : unit_test_p->errors()) {
                        strs << "* [" << test->name() << "]: " << error << '\n';
                    }
                    this->log(strs, INFO);
                }
            }
        }
    }
    this->log("----------------------------------------", INFO);
}

performance_test_collection::performance_test_collection(
    const size_type runs, std::shared_ptr<sample_la_structures<double>> samples)
    : test_collection("performance tests"), p_samples(std::move(samples)), p_runs(runs)
{}

void performance_test_collection::report(const std::string &label_filter)
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
    for (auto &labeled : p_tests) {
        if (label_filter == "all" || labeled.first == label_filter) {
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
            }
        }
    }
    log(table_row_break.str(), INFO);
}

} // namespace test
} // namespace la
