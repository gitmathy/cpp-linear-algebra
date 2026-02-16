#ifndef TEST_LA_MATRIX_ROW_ITERATOR_H
#define TEST_LA_MATRIX_ROW_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing row-iterator of matrix (row-wise storage)
class matrix_row_iterator_test : public unit_test
{
public:
    inline matrix_row_iterator_test() : unit_test("matrix row-iterator test") {}
    ~matrix_row_iterator_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
