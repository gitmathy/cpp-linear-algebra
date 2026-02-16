#ifndef TEST_LA_MATRIX_COL_ITERATOR_H
#define TEST_LA_MATRIX_COL_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing col-iterator of matrix (column-wise storage)
class matrix_col_iterator_test : public unit_test
{
public:
    inline matrix_col_iterator_test() : unit_test("matrix col-iterator test") {}
    ~matrix_col_iterator_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
