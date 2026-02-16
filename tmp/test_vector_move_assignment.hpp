#ifndef TEST_LA_VECTOR_MOVE_ASSIGNMENT_H
#define TEST_LA_VECTOR_MOVE_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test moving of vectors
class vector_move_assignment_test : public unit_test
{
public:
    inline vector_move_assignment_test() : unit_test("vector move-assignment test") {}
    ~vector_move_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
