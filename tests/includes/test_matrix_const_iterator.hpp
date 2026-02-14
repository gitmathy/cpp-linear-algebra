#ifndef TEST_LA_MATRIX_CONST_ITERATOR_H
#define TEST_LA_MATRIX_CONST_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing const_iterator of matrix
class matrix_const_iterator_test : public unit_test
{
public:
    inline matrix_const_iterator_test() : unit_test("matrix const-iterator test") {}
    ~matrix_const_iterator_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
