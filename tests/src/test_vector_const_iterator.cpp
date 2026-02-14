#include "includes/test_vector_const_iterator.hpp"
#include "../includes/vector.hpp"
#include <numeric>

namespace la_test
{

bool vector_const_iterator_test::execute()
{
    bool result = true;

    la::vector<int> v(6);
    for (la::size_type i = 0; i < v.size(); ++i)
        v(i) = static_cast<int>(i + 1); // 1..6

    const la::vector<int> cv = v; // use copy / const access

    // iterate with const-iterator and verify values
    la::size_type pos = 0;
    for (la::vector<int>::citerator it = cv.begin(); it != cv.end(); ++it, ++pos)
    {
        if (*it != static_cast<int>(pos + 1))
        {
            result = false;
            p_logger.log("Const-iterator read incorrect value", ERROR);
            break;
        }
    }

    // test algorithm on const-iterators (std::accumulate)
    int sum = std::accumulate(cv.begin(), cv.end(), 0);
    int expect = 0;
    for (int i = 1; i <= static_cast<int>(cv.size()); ++i)
        expect += i;
    if (sum != expect)
    {
        result = false;
        p_logger.log("std::accumulate over const-iterator produced wrong sum", ERROR);
    }

    if (!result)
        p_errors.push_back("vector<> error in const-iterator tests");

    return result;
}

} // namespace la_test
