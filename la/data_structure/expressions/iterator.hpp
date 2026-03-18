/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/iterator.hpp
/// @brief Declaration and definition of iterators
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_EXPRESSIONS_ITERATOR_HPP
#define LA_DATA_STRUCTURE_EXPRESSIONS_ITERATOR_HPP

#include "la/data_structure/util/concepts.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"

namespace la {
namespace expressions {

/// @brief Iterator to column indices by merging two rows
template <typename ExpressionT, bool is_const = false>
class col_idx_iterator
{
private:
    /// @brief ExpressionT must define end_col_idx
    static_assert(la::util::has_end_col_idx<ExpressionT>,
                  "col_idx_iterator: ExpressionT must define end_col_idx");
    /// @brief ExpressionT must define begin_col_idx
    static_assert(la::util::has_begin_col_idx<ExpressionT>,
                  "col_idx_iterator: ExpressionT must define begin_col_idx");

public:
    /// @brief Type of value
    using value_type = size_type;

    /// @brief Type of a pointer to a value
    using pointer_type = std::conditional_t<is_const, const value_type *, value_type *>;

    /// @brief Type of referencing a value
    using reference_type = std::conditional_t<is_const, const value_type &, value_type &>;

private:
    /// @brief Position at left
    pointer_type p_left, p_left_end;
    /// @brief Position at right
    pointer_type p_right, p_right_end;

    /// @brief Private default constructor only used be end()
    inline col_idx_iterator(const pointer_type left, const pointer_type left_end,
                            const pointer_type right, const pointer_type right_end);

public:
    /// @brief Constructing from given expressions for a given row i
    inline col_idx_iterator(std::conditional_t<is_const, const ExpressionT &, ExpressionT &> left,
                            std::conditional_t<is_const, const ExpressionT &, ExpressionT &> right,
                            const size_type i);

    /// @brief Copying an iterator
    inline col_idx_iterator(const col_idx_iterator<ExpressionT, is_const> &rhs);

    /// @brief Dereference: Returns a reference to the data
    inline reference_type operator*() const;

    // Arrow: Returns the address of the data
    inline pointer_type operator->() const;

    /// @brief End of the iterator
    inline col_idx_iterator<ExpressionT, is_const> end() const;

    /// @brief Prefix ++
    inline col_idx_iterator<ExpressionT, is_const> &operator++();

    /// @brief Postfix ++
    col_idx_iterator<ExpressionT, is_const> operator++(int);

    /// @brief Equal comparision.
    inline bool operator==(const col_idx_iterator<ExpressionT, is_const> &rhs) const;

    /// @brief Unequal comparision.
    inline bool operator!=(const col_idx_iterator<ExpressionT, is_const> &rhs) const;
};

template <typename ExpressionT>
using const_col_idx_iterator = col_idx_iterator<ExpressionT, true>;

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const>::col_idx_iterator(
    const col_idx_iterator<ExpressionT, is_const>::pointer_type left,
    const col_idx_iterator<ExpressionT, is_const>::pointer_type left_end,
    const col_idx_iterator<ExpressionT, is_const>::pointer_type right,
    const col_idx_iterator<ExpressionT, is_const>::pointer_type right_end)
    : p_left(left), p_left_end(left_end), p_right(right), p_right_end(right_end)
{}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const>::col_idx_iterator(
    const col_idx_iterator<ExpressionT, is_const> &rhs)
    : p_left(rhs.p_left), p_left_end(rhs.p_left_end), p_right(rhs.p_right),
      p_right_end(rhs.p_right_end)
{}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const>::col_idx_iterator(
    std::conditional_t<is_const, const ExpressionT &, ExpressionT &> left,
    std::conditional_t<is_const, const ExpressionT &, ExpressionT &> right, const size_type i)
    : p_left(left.begin_col_idx(i)), p_left_end(left.end_col_idx(i)),
      p_right(right.begin_col_idx(i)), p_right_end(right.end_col_idx(i))
{}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const>::reference_type
col_idx_iterator<ExpressionT, is_const>::operator*() const
{
    BOUNDARY_ASSERT(p_left != p_left_end || p_right != p_right_end,
                    "col_idx_iterator: out of bound");
    if (p_left == p_left_end) {
        return *p_right;
    }
    if (p_right == p_right_end) {
        return *p_left;
    }
    return *p_left < *p_right ? *p_left : *p_right;
}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const>::pointer_type
col_idx_iterator<ExpressionT, is_const>::operator->() const
{
    BOUNDARY_ASSERT(p_left != p_left_end || p_right != p_right_end,
                    "col_idx_iterator: out of bound");
    if (p_left == p_left_end) {
        return p_right;
    }
    if (p_right == p_right_end) {
        return p_left;
    }
    return *p_left < *p_right ? p_left : p_right;
}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const> col_idx_iterator<ExpressionT, is_const>::end() const
{
    return col_idx_iterator<ExpressionT, is_const>(p_left_end, nullptr, p_right_end, nullptr);
}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const> &col_idx_iterator<ExpressionT, is_const>::operator++()
{
    BOUNDARY_ASSERT(p_left != p_left_end || p_right != p_right_end,
                    "col_idx_iterator: ++ out of bound");
    if (p_left == p_left_end) {
        ++p_right;
    } else if (p_right == p_right_end) {
        ++p_left;
    } else if (*p_left == *p_right) {
        ++p_left;
        ++p_right;
    } else if (*p_left < *p_right) {
        ++p_left;
    } else {
        ++p_right;
    }
    return *this;
}

template <typename ExpressionT, bool is_const>
col_idx_iterator<ExpressionT, is_const> col_idx_iterator<ExpressionT, is_const>::operator++(int)
{
    col_idx_iterator<ExpressionT, is_const> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename ExpressionT, bool is_const>
inline bool col_idx_iterator<ExpressionT, is_const>::operator==(
    const col_idx_iterator<ExpressionT, is_const> &rhs) const
{
    return p_left == rhs.p_left && p_right == rhs.p_right;
}

template <typename ExpressionT, bool is_const>
inline bool col_idx_iterator<ExpressionT, is_const>::operator!=(
    const col_idx_iterator<ExpressionT, is_const> &rhs) const
{
    return !(*this == rhs);
}

} // namespace expressions
} // namespace la
#endif
