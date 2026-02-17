#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include <iostream>

using namespace la;

int main()
{
    matrix<int> A(2, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    vector<int> x(3);
    x(0) = 1;
    x(1) = 2;
    x(2) = 3;
    vector<int> y = A * x;
    std::cout << y(0) << ", " << y(1) << std::endl;
}
