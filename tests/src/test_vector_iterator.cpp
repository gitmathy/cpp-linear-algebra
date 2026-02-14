#include "includes/test_vector_iterator.hpp"
#include "../includes/vector.hpp"
#include <algorithm>

namespace la_test
{

bool vector_iterator_test::execute()
{
    bool result = true;

    // populate using iterator
    la::vector<int> v(5);
    int idx = 0;
    for (la::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        *it = ++idx; // 1..5
    }
    // check values
    for (la::size_type i = 0; i < v.size(); ++i)
    {
        if (v(i) != static_cast<int>(i + 1))
        {
            result = false;
            p_logger.log("Iterator wrote incorrect value", ERROR);
            break;
        }
    }

    // check that iterator is a raw pointer into storage
    if (v.begin() != &v(0))
    {
        result = false;
        p_logger.log("begin() does not point to element 0", ERROR);
    }

    // test algorithm using iterator (std::fill)
    std::fill(v.begin(), v.end(), 7);
    for (la::size_type i = 0; i < v.size(); ++i)
    {
        if (v(i) != 7)
        {
            result = false;
            p_logger.log("std::fill via iterator failed", ERROR);
            break;
        }
    }

    if (!result)
        p_errors.push_back("vector<> error in iterator tests");

    return result;
}

} // namespace la_test
