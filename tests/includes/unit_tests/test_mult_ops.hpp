#ifndef LA_TEST_UNIT_TEST_MULT_OPS_H
#define LA_TEST_UNIT_TEST_MULT_OPS_H

#include "tests/includes/unit_test.hpp"

namespace la
{
namespace test
{

/// @brief Test add and sub of vectors
class mat_vec_mult_test : public unit_test
{
public:
    /// @brief Constructing the test
    mat_vec_mult_test() : unit_test("multiplying matrix with vector") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
