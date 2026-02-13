#ifndef TEST_LA_TEST_VECTOR_H
#define TEST_LA_TEST_VECTOR_H

#include "includes/unit_test.hpp"

namespace la_test
{

class vector_test : public unit_test
{
public:
    /// @brief Setup the vector test
    vector_test();
    /// @brief Destruct the vector test
    ~vector_test() = default;

    /// @brief Execute the test
    /// @return True if test succeeded
    bool execute() override;
};

} // namespace la_test
#endif
