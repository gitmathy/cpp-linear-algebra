#ifndef LA_TEST_UNIT_TEST_LU_DECOMP_H
#define LA_TEST_UNIT_TEST_LU_DECOMP_H

#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

/// @brief Test add and sub of vectors
class lu_decomposition_test : public unit_test
{
public:
    /// @brief Constructing the test
    lu_decomposition_test() : unit_test("lu decomposition") {}

    /// @brief Run the test
    int execute() override;
};

} // namespace test
} // namespace la
#endif
