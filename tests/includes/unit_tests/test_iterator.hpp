#ifndef LA_TEST_UNIT_TEST_ITERATOR_H
#define LA_TEST_UNIT_TEST_ITERATOR_H

#include "tests/includes/unit_test.hpp"
#include <list>
#include <string>

namespace la {
namespace test {

/// @brief Test iterating of vectors
class vector_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    vector_iterator_test() : unit_test("vector_iterator", "Testing iterators") {}

    /// @brief Run the test
    int execute();
};

/// @brief Test iterating of matrices
class matrix_iterator_test : public unit_test
{
public:
    /// @brief Constructing the test
    matrix_iterator_test() : unit_test("matrix_iterator", "Testing iterators") {}

    /// @brief Run the test
    int execute();
};

} // namespace test
} // namespace la
#endif
