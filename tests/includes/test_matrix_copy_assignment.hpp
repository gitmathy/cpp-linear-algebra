#ifndef TEST_LA_MATRIX_COPY_ASSIGNMENT_H
#define TEST_LA_MATRIX_COPY_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test copy-assignment of matrices
class matrix_copy_assignment_test : public unit_test
{
public:
    inline matrix_copy_assignment_test() : unit_test("matrix copy-assignment test") {}
    ~matrix_copy_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
