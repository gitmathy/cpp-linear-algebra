#ifndef TEST_LA_VECTOR_MOVE_CTOR_H
#define TEST_LA_VECTOR_MOVE_CTOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test move constructor of vectors
class vector_move_constructor_test : public unit_test
{
public:
    inline vector_move_constructor_test() : unit_test("vector move-constructor test") {}
    ~vector_move_constructor_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
