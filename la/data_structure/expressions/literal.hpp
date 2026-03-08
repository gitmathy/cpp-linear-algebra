/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/expressions/literal.hpp
/// @brief Definition and declaration of literals representing scalars
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURES_EXPRESSIONS_LITERAL_HPP
#define LA_DATA_STRUCTURES_EXPRESSIONS_LITERAL_HPP

#include "la/util/types.hpp"

namespace la {
namespace expressions {

/// @brief A Literal stores a literal, i.e., scalar value.
/// @tparam T type of the scalar value, e.g., int, double, float, etc.
template <typename T>
class literal
{
public:
    /// @brief Type of the value
    typedef T value_type;

private:
    /// @brief the value represented by the literal
    T p_value;

public:
    /// @brief No default constructor
    literal() = delete;

    /// @brief Construct by value
    literal(const T &val) : p_value(val) {}

    /// @brief Copying a literal
    literal(const literal<T> &rhs) : p_value(rhs.p_value) {}

    /// @brief Moving a literal
    literal(literal<T> &&rhs) noexcept : p_value(std::move(rhs.p_value)) {}

    /// @brief Evaluate literal
    inline const T &evaluate(const size_type) const { return p_value; }

    /// @brief Evaluate literal (2d access)
    inline const T &evaluate(const size_type, const size_type) const { return p_value; }

    /// @brief Get row_idx_begin
    inline size_type row_idx_begin(const size_type) const { return 0; }

    /// @brief Get column index of non-zero index
    inline size_type col_idx(const size_type) const { return 0; }

    /// @brief Size of literal
    inline size_type size() const { return 1; }

    /// @brief Number of rows
    inline size_type rows() const { return 1; }

    /// @brief Number of cols
    inline size_type cols() const { return 1; }

    /// @brief A literal is zero dimensional
    const static size_type dimension = size_type(0);

    /// @brief A literal is not dense
    const static bool dense = false;
};

} // namespace expressions
} // namespace la

#endif
