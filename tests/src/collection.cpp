#include "tests/includes/collection.hpp"
#include "tests/includes/performance_test.hpp"
#include "tests/includes/unit_test.hpp"
#include <iomanip>
#include <ranges>
#include <sstream>

namespace la
{
namespace test
{

size_type test_collection::numer_of_tests(const std::string &label) const
{
    size_type number = 0;
    if (label == "all")
    {
        for (auto &n : p_tests)
        {
            number += n.second.size();
        }
        return number;
    }
    auto fit = p_tests.find(label);
    return fit == p_tests.end() ? 0 : fit->second.size();
}

void test_collection::transfer(const std::string &label, std::unique_ptr<base_test> new_test)
{
    if (new_test == nullptr)
        return;
    auto fit = p_tests.find(label);
    if (fit == p_tests.end())
    {
        // the label does not exists so far, so create the label
        p_tests.emplace(std::make_pair(label, std::list<std::unique_ptr<base_test>>()));
    }

    p_tests[label].push_back(std::move(new_test));
}

int test_collection::run(const std::string &label_filter)
{
    std::stringstream strs;
    strs << "================================================================================\n";
    strs << "    TESTING: " << p_name << '\n';
    strs << "Label          : " << label_filter << '\n';
    strs << "Number of tests: " << numer_of_tests(label_filter) << '\n';
    strs << "================================================================================\n\n";
    log(strs, INFO);

    int result = 0, failed_tests = 0, test_result, performed_tests = 0;
    for (auto &labeled :
         p_tests | std::views::filter([&](auto item) { return label_filter == "all" || item.first == label_filter; }))
    {
        for (auto &test : labeled.second)
        {
            strs << "--------- Test " << test->name() << " (" << labeled.first << ")\n";
            log(strs, INFO);
            strs << "Setup test: " << test->name() << '\n';
            log(strs, DEBUG);
            test->setup();
            strs << "Execute test: " << test->name() << '\n';
            log(strs, DEBUG);
            test_result = test->execute();
            ++performed_tests;
            failed_tests += test_result > 0 ? 1 : 0;
            result += test_result;
            strs << "Tear down test: " << test->name() << '\n';
            log(strs, DEBUG);
            test->tear_down();
        }
    }

    report(label_filter);

    strs << "================================================================================\n";
    strs << "    SUMMARY: " << p_name << '\n';
    strs << "Performed tests  : " << performed_tests << '\n';
    strs << "Total test result:" << result << '\n';
    strs << "Failed tests     :" << failed_tests << '\n';
    strs << "================================================================================\n\n";
    log(strs, INFO);
    return result;
}

void unit_test_collection::report(const std::string &label_filter)
{
    std::stringstream strs;
    for (auto &labeled :
         p_tests | std::views::filter([&](auto item) { return label_filter == "all" || item.first == label_filter; }))
    {
        for (auto &test : labeled.second)
        {
            const unit_test *const unit_test_p = dynamic_cast<unit_test *>(test.get());
            if (unit_test_p->failed())
            {
                for (auto &error : unit_test_p->errors())
                {
                    strs << "* [" << test->name() << "]: " << error << '\n';
                }
                this->log(strs, INFO);
            }
        }
    }
}

void performance_test_collection::report(const std::string &label_filter)
{
    std::stringstream strs;
    for (auto &labeled :
         p_tests | std::views::filter([&](auto item) { return label_filter == "all" || item.first == label_filter; }))
    {
        for (auto &test : labeled.second)
        {
            const performance_test *const perf_test_p = dynamic_cast<performance_test *>(test.get());
            strs << "* [" << test->name() << "] (# " << perf_test_p->executions() << "): total " << std::setprecision(4)
                 << perf_test_p->total_time() << "s, average " << perf_test_p->average_time() << "s\n";
        }
    }
}

} // namespace test
} // namespace la
