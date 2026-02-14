#ifndef TEST_LA_MATRIX_MOVE_CTOR_H
#define TEST_LA_MATRIX_MOVE_CTOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test move constructor of matrices
class matrix_move_constructor_test : public unit_test
{
public:
    inline matrix_move_constructor_test() : unit_test("matrix move-constructor test") {}
    ~matrix_move_constructor_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
