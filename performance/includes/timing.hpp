#ifndef TEST_LA_PERF_TIMING_H
#define TEST_LA_PERF_TIMING_H

#include "includes/settings.hpp"
#include <chrono>
#include <string>
#include <unordered_map>

namespace la_perf
{

typedef std::chrono::duration<double> duration_type;

/// ===============================================
/// T I M I N G   E N T R Y
/// ===============================================

/// @brief A single entry in time report, total duration and number of calls
struct timing_entry
{
    /// @brief Total duration
    duration_type duration;
    /// @brief Total number of calls
    unsigned long int calls;
};

/// ===============================================
/// T I M E R
/// ===============================================

/// @brief Measure time between start and stop
class timer
{
private:
    /// @brief Start time of the timing
    std::chrono::time_point<std::chrono::steady_clock> p_start;
    /// @brief End of time taking, equals nullptr when not stopped
    std::chrono::time_point<std::chrono::steady_clock> *p_end;

public:
    /// @brief Constructor starts timing
    /// @param name Name of the function
    inline timer() : p_end(nullptr) { restart(); }

    /// @brief Default destructor
    ~timer() = default;

    /// @brief Reset the timer and start taking time
    void restart();

    /// @brief Either get the time between start and now or last stop call
    /// @return
    inline duration_type get() const
    {
        return p_end != nullptr ? (*p_end - p_start) : (std::chrono::steady_clock::now() - p_start);
    }

    /// @brief Stop the timer and get the time
    /// @return
    duration_type stop();
};

/// ===============================================
/// T I M E   R E P O R T
/// ===============================================

/// @brief Time reporting as a singleton class
class time_report
{
private:
    /// @brief Implementing singleton pattern
    static time_report *p_instance;

    /// @brief Record of all timings
    std::unordered_map<std::string, timing_entry> p_timings;

    /// @brief Recording overall time
    timer p_timer;

    /// @brief Private constructor for singleton pattern
    inline time_report() : p_timings(), p_timer() {}

public:
    /// @brief Destructor write a report
    ~time_report() { report(); };

    /// @brief Get time reporting as singleton pattern
    /// @return
    static time_report &get();

    /// @brief Record a time
    /// @param what Name of what to record
    /// @param time Duration to add
    void record(const std::string &what, const duration_type &time);

    /// @brief Print out a report
    void report();
};

/// ===============================================
/// S C O P E   T I M E R
/// ===============================================

/// @brief Time a scope, i.e., between construct ad destruct
class scope_timer : public timer
{
private:
    /// @brief Nice name what is being timed
    std::string p_what;

public:
    /// @brief Start time keeping
    inline scope_timer(const std::string &what) : p_what(what) {}

    /// @brief Report time keeping
    ~scope_timer() { time_report::get().record(p_what, timer::get()); }
};

#ifdef TIMEMING
#define TIMEME la_perf::scope_timer __my_function_timer__ = la_perf::scope_timer(__func__)
#else
#define TIMEME(WHAT) ((void)0)
#endif

} // namespace la_perf

#endif
