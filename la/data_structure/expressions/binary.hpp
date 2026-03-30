/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/binary.hpp
/// @brief Definition and declaration of binary expressions
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURES_EXPRESSIONS_BINARY_HPP
#define LA_DATA_STRUCTURES_EXPRESSIONS_BINARY_HPP

#include "la/data_structure/expressions/iterator.hpp"
#include "la/data_structure/expressions/traits.hpp"
#include "la/util/types.hpp"

namespace la {
namespace expressions {

/// @brief Representing a binary expression consisting of two "operants" and an operation, e.g.,
/// (vector, scalar, add) or (matrix, matrix, substract)
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
    binary_expression(const left_expression_type &left, const right_expression_type &right);

    /// @brief Copying a binary_expression
    binary_expression(const binary_expression &bin) : p_left(bin.p_left), p_right(bin.p_right) {}

    /// @brief Moving a binary_expression
    binary_expression(binary_expression &&bin) noexcept;

    /// @brief Evaluate binary_expression
    inline value_type evaluate(const size_type i) const;

    /// @brief Evaluate binary_expression (2d access)
    inline value_type evaluate(const size_type i, const size_type j) const;

    /// @brief Get row_idx_begin
    inline size_type row_idx_begin(const size_type i) const;

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type nz_idx) const;

    /// @brief Constant iterator to begin of column indices
    inline auto begin_col_idx(const size_type i) const;

    /// @brief Constant iterator to end of column indices
    inline auto end_col_idx(const size_type i) const;

    /// @brief Get the rows of the result
    inline size_type rows() const;

    /// @brief Get the columns of the result
    inline size_type cols() const;

    /// @brief Number of non-zeros
    inline size_type non_zeros() const;

    /// @brief Get dimension of result
    constexpr static size_type dimension =
        ExpTLeft::dimension == 0 ? ExpTRight::dimension : ExpTLeft::dimension;

    /// @brief If any side is dense, the result is dense, too
    constexpr static bool dense = ExpTLeft::dense || ExpTRight::dense;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
binary_expression<ExpTLeft, ExpTRight, OpsT>::binary_expression(const left_expression_type &left,
                                                                const right_expression_type &right)
    : p_left(left), p_right(right)
{}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
binary_expression<ExpTLeft, ExpTRight, OpsT>::binary_expression(binary_expression &&bin) noexcept
    : p_left(std::move(bin.p_left)), p_right(std::move(bin.p_right))
{}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline binary_expression<ExpTLeft, ExpTRight, OpsT>::value_type
binary_expression<ExpTLeft, ExpTRight, OpsT>::evaluate(const size_type i) const
{

    return OpsT::evaluate(p_left, p_right, i);
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline binary_expression<ExpTLeft, ExpTRight, OpsT>::value_type
binary_expression<ExpTLeft, ExpTRight, OpsT>::evaluate(const size_type i, const size_type j) const
{
    return OpsT::evaluate(p_left, p_right, i, j);
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline size_type
binary_expression<ExpTLeft, ExpTRight, OpsT>::row_idx_begin(const size_type i) const
{
    SHAPE_ASSERT(ExpTLeft::dimension == 2 || ExpTRight::dimension == 2,
                 "binary_expression: row_idx_begin one side needs to be a matrix");
    return ExpTLeft::dimension == 2 ? p_left.row_idx_begin(i) : p_right.row_idx_begin(i);
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::col_idx(const size_type nz_idx) const
{
    SHAPE_ASSERT(ExpTLeft::dimension == 2 || ExpTRight::dimension == 2,
                 "binary_expression: col_idx one side needs to be a matrix");
    return ExpTLeft::dimension == 2 ? p_left.col_idx(nz_idx) : p_right.col_idx(nz_idx);
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline auto binary_expression<ExpTLeft, ExpTRight, OpsT>::begin_col_idx(const size_type i) const
{
    static_assert(std::is_same_v<ExpTLeft, ExpTRight>,
                  "Types ExpTLeft and ExpTRight must be identical!");
    return const_col_idx_iterator<ExpTLeft>(p_left, p_right, i);
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline auto binary_expression<ExpTLeft, ExpTRight, OpsT>::end_col_idx(const size_type i) const
{
    static_assert(std::is_same_v<ExpTLeft, ExpTRight>,
                  "Types ExpTLeft and ExpTRight must be identical!");
    return const_col_idx_iterator<ExpTLeft>(p_left, p_right, i).end();
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::rows() const
{
    if constexpr (ExpTLeft::dimension == 0) {
        return p_right.rows();
    }
    if constexpr (ExpTRight::dimension == 0) {
        return p_left.rows();
    }
    return p_left.rows();
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::cols() const
{
    if constexpr (ExpTLeft::dimension == 0) {
        return p_right.cols();
    }
    if constexpr (ExpTRight::dimension == 0) {
        return p_left.cols();
    }
    return p_right.cols();
}

template <typename ExpTLeft, typename ExpTRight, typename OpsT>
inline size_type binary_expression<ExpTLeft, ExpTRight, OpsT>::non_zeros() const
{
    return ExpTLeft::dimension == 2 ? p_left.non_zeros() : p_right.non_zeros();
}

} // namespace expressions
} // namespace la

#endif
