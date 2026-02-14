#ifndef LA_INTERNAL_LITERAL_H
#define LA_INTERNAL_LITERAL_H

#include "includes/types.hpp"
#include <memory>

namespace la
{
namespace internal
{

/// @brief A Literal stores a literal, i.e., scalar value.
/// @tparam T type of the scalar value, e.g., int, double, float, etc.
template <typename T> class literal
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

    inline size_type size() const { return 1; }
};

} // namespace internal

} // namespace la

#endif
