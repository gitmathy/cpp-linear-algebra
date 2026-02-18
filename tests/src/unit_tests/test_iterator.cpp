#include "tests/includes/unit_tests/test_iterator.hpp"
#include "includes/matrix.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"
#include <numeric>

namespace la {
namespace test {

int vector_iterator_test::execute()
{
    la::vector<la::size_type> v(6);
    for (la::size_type i = 0; i < v.rows(); ++i)
        v(i) = i + 1; // 1..6

    const la::vector<la::size_type> cv = v; // use copy / const access
    // iterate with const-iterator and verify values
    la::size_type pos = 0;
    for (la::vector<la::size_type>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Vector const-iterator reads incorrect value");

    // test algorithm on const-iterators (std::accumulate)
    la::size_type sum = std::accumulate(cv.begin(), cv.end(), 0);
    const la::size_type expect = 1 + 2 + 3 + 4 + 5 + 6;
    if (sum != expect)
        report_error("std::accumulate over const-iterator produced wrong sum");

    return (int)errors().size();
}

int matrix_iterator_test::execute()
{
    la::matrix<la::size_type> m(2, 5);
    la::size_type cnt = 0;
    for (la::size_type i = 0; i < m.rows(); ++i)
        for (la::size_type j = 0; j < m.cols(); ++j)
            m(i, j) = ++cnt; // 1..10 row-major

    la::size_type pos = 0;
    for (la::matrix<la::size_type>::citerator it = m.begin(); it != m.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Iterator over row-wise matrix read incorrect value");

    pos = 5;
    for (la::matrix<la::size_type>::citerator it = m.row_begin(1); it != m.row_end(1); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Row iterator read incorrect value");

    la::matrix<la::size_type, COLUMN_WISE> cm(2, 5);
    cnt = 0;
    for (la::size_type j = 0; j < m.cols(); ++j)
        for (la::size_type i = 0; i < m.rows(); ++i)
            cm(i, j) = ++cnt; // 1..10 column-major

    pos = 0;
    for (la::matrix<la::size_type, COLUMN_WISE>::citerator it = cm.begin(); it != cm.end();
         ++it, ++pos)
        if (*it != pos + 1)
            report_error("Iterator over column-wise read incorrect value");

    pos = 2;
    for (la::matrix<la::size_type>::citerator it = cm.col_begin(1); it != cm.col_end(1);
         ++it, ++pos)
        if (*it != pos + 1)
            report_error("Column iterator read incorrect value");

    return (int)errors().size();
}

} // namespace test
} // namespace la
