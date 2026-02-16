#ifndef TEST_LA_VECTOR_EXPRESSION_TEMPORARY_H
#define TEST_LA_VECTOR_EXPRESSION_TEMPORARY_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Test expression-template temporaries and their lifetimes
class vector_expression_temporary_test : public unit_test
{
public:
    inline vector_expression_temporary_test() : unit_test("vector expression-temporary test") {}
    ~vector_expression_temporary_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
