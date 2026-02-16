#ifndef TEST_LA_MATRIX_ITERATOR_H
#define TEST_LA_MATRIX_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing iterator of matrix
class matrix_iterator_test : public unit_test
{
public:
    inline matrix_iterator_test() : unit_test("matrix iterator test") {}
    ~matrix_iterator_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
