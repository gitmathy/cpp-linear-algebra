#include "../includes/la.hpp"
#include "../includes/vector.hpp"
#include "includes/timing.hpp"
#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iostream>

const la::size_type N = 100000000;
const la::size_type RUNS = 10;

template <typename T> inline double get_random() { return T((std::rand() / (T)RAND_MAX) * 2 - 1); }

template <typename T> class performance_add
{
private:
    la::vector<T> a, b;

public:
    performance_add(la::size_type n) : a(n), b(n) { init(); }

    void init()
    {
        TIME_ME;
        a.apply_func([](T) { return get_random<T>(); });
        b.apply_func([](T) { return get_random<T>(); });
    }

    void run_assign_add(la::size_type num_run)
    {
        TIME_ME;
        for (la::size_type i = 0; i < num_run; ++i)
            a += b;
    }

    void run_add(la::size_type num_run)
    {
        std::cout << "add" << std::endl;
        TIME_ME;
        la::vector<T> c(a.size());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b;
    }

    void run_multiple_add(la::size_type num_run)
    {
        std::cout << "multiple_add" << std::endl;
        TIME_ME;
        la::vector<T> c(a.size());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b + 3 + a + b + 2;
    }

    void run_multiple_add_sub(la::size_type num_run)
    {
        std::cout << "multiple_add_sub" << std::endl;
        TIME_ME;
        la::vector<T> c(a.size());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a - b - 2 + a - b + 2;
    }
};

void time_add(const la::size_type n = 10000)
{
    TIME_ME;
    la::vector<double> v(n);
}

int main()
{
    std::srand(std::time({})); // use current time as seed for random generator
    la_perf::time_report &timings = la_perf::time_report::get();

    std::cout << "Running performance tests\n" << std::endl;
    std::cout << "Dimension: " << N << '\n' << "# runs: " << RUNS << '\n' << std::endl;

    performance_add<double> add(N);
    std::cout << "assign_add" << std::endl;
    add.run_assign_add(RUNS);

    add.run_add(RUNS);

    add.run_multiple_add(RUNS);

    add.run_multiple_add_sub(RUNS);

    timings.report();
    return 0;
}
