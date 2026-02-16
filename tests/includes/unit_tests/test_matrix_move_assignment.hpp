#ifndef TEST_LA_MATRIX_MOVE_ASSIGNMENT_H
#define TEST_LA_MATRIX_MOVE_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test moving of matrices
class matrix_move_assignment_test : public unit_test
{
public:
    inline matrix_move_assignment_test() : unit_test("matrix move-assignment test") {}
    ~matrix_move_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
