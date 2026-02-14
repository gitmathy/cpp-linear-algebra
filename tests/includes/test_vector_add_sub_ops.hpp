#ifndef TEST_LA_VECTOR_ADD_SUB_OPS_H
#define TEST_LA_VECTOR_ADD_SUB_OPS_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test addition and substraction of vectors
class vector_add_sub_ops_test : public unit_test
{
public:
    inline vector_add_sub_ops_test() : unit_test("vector add/sub ops test") {}
    ~vector_add_sub_ops_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
