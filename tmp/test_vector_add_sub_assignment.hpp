#ifndef TEST_LA_VECTOR_ADD_SUB_ASSIGNMENT_H
#define TEST_LA_VECTOR_ADD_SUB_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing substraction and addition by assignment of vectors
class vector_add_sub_assignment_test : public unit_test
{
public:
    inline vector_add_sub_assignment_test() : unit_test("vector add/sub assignment test") {}
    ~vector_add_sub_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
