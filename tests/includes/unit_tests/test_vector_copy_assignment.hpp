#ifndef TEST_LA_VECTOR_COPY_ASSIGNMENT_H
#define TEST_LA_VECTOR_COPY_ASSIGNMENT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test copy assignment of vector
class vector_copy_assignment_test : public unit_test
{
public:
    inline vector_copy_assignment_test() : unit_test("vector copy-assignment test") {}
    ~vector_copy_assignment_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
