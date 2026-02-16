#ifndef LA_TEST_RESIZE_TEST_H
#define LA_TEST_RESIZE_TEST_H

#include "includes/matrix.hpp"
#include "includes/vector.hpp"
#include "tests/includes/performance_test.hpp"

namespace la
{
namespace test
{

/// @brief Test resize a vector (free memory, allocate memory, and assign default value)
class vector_resize : public vector_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a.resize(p_b.rows()); }

public:
    /// @brief Set me up
    vector_resize(const size_type runs, const size_type dim) : vector_performance_test("vector_resize", runs, dim) {}
};

/// @brief Test resize a matrix (free memory, allocate memory, and assign default value)
class matrix_resize : public matrix_performance_test
{
protected:
    /// @brief Execute a single test
    inline void run_single_test() override { p_a.resize(p_b.rows(), p_b.cols()); }

public:
    /// @brief Set me up
    matrix_resize(const size_type runs, const size_type m, const size_type n)
        : matrix_performance_test("matrix_resize", runs, m, n)
    {
    }
};

} // namespace test
} // namespace la
#endif
