#include "tests/includes/timing.hpp"
#include <Eigen/Dense>
#include <iostream>

const long int M = 3000;
const long int N = 3000;

/// @brief Get a random value
template <typename T>
inline double get_random()
{
    return T((std::rand() / (T)RAND_MAX) * 2 - 1);
}

template <typename MatType>
void init(MatType &mat)
{
    for (long int i = 0; i < mat.rows(); ++i) {
        for (long int j = 0; j < mat.cols(); ++j) {
            mat(i, j) = get_random<double>();
        }
    }
}

void run_performance_row()
{
    // Explicitly define Row-Major matrix types
    using RowMatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

    RowMatrixXd c(M, N), a(M, N), b(M, N);

    // Initialize matrices
    init(a);
    init(b);
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

void run_performance_col()
{
    Eigen::MatrixXd c(M, N), a(M, N), b(M, N);
    init(c);
    init(a);
    init(c);

    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        c = a * b + a;
    }
    auto duration = timer.get();
    std::cout << "Computing 10 times multiply operation of matrices (column wise) of size ("
              << c.rows() << " x " << c.cols() << ") took: " << duration.count()
              << "s, avg: " << (duration.count() / 10) << std::endl;
}

int main()
{
    run_performance_row();
    run_performance_col();

    // std::cout << m << std::endl;
}
