#ifndef LA_INTERNAL_BINARY_H
#define LA_INTERNAL_BINARY_H

#include "includes/internal/traits.hpp"
#include "includes/types.hpp"
#include <algorithm>
#include <memory>

namespace la {
namespace internal {

/// @brief Representing a binary expression consisting of two "operants" and an operation, e.g.,
/// (vector, scalar, add)
///     or (matrix, matrix, substract)
/// @tparam ExpTLeft type of left expression
/// @tparam ExpTRight type of right expression
/// @tparam OpsT type of operation
template <typename ExpTLeft, typename ExpTRight, typename OpsT>
class binary_expression
{
public:
    /// @brief Value type
    typedef typename expression_traits<ExpTLeft>::value_type value_type;

    /// @brief Type of left expression
    typedef typename expression_traits<ExpTLeft>::expression_type left_expression_type;

    /// @brief Type of right expression
    typedef typename expression_traits<ExpTRight>::expression_type right_expression_type;

private:
    /// @brief The left expression
    left_expression_type p_left;

    /// @brief The right expression
    right_expression_type p_right;

public:
    /// @brief No default constructor
    binary_expression() = delete;

    /// @brief Construct by values
    binary_expression(const left_expression_type &left, const right_expression_type &right)
        : p_left(left), p_right(right)
    {}

    /// @brief Copying a binary_expression
    binary_expression(const binary_expression &bin) : p_left(bin.p_left), p_right(bin.p_right) {}

    /// @brief Moving a binary_expression
    binary_expression(binary_expression &&bin) noexcept
        : p_left(std::move(bin.p_left)), p_right(std::move(bin.p_right))
    {}

    /// @brief Evaluate binary_expression
    inline value_type evaluate(const size_type i) const
    {
        return OpsT::evaluate(p_left, p_right, i);
    }

    /// @brief Evaluate binary_expression (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const
    {
        return OpsT::evaluate(p_left, p_right, i, j);
    }

    /// @brief Get the rows of the result
    inline size_type rows() const;

    /// @brief Get the columns of the result
    inline size_type cols() const;

    /// @brief Get dimension of result
    inline size_type dimension() const;
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::rows() const
{
    if (p_left.dimension() == 0) {
        return p_right.rows();
    }
    if (p_right.dimension() == 0) {
        return p_left.rows();
    }
    return p_left.rows();
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::cols() const
{
    if (p_left.dimension() == 0) {
        return p_right.cols();
    }
    if (p_right.dimension() == 0) {
        return p_left.cols();
    }
    return p_right.cols();
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::dimension() const
{
    if (p_left.dimension() == 0) {
        return p_right.dimension();
    }
    if (p_right.dimension() == 0) {
        return p_left.dimension();
    }
    // matrix * matrix => 2d
    // matrix * vector => 1d
    // vector * vector => 1d
    return std::min(p_left.dimension(), p_right.dimension());
}

} // namespace internal

} // namespace la

#endif
