#include "../includes/la.hpp"
#include "../includes/vector.hpp"
#include "includes/timing.hpp"
#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iostream>

const la::size_type VECTOR_N = 100000000;
const la::size_type MATRIX_M = 1000;
const la::size_type MATRIX_N = 100000;
const la::size_type RUNS = 10;

template <typename T> inline double get_random() { return T((std::rand() / (T)RAND_MAX) * 2 - 1); }

template <typename T> class performance_add_vec
{
private:
    /// @brief vectors used for testing
    la::vector<T> a, b;

public:
    performance_add_vec(la::size_type n) : a(n), b(n) { init(); }

    void init()
    {
        TIME_ME;
        a.apply_func([](T) { return get_random<T>(); });
        b.apply_func([](T) { return get_random<T>(); });
    }

    void vec_run_assign_add(la::size_type num_run)
    {
        TIME_ME;
        for (la::size_type i = 0; i < num_run; ++i)
            a += b;
    }

    void vec_run_add(la::size_type num_run)
    {
        std::cout << "add" << std::endl;
        TIME_ME;
        la::vector<T> c(a.rows());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b;
    }

    void vec_run_multiple_add(la::size_type num_run)
    {
        std::cout << "multiple_add" << std::endl;
        TIME_ME;
        la::vector<T> c(a.rows());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b + a + b;
    }

    void vec_run_multiple_add_sub(la::size_type num_run)
    {
        std::cout << "multiple_add_sub" << std::endl;
        TIME_ME;
        la::vector<T> c(a.rows());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a - b - 2 + a - b + 2;
    }
};

template <typename T> class performance_add_mat
{
private:
    /// @brief vectors used for testing
    la::matrix<T> a, b;

public:
    performance_add_mat(la::size_type m, la::size_type n) : a(m, n), b(m, n) { init(); }

    void init()
    {
        TIME_ME;
        a.apply_func([](T) { return get_random<T>(); });
        b.apply_func([](T) { return get_random<T>(); });
    }

    void mat_run_assign_add(la::size_type num_run)
    {
        TIME_ME;
        for (la::size_type i = 0; i < num_run; ++i)
            a += b;
    }

    void mat_run_add(la::size_type num_run)
    {
        std::cout << "add" << std::endl;
        TIME_ME;
        la::matrix<T> c(a.rows(), a.cols());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b;
    }

    void mat_run_multiple_add(la::size_type num_run)
    {
        std::cout << "multiple_add" << std::endl;
        TIME_ME;
        la::matrix<T> c(a.rows(), a.cols());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a + b + a + b;
    }

    void run_multiple_add_sub(la::size_type num_run)
    {
        std::cout << "multiple_add_sub" << std::endl;
        TIME_ME;
        la::matrix<T> c(a.rows(), a.cols());
        for (la::size_type i = 0; i < num_run; ++i)
            c = a - b - 2 + a - b + 2;
        if (c.rows() != a.rows() || c.cols() != a.cols())
        {
            throw std::runtime_error("Invalid dimension of result");
        }
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

    std::cout << "Running performance tests on vector\n" << std::endl;
    std::cout << "Dimension: " << VECTOR_N << '\n' << "# runs: " << RUNS << '\n' << std::endl;

    performance_add_vec<double> add(VECTOR_N);
    std::cout << "assign_add" << std::endl;
    add.vec_run_assign_add(RUNS);

    add.vec_run_add(RUNS);

    add.vec_run_multiple_add(RUNS);

    add.vec_run_multiple_add_sub(RUNS);

    std::cout << "Running performance tests on matrix\n" << std::endl;
    std::cout << "Dimension: " << MATRIX_M << " x " << MATRIX_N << '\n' << "# runs: " << RUNS << '\n' << std::endl;

    performance_add_mat<double> add_matrix(MATRIX_M, MATRIX_N);
    std::cout << "assign_add" << std::endl;
    add_matrix.mat_run_assign_add(RUNS);

    add_matrix.mat_run_add(RUNS);

    add_matrix.mat_run_multiple_add(RUNS);

    add_matrix.run_multiple_add_sub(RUNS);

    timings.report();
    return 0;
}
