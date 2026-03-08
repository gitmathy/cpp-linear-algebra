/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/static_vector.hpp
/// @brief Declaration and definition of a static vector class, i.e., vector of fixed size
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_STATIC_VECTOR_HPP
#define LA_STATIC_VECTOR_HPP

#include "la/data_structure/expressions/forward.hpp"
#include "la/data_structure/forward.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>

namespace la {

/// @brief Vector of a given size at compile time
/// @tparam T Type of every element
/// @tparam N Size of the vector
template <typename T, size_type N>
class static_vector
{
public:
    /// @brief Type of every element
    typedef T value_type;

    /// @brief Definition of iterator type
    typedef T *iterator;
    /// @brief Definition of constant iterator type
    typedef const T *citerator;

private:
    /// @brief The values (we don't want to use std::array, here)
    T p_vals[N];

public:
    /// public variable members

    /// @brief Dimension of a matrix
    constexpr static size_type dimension = size_type(1);

    /// @brief A static_vector is dense
    constexpr static bool dense = false;

public:
    /// @brief fill with values.
    explicit static_vector(const T &val = T());

    /// @brief Construct from vector
    explicit static_vector(const vector<T> &vec);

    /// @brief Construct a vector with a list of values
    static_vector(const std::initializer_list<T> &init_list);

    /// @brief Construct a vector with a pointer to list of elements
    static_vector(T const *vals);

    /// @brief Move a vector
    explicit static_vector(static_vector<T, N> &&rhs) noexcept;

    /// @brief Copy constructor
    static_vector(const static_vector<T, N> &rhs);

    /// @brief Construct from expression
    template <typename ExpressionT>
    static_vector(const expressions::operant<ExpressionT> &exp);

    /// @brief Destructing a vector
    ~static_vector() = default;

    /// @brief Get number of rows
    inline size_type rows() const { return N; }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return N; }

    /// @brief Assign another vector
    static_vector<T, N> &operator=(const static_vector<T, N> &rhs);

    /// @brief Assign another vector
    static_vector<T, N> &operator=(const vector<T> &rhs);

    /// @brief Move assign a vector
    static_vector<T, N> &operator=(static_vector<T, N> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT>
    static_vector<T, N> &operator=(const expressions::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    static_vector<T, N> &operator=(const std::initializer_list<T> &init_list);

    /// @brief Add another vector
    static_vector<T, N> &operator+=(const static_vector<T, N> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT>
    static_vector<T, N> &operator+=(const expressions::operant<ExpressionT> &exp);

    /// @brief Multiply with a scalar
    static_vector<T, N> &operator*=(const T &rhs);

    /// @brief Multiply (element wise) another vector
    static_vector<T, N> &operator*=(const static_vector<T, N> &rhs);

    /// @brief Multiply (element wise) from another expression
    template <typename ExpressionT>
    static_vector<T, N> &operator*=(const expressions::operant<ExpressionT> &exp);

    /// @brief Substract another vector
    static_vector<T, N> &operator-=(const static_vector<T, N> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT>
    static_vector<T, N> &operator-=(const expressions::operant<ExpressionT> &exp);

    /// @brief Get i'th element for reading
    inline const T &operator()(const size_type i) const;

    /// @brief Get i'th element for writing
    inline T &operator()(const size_type i);

    /// @brief Evaluate at position i is reading the element
    inline const T &evaluate(const size_type i) const { return (*this)(i); }

    /// @brief Evaluate at position i, j is reading the element i(j is ignored)
    inline const T &evaluate(const size_type i, const size_type) const { return (*this)(i); }

    /// @brief Iterator to begin
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end
    inline iterator end() { return p_vals + N; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + N; }
};

/// @brief Write a vector to an output stream
template <typename T, size_type N>
std::ostream &operator<<(std::ostream &os, const static_vector<T, N> &vec);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T, size_type N>
static_vector<T, N>::static_vector(const T &val)
{
    std::fill(p_vals, p_vals + N, val);
}

template <typename T, size_type N>
static_vector<T, N>::static_vector(const std::initializer_list<T> &init_list)
{
    *this = init_list;
}

template <typename T, size_type N>
static_vector<T, N>::static_vector(T const *vals)
{
    std::copy(vals, vals + N, p_vals);
}

template <typename T, size_type N>
static_vector<T, N>::static_vector(static_vector<T, N> &&rhs) noexcept
{
    *this = rhs;
}

template <typename T, size_type N>
static_vector<T, N>::static_vector(const static_vector<T, N> &rhs)
{
    *this = rhs;
}

template <typename T, size_type N>
template <typename ExpressionT>
static_vector<T, N>::static_vector(const expressions::operant<ExpressionT> &exp)
{
    *this = exp;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator=(const static_vector<T, N> &rhs)
{
    std::copy(rhs.p_vals, rhs.p_vals + N, p_vals);
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator=(static_vector<T, N> &&rhs) noexcept
{
    std::copy(rhs.p_vals, rhs.p_vals + N, p_vals);
    return *this;
}

template <typename T, size_type N>
template <typename ExpressionT>
static_vector<T, N> &static_vector<T, N>::operator=(const expressions::operant<ExpressionT> &exp)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] = exp.evaluate(i);
    }
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator=(const std::initializer_list<T> &init_list)
{
    T *val = p_vals;
    auto it = init_list.begin();
    for (size_type i = 0; i < N; ++i) {
        *val++ = *it++;
    }
    SHAPE_ASSERT(it == init_list.end(), "Init static vector from init list");
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator+=(const static_vector<T, N> &rhs)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] += rhs.p_vals[i];
    }
    return *this;
}

template <typename T, size_type N>
template <typename ExpressionT>
static_vector<T, N> &static_vector<T, N>::operator+=(const expressions::operant<ExpressionT> &exp)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] += exp.evaluate(i);
    }
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator*=(const T &rhs)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] *= rhs;
    }
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator*=(const static_vector<T, N> &rhs)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] *= rhs.p_vals[i];
    }
    return *this;
}

template <typename T, size_type N>
template <typename ExpressionT>
static_vector<T, N> &static_vector<T, N>::operator*=(const expressions::operant<ExpressionT> &exp)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] *= exp.evaluate(i);
    }
    return *this;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator-=(const static_vector<T, N> &rhs)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] -= rhs.p_vals[i];
    }
    return *this;
}

template <typename T, size_type N>
template <typename ExpressionT>
static_vector<T, N> &static_vector<T, N>::operator-=(const expressions::operant<ExpressionT> &exp)
{
    for (size_type i = 0; i < N; ++i) {
        p_vals[i] -= exp.evaluate(i);
    }
    return *this;
}

template <typename T, size_type N>
const T &static_vector<T, N>::operator()(const size_type i) const
{
    BOUNDARY_ASSERT(i < N, "static_vector: index out of bound");
    return p_vals[i];
}

template <typename T, size_type N>
T &static_vector<T, N>::operator()(const size_type i)
{
    BOUNDARY_ASSERT(i < N, "static_vector: index out of bound");
    return p_vals[i];
}

template <typename T, size_type N>
std::ostream &operator<<(std::ostream &os, const static_vector<T, N> &vec)
{
    os << '[';
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << ']';
    return os;
}

} // namespace la
#endif
