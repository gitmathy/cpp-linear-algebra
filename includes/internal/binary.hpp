#ifndef LA_INTERNAL_BINARY_H
#define LA_INTERNAL_BINARY_H

#include "includes/internal/traits.hpp"
#include "includes/types.hpp"
#include <memory>

namespace la
{
namespace internal
{

/// @brief Representing a binary expression, e.g., vector, scalar, add
/// @tparam ExpTLeft type of left expression
/// @tparam ExpTRight type of right expression
/// @tparam OpsT type of operation
template <typename ExpTLeft, typename ExpTRight, typename OpsT> class binary_expression
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
    const left_expression_type p_left;

    /// @brief The right expression
    const right_expression_type p_right;

public:
    /// @brief No default constructor
    binary_expression() = delete;

    /// @brief Construct by values
    binary_expression(const left_expression_type &left, const right_expression_type &right)
        : p_left(left), p_right(right)
    {
    }

    /// @brief Copying a binary_expression
    binary_expression(const binary_expression &bin) : p_left(bin.p_left), p_right(bin.p_right) {}

    /// @brief Moving a binary_expression
    binary_expression(binary_expression &&bin) noexcept : p_left(std::move(bin.p_left)), p_right(std::move(bin.p_right))
    {
    }

    /// @brief Evaluate binary_expression
    inline value_type evaluate(const size_type i) const { return OpsT::evaluate(p_left, p_right, i); }

    /// @brief Evaluate binary_expression (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const
    {
        return OpsT::evaluate(p_left, p_right, i, j);
    }

    /// @brief Get the size of the result
    /// @return
    inline size_type size() const { return std::max(p_left.size(), p_right.size()); }
};

} // namespace internal

} // namespace la

#endif
