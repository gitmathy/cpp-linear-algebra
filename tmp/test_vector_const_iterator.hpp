#ifndef TEST_LA_VECTOR_CONST_ITERATOR_H
#define TEST_LA_VECTOR_CONST_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing const_iterator of vector
class vector_const_iterator_test : public unit_test
{
public:
    inline vector_const_iterator_test() : unit_test("vector const-iterator test") {}
    ~vector_const_iterator_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
