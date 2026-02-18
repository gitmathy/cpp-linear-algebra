#include "includes/la.hpp"
#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include <iostream>

using namespace la;

int main()
{
    matrix<double> A({{1, 2, 3}, {4, 5, 6}});
    A.to_file("a_dummy.mat", true);
    la::matrix<double, ROW_WISE> A_row_txt;
    A_row_txt.from_file("a_dummy.mat", true);
    std::cout << A_row_txt << std::endl;
}
