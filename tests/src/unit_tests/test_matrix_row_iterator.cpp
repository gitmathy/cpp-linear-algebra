#include "includes/test_matrix_row_iterator.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_row_iterator_test::execute()
{
    bool result = true;

    la::matrix<int> m(3, 4); // row-wise storage (default)
    for (la::size_type i = 0; i < m.rows(); ++i)
        for (la::size_type j = 0; j < m.cols(); ++j)
            m(i, j) = static_cast<int>(i * m.cols() + j + 1);

    // check each row using row_begin/row_end
    for (la::size_type i = 0; i < m.rows(); ++i)
    {
        la::size_type pos = 0;
        for (la::matrix<int>::iterator it = m.row_begin(i); it != m.row_end(i); ++it, ++pos)
        {
            int expect = static_cast<int>(i * m.cols() + pos + 1);
            if (*it != expect)
            {
                p_logger.log("Row-iterator produced incorrect sequence", ERROR);
                result = false;
                break;
            }
        }
        if (!result)
            break;
    }

    if (!result)
        p_errors.push_back("matrix<> error in row-iterator tests");

    return result;
}

} // namespace la_test
