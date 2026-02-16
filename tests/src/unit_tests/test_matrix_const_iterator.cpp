#include "includes/test_matrix_const_iterator.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_const_iterator_test::execute()
{
    bool result = true;

    la::matrix<int> m(3, 4);
    la::size_type cnt = 0;
    for (la::size_type i = 0; i < m.rows(); ++i)
        for (la::size_type j = 0; j < m.cols(); ++j)
            m(i, j) = static_cast<int>(++cnt); // 1..12 row-major

    const la::matrix<int> cm = m; // const copy

    la::size_type pos = 0;
    for (la::matrix<int>::citerator it = cm.begin(); it != cm.end(); ++it, ++pos)
    {
        if (*it != static_cast<int>(pos + 1))
        {
            p_logger.log("Const-iterator read incorrect value", ERROR);
            result = false;
            break;
        }
    }

    if (!result)
        p_errors.push_back("matrix<> error in const-iterator tests");

    return result;
}

} // namespace la_test
