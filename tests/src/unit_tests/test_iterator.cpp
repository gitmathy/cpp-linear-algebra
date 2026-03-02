/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/test_iterator.cpp
/// @brief Implementation of test of iterators
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/test_iterator.hpp"
#include "la/dense"
#include "la/static"
#include <numeric>

namespace la {
namespace test {

int vector_iterator_test::execute()
{
    vector<size_type> v(6);
    for (size_type i = 0; i < v.rows(); ++i)
        v(i) = i + 1; // 1..6

    const vector<size_type> cv = v; // use copy / const access
    // iterate with const-iterator and verify values
    size_type pos = 0;
    for (vector<size_type>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Vector const-iterator reads incorrect value");

    // test algorithm on const-iterators (std::accumulate)
    size_type sum = std::accumulate(cv.begin(), cv.end(), size_type(0));
    const size_type expect = 1 + 2 + 3 + 4 + 5 + 6;
    if (sum != expect)
        report_error("std::accumulate over const-iterator produced wrong sum");

    return (int)errors().size();
}

int static_vector_iterator_test::execute()
{
    static_vector<size_type, 6> v;
    for (size_type i = 0; i < v.rows(); ++i)
        v(i) = i + 1; // 1..6

    const static_vector<size_type, 6> cv = v; // use copy / const access
    // iterate with const-iterator and verify values
    size_type pos = 0;
    for (static_vector<size_type, 6>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Vector const-iterator reads incorrect value");

    // test algorithm on const-iterators (std::accumulate)
    size_type sum = std::accumulate(cv.begin(), cv.end(), size_type(0));
    const size_type expect = 1 + 2 + 3 + 4 + 5 + 6;
    if (sum != expect)
        report_error("std::accumulate over const-iterator produced wrong sum");

    return (int)errors().size();
}

int matrix_iterator_test::execute()
{
    matrix<size_type> m(2, 5);
    size_type cnt = 0;
    for (size_type i = 0; i < m.rows(); ++i)
        for (size_type j = 0; j < m.cols(); ++j)
            m(i, j) = ++cnt; // 1..10 row-major

    size_type pos = 0;
    for (matrix<size_type>::citerator it = m.begin(); it != m.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Iterator over row-wise matrix read incorrect value");

    pos = 5;
    for (matrix<size_type>::citerator it = m.row_begin(1); it != m.row_end(1); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Row iterator read incorrect value");

    matrix<size_type, COLUMN_WISE> cm(2, 5);
    cnt = 0;
    for (size_type j = 0; j < m.cols(); ++j)
        for (size_type i = 0; i < m.rows(); ++i)
            cm(i, j) = ++cnt; // 1..10 column-major

    pos = 0;
    for (matrix<size_type, COLUMN_WISE>::citerator it = cm.begin(); it != cm.end(); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Iterator over column-wise read incorrect value");

    pos = 2;
    for (matrix<size_type>::citerator it = cm.col_begin(1); it != cm.col_end(1); ++it, ++pos)
        if (*it != pos + 1)
            report_error("Column iterator read incorrect value");

    return (int)errors().size();
}

} // namespace test
} // namespace la
