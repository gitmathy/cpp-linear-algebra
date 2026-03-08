/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/collection.cpp
/// @brief Implementation of test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/collection.hpp"
#include "tests/includes/timing.hpp"
#include "tests/includes/unit_test.hpp"
#include <iomanip>
#include <numeric>
#include <sstream>

namespace la {
namespace test {

bool label_in_filter(const std::string &label, const std::set<std::string> &label_filter)
{
    if (label_filter.empty()) {
        return true;
    }
    return (label_filter.find(label) != label_filter.end());
}

size_type test_collection::numer_of_tests(const std::set<std::string> &label_filter) const
{
    size_type number = 0;
    for (auto &n : p_tests) {
        if (label_in_filter(n.first, label_filter)) {
            number += n.second.size();
        }
    }
    return number;
}

size_type test_collection::max_name_length(const std::set<std::string> &label_filter) const
{
    size_type max_name_length = 0;
    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
            size_type labeled_max_name = 0;
            for (auto &test : labeled.second) {
                labeled_max_name = std::max(labeled_max_name, test->name().size());
            }
            max_name_length = std::max(max_name_length, labeled_max_name);
        }
    }
    return max_name_length;
}

size_type test_collection::max_label_length(const std::set<std::string> &label_filter) const
{
    size_type max_label_length = 0;
    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
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

int test_collection::run(const std::set<std::string> &label_filter)
{
    timer execution_timer;
    std::stringstream strs;
    std::stringstream labels_strs;
    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
            labels_strs << labeled.first << " ";
        }
    }

    strs << "================================================================================\n";
    strs << "    TESTING: " << p_name << '\n';
    strs << "Label          : " << labels_strs.str() << '\n';
    strs << "Number of tests: " << numer_of_tests(label_filter) << '\n';
    strs << "================================================================================\n";
    log(strs, INFO);

    int result = 0, failed_tests = 0, test_result, performed_tests = 0;
    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
            for (auto &test : labeled.second) {
                strs << "--------- Test " << test->name() << " (" << labeled.first
                     << ")  ---------";
                log(strs, INFO);
                strs << "Test description: " << test->description() << "\nSetup test...";
                log(strs, DEBUG);
                test->setup();
                strs << "Execute test...";
                log(strs, DEBUG);
                test_result = test->execute();
                ++performed_tests;
                failed_tests += test_result > 0 ? 1 : 0;
                result += test_result;
                strs << "Tear down test...";
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

} // namespace test
} // namespace la
