#ifndef TEST_LA_MATRIX_RESIZE_H
#define TEST_LA_MATRIX_RESIZE_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test resizing of matrices
class matrix_resize_test : public unit_test
{
public:
    inline matrix_resize_test() : unit_test("matrix resize test") {}
    ~matrix_resize_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
