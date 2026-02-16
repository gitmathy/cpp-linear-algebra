#ifndef TEST_LA_MATRIX_COPY_CTOR_H
#define TEST_LA_MATRIX_COPY_CTOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test copy constructor of matrices
class matrix_copy_constructor_test : public unit_test
{
public:
    inline matrix_copy_constructor_test() : unit_test("matrix copy-constructor test") {}
    ~matrix_copy_constructor_test() = default;

    bool execute() override;
};

} // namespace la_test

#endif
