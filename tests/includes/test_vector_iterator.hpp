#ifndef TEST_LA_VECTOR_ITERATOR_H
#define TEST_LA_VECTOR_ITERATOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

/// @brief Testing iterator of vector
class vector_iterator_test : public unit_test
{
public:
    inline vector_iterator_test() : unit_test("vector iterator test") {}
    ~vector_iterator_test() = default;

    /// @brief Run the test
    bool execute() override;
};

} // namespace la_test

#endif
