#include "la/dense"
#include <iostream>

using namespace la;
using namespace algorithm;

int main()
{
    matrix<double> A({{1, 2, 3}, {4, 5, 6}});
    matrix<double> B = A;
    matrix<double> C = A + B;
    matrix<double> D = A * B;
    matrix<double> E = -A;
    matrix<double> F = A - B;

    std::cout << norm(C) << std::endl;

    lu_decomposition<double> LU(A);
    LU.decompose();
}
