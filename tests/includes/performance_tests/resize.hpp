#ifndef LA_TEST_RESIZE_TEST_H
#define LA_TEST_RESIZE_TEST_H

#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la {
namespace test {

/// @brief Test resize a vector (free memory, allocate memory, and assign default value)
class vector_resize : public performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a_vec.resize(p_a_vec.rows() + 1); }

public:
    /// @brief Set me up
    vector_resize(const size_type runs)
        : performance_test("vector_resize", "Testing a.resize()", runs)
    {}
};

/// @brief Test resize a matrix (free memory, allocate memory, and assign default value)
template <storage_type StorageT>
class matrix_resize : public performance_test
{
protected:
    /// @brief Execute a single test
    /// We resize to one larger than the normal size, to enforce resizing and resetting when tearing
    /// down the test
    inline void run_single_test() override
    {
        if constexpr (StorageT == ROW_WISE) {
            p_A_row.resize(p_A_row.rows() + 1, p_A_row.cols() + 1);
        } else {
            p_A_col.resize(p_A_col.rows() + 1, p_A_col.cols() + 1);
        }
    }

public:
    /// @brief Set me up
    matrix_resize(const size_type runs)
        : performance_test(std::string("matrix_resize ") + (StorageT == ROW_WISE ? "row" : "col"),
                           "Testing A.resize()", runs)
    {}
};

} // namespace test
} // namespace la
#endif
