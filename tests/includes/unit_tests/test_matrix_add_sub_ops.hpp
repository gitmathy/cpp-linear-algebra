#ifndef TEST_LA_MATRIX_ADD_SUB_OPS_H
#define TEST_LA_MATRIX_ADD_SUB_OPS_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing addition and subtraction operators for matrices
class matrix_add_sub_ops_test : public unit_test
{
public:
    inline matrix_add_sub_ops_test() : unit_test("matrix add/sub ops test") {}
    ~matrix_add_sub_ops_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
