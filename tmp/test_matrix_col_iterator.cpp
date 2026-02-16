#include "includes/test_matrix_col_iterator.hpp"
#include "../includes/matrix.hpp"

namespace la_test
{

bool matrix_col_iterator_test::execute()
{
    bool result = true;

    // column-wise storage
    la::matrix<int, la::COLUMN_WISE> m(3, 4);
    // fill with column-major increasing values so each column is contiguous
    for (la::size_type j = 0; j < m.cols(); ++j)
        for (la::size_type i = 0; i < m.rows(); ++i)
            m(i, j) = static_cast<int>(j * m.rows() + i + 1);

    // check each column using col_begin/col_end
    for (la::size_type j = 0; j < m.cols(); ++j)
    {
        la::size_type pos = 0;
        for (la::matrix<int, la::COLUMN_WISE>::iterator it = m.col_begin(j); it != m.col_end(j); ++it, ++pos)
        {
            int expect = static_cast<int>(j * m.rows() + pos + 1);
            if (*it != expect)
            {
                p_logger.log("Col-iterator produced incorrect sequence", ERROR);
                result = false;
                break;
            }
        }
        if (!result)
            break;
    }

    if (!result)
        p_errors.push_back("matrix<> error in col-iterator tests");

    return result;
}

} // namespace la_test
