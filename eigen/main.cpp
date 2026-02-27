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

void run_performance()
{
    Eigen::MatrixXd c(M, N), a(M, N), b(M, N);
    init(c);
    init(a);
    init(c);

    la::test::timer timer;
    for (int i = 0; i < 10; ++i) {
        c = a * b;
    }
    auto duration = timer.get();
    std::cout << "Computing 10 times multiply operation of matrices of size (" << c.rows() << " x "
              << c.cols() << ") took: " << duration.count() << "s, avg: " << (duration.count() / 10)
              << std::endl;
}

int main()
{
    run_performance();

    // std::cout << m << std::endl;
}
