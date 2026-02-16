#ifndef TEST_LA_MATRIX_CONSTRUCT_H
#define TEST_LA_MATRIX_CONSTRUCT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test construction of matrices
class matrix_construct_test : public unit_test
{
public:
    inline matrix_construct_test() : unit_test("matrix construct test") {}
    ~matrix_construct_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
