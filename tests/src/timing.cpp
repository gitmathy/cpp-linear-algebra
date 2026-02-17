#include "tests/includes/timing.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace la
{
namespace test
{

/// ===============================================
/// T I M E R
/// ===============================================

timer::~timer()
{
    if (p_end != nullptr)
    {
        delete p_end;
    }
}

void timer::restart()
{
    if (p_end != nullptr)
    {
        delete p_end;
        p_end = nullptr;
    }
    p_start = std::chrono::high_resolution_clock::now();
}

duration_type timer::stop()
{
    if (p_end == nullptr)
        p_end = new std::chrono::time_point<std::chrono::high_resolution_clock>;
    *p_end = std::chrono::high_resolution_clock::now();
    return *p_end - p_start;
}

/// ===============================================
/// T I M E   R E P O R T
/// ===============================================

time_report *time_report::p_instance = nullptr;

time_report &time_report::get()
{
    if (p_instance == nullptr)
    {
        p_instance = new time_report();
    }
    return *p_instance;
}

void time_report::record(const std::string &what, const duration_type &time)
{
    auto fit = p_timings.find(what);
    if (fit == p_timings.end())
    {
        p_timings.emplace(what, timing_entry({time, 1}));
    }
    else
    {
        fit->second.calls += 1;
        fit->second.duration += time;
    }
}

namespace time_reporting_helper
{
template <typename T> inline std::size_t num_digits(T number)
{
    std::size_t digits = 0;
    while (number != 0)
    {
        number /= 10;
        digits++;
    }
    return digits;
}
} // namespace time_reporting_helper

void time_report::report()
{
    duration_type total_elapsed_seconds = p_timer.get();

    if (p_timings.empty())
    {
        std::cout << "Timing Report (no recorded timings)\n";
        return;
    }

    std::size_t max_descr_width = std::max_element(p_timings.begin(), p_timings.end(), [](const auto &a, const auto &b)
                                                   { return a.first.length() < b.first.length(); })
                                      ->first.length();
    max_descr_width = max_descr_width < 11 ? 11 : max_descr_width;
    std::size_t max_digits_calls = time_reporting_helper::num_digits(
        std::max_element(p_timings.begin(), p_timings.end(),
                         [](const auto &a, const auto &b)
                         {
                             return time_reporting_helper::num_digits(a.second.calls) <
                                    time_reporting_helper::num_digits(b.second.calls);
                         })
            ->second.calls);
    std::ostringstream stringstr;
    std::cout << "Timing Report\n";
    stringstr << "| " << std::left << std::setw(max_descr_width) << "description" << " | " << std::left
              << std::setw(max_digits_calls) << '#' << " | " << std::left << std::setw(13) << "duration [s]" << " | "
              << std::left << std::setw(17) << "avg duration [s] |\n";
    for (std::size_t i = 0; i < max_descr_width + 3; ++i)
        stringstr << '-';
    stringstr << '|';
    for (std::size_t i = 0; i < max_digits_calls + 2; ++i)
        stringstr << '-';
    stringstr << "|---------------|-------------------" << std::endl;
    for (auto it = p_timings.begin(); it != p_timings.end(); ++it)
    {
        stringstr << "| " << std::left << std::setw(max_descr_width) << it->first << " | " << std::right
                  << std::setw(max_digits_calls) << it->second.calls << " | " << std::right << std::setw(13)
                  << std::setprecision(4) << std::fixed << it->second.duration.count() << " | " << std::setw(16)
                  << std::setprecision(4) << std::fixed << (it->second.duration.count() / it->second.calls) << " |\n";
    }
    for (std::size_t i = 0; i < max_descr_width + 3; ++i)
        stringstr << '-';
    stringstr << '|';
    for (std::size_t i = 0; i < max_digits_calls + 2; ++i)
        stringstr << '-';
    stringstr << "|---------------|-------------------" << std::endl;
    stringstr << "| " << std::left << std::setw(max_descr_width) << "Overall" << " | " << std::right
              << std::setw(max_digits_calls) << "1" << " | " << std::right << std::setw(13) << std::setprecision(4)
              << std::fixed << total_elapsed_seconds.count() << " |       N/A        |";
    std::cout << stringstr.str() << std::endl;
}

} // namespace test
} // namespace la
