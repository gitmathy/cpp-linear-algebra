#ifndef TEST_LA_VECTOR_CONSTRUCT_H
#define TEST_LA_VECTOR_CONSTRUCT_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test constrcution of vectors
class vector_construct_test : public unit_test
{
public:
    inline vector_construct_test() : unit_test("vector construct test") {}
    ~vector_construct_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
