#include "tests/includes/timing.hpp"
#include <Eigen/Dense>
#include <iostream>

const long int M = 3000;
const long int N = 3000;
const long int SOL_N = 1000;

/// @brief Get a random value
template <typename T>
inline double get_random()
{
    return T((std::rand() / (T)RAND_MAX) * 2 - 1);
}

template <typename MatType>
void init_mat(MatType &mat)
{
    for (long int i = 0; i < mat.rows(); ++i) {
        for (long int j = 0; j < mat.cols(); ++j) {
            mat(i, j) = get_random<double>();
        }
    }
}

template <typename VecType>
void init_vec(VecType &vec)
{
    for (long int i = 0; i < vec.size(); ++i) {
        vec(i) = get_random<double>();
    }
}

void run_performance_multiply_row()
{
    // Explicitly define Row-Major matrix types
    using RowMatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

    RowMatrixXd c(M, N), a(M, N), b(M, N);

    // Initialize matrices
    init_mat(a);
    init_mat(b);
    c.setZero();

    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        // .noalias() is critical to avoid an intermediate temporary matrix
        c.noalias() = a * b;
    }

    auto duration = timer.get();
    std::cout << "Computing 10 times multiply operation of matrices (row wise) of size ("
              << c.rows() << " x " << c.cols() << ") took: " << duration.count()
              << "s, avg: " << (duration.count() / 10) << std::endl;
}

void run_performance_multiply_col()
{
    Eigen::MatrixXd c(M, N), a(M, N), b(M, N);
    init_mat(c);
    init_mat(a);
    init_mat(c);

    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        c = a * b;
    }
    auto duration = timer.get();
    std::cout << "Computing 10 times multiply operation of matrices (column wise) of size ("
              << c.rows() << " x " << c.cols() << ") took: " << duration.count()
              << "s, avg: " << (duration.count() / 10) << std::endl;
}

void run_performance_solve_col()
{
    Eigen::MatrixXd A(SOL_N, SOL_N);
    Eigen::VectorXd b(SOL_N);
    init_mat(A);
    init_vec(b);
    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        Eigen::VectorXd x = A.partialPivLu().solve(b);
    }
    auto duration = timer.get();
    std::cout << "Solving a linear equation system (size " << SOL_N
              << ") 10 times for column based storage took: " << duration.count()
              << "s, avg: " << (duration.count() / 10) << std::endl;
}

void run_performance_solve_row()
{
    // Explicitly define Row-Major matrix types
    using RowMatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

    RowMatrixXd A(SOL_N, SOL_N);
    Eigen::VectorXd b(SOL_N);
    init_mat(A);
    init_vec(b);
    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        Eigen::VectorXd x = A.partialPivLu().solve(b);
    }
    auto duration = timer.get();
    std::cout << "Solving a linear equation system (size " << SOL_N
              << ") 10 times for column based storage took: " << duration.count()
              << "s, avg: " << (duration.count() / 10) << std::endl;
}

int main()
{
    // run_performance_multiply_row();
    // run_performance_multiply_col();
    run_performance_solve_col();
    run_performance_solve_row();

    // std::cout << m << std::endl;
}
