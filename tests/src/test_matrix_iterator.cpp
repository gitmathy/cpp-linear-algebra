#include "includes/test_matrix_iterator.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_iterator_test::execute()
{
    bool result = true;

    la::matrix<int> m(2, 5);
    la::size_type cnt = 0;
    for (la::size_type i = 0; i < m.rows(); ++i)
        for (la::size_type j = 0; j < m.cols(); ++j)
            m(i, j) = static_cast<int>(++cnt); // 1..10 row-major

    la::size_type pos = 0;
    for (la::matrix<int>::iterator it = m.begin(); it != m.end(); ++it, ++pos)
    {
        if (*it != static_cast<int>(pos + 1))
        {
            p_logger.log("Iterator read incorrect value", ERROR);
            result = false;
            break;
        }
    }

    if (!result)
        p_errors.push_back("matrix<> error in iterator tests");

    return result;
}

} // namespace la_test
