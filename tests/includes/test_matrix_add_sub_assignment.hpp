#ifndef TEST_LA_MATRIX_ADD_SUB_ASSIGNMENT_H
#define TEST_LA_MATRIX_ADD_SUB_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing substraction and addition by assignment of matrices
class matrix_add_sub_assignment_test : public unit_test
{
public:
    inline matrix_add_sub_assignment_test() : unit_test("matrix add/sub assignment test") {}
    ~matrix_add_sub_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
