#ifndef TEST_LA_VECTOR_RESIZE_H
#define TEST_LA_VECTOR_RESIZE_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test resizing of vectors
class vector_resize_test : public unit_test
{
public:
    inline vector_resize_test() : unit_test("vector resize test") {}
    ~vector_resize_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
