#ifndef LA_TEST_DECOMPOSE_H
#define LA_TEST_DECOMPOSE_H

#include "la/dense"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Solve x= A^-1 * b
template <storage_type MatStorageT, storage_type DecompositionStorageT>
class decompose_solve_lu : public performance_test
{
private:
    /// @brief Size of the system
    size_type p_size;

protected:
    /// @brief Execute a single test
    void run_single_test() override
    {
        if constexpr (MatStorageT == ROW_WISE) {
            la::algorithm::lu_decomposition<double, DecompositionStorageT> decomposition(p_A_row);
            decomposition.solve(p_b_vec);
        } else {
            la::algorithm::lu_decomposition<double, DecompositionStorageT> decomposition(p_A_col);
            decomposition.solve(p_b_vec);
        }
    }

public:
    /// @brief Set me up
    decompose_solve_lu(const size_type runs, const size_type n)
        : performance_test(std::string("decompose_solve_lu_") +
                               (DecompositionStorageT == ROW_WISE ? "row: " : "col: ") +
                               (MatStorageT == ROW_WISE ? "row" : "col"),
                           "Testing A^1*b", runs),
          p_size(n)
    {}

    /// @brief Setup the test
    void setup() override { p_samples->adjust(p_size, p_size, p_size); }
};

} // namespace test
} // namespace la
#endif
