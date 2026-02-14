#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include "includes/internal/operant.hpp"
#include "includes/types.hpp"
#include <algorithm>
#include <iostream>

namespace la
{

/// @brief Defining a vector used for numerical computations
/// @tparam T Type of every element
template <typename T> class vector
{
public:
    /// @brief Type of every element
    typedef T value_type;

    /// @brief Definition of iterator type
    typedef T *iterator;
    /// @brief Definition of constant iterator type
    typedef const T *citerator;

private:
    /// @brief The values of the vector
    T *p_vals;
    /// @brief Dimension of the vector
    size_type p_size;

public:
    /// @brief Construct a vector of given size, initialize elements with 0
    explicit vector(size_type n);

    /// @brief Constructing a vector with default values
    /// @param n Size of the vector
    /// @param val Default value
    vector(size_type n, const T &val);

    /// @brief Move a vector
    explicit vector(vector<T> &&rhs) noexcept;

    /// @brief Copy constructor
    vector(const vector<T> &rhs);

    /// @brief Construct from expression
    template <typename ExpressionT> vector(const internal::operant<ExpressionT> &exp) : p_vals(nullptr), p_size(0)
    {
        *this = exp;
    }

    /// @brief Destructing a vector
    ~vector();

    /// @brief Resize a vector. If the vector becomes "bigger", fill values with the default value
    /// @param n New size
    /// @param val default value
    void resize(size_type n, const T &val = T(0));

    /// @brief Get the size of the vector
    inline size_type size() const { return p_size; }

    /// @brief Get i'th element for reading
    inline const T &operator()(const size_type i) const { return p_vals[i]; }

    /// @brief Get i'th element for writing
    inline T &operator()(const size_type i) { return p_vals[i]; }

    /// @brief Evaluate at position i is reading the element
    inline const T &evaluate(const size_type i) const { return p_vals[i]; }

    /// @brief Evaluate at position i, j is reading the element i(j is ignored)
    inline const T &evaluate(const size_type i, const size_type j) const { return p_vals[i]; }

    /// @brief Assign another vector
    vector<T> &operator=(const vector<T> &rhs);

    /// @brief Move assign a vector
    vector<T> &operator=(vector<T> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT> vector<T> &operator=(const internal::operant<ExpressionT> &exp);

    /// @brief Add another vector
    vector<T> &operator+=(const vector<T> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT> vector<T> &operator+=(const internal::operant<ExpressionT> &exp);

    /// @brief Substract another vector
    vector<T> &operator-=(const vector<T> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT> vector<T> &operator-=(const internal::operant<ExpressionT> &exp);

    /// @brief Iterator to begin
    inline iterator begin() { return p_vals; }
    /// @brief Iterator to end
    inline iterator end() { return p_vals + p_size; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + p_size; }

    /// @brief Apply a function to every entry, i.e., x(i)=func(x(i))
    /// @tparam function, supports func(T)
    template <typename function> vector<T> &apply_func(function func);
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T> vector<T>::vector(size_type n) : p_vals(new T[n]), p_size(n)
{
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = T(0);
}

template <typename T> vector<T>::vector(size_type n, const T &val) : p_vals(new T[n]), p_size(n)
{
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = val;
}

// take ownership and leave rhs in a valid empty state
template <typename T> vector<T>::vector(vector<T> &&rhs) noexcept : p_vals(rhs.p_vals), p_size(rhs.p_size)
{
    rhs.p_vals = nullptr;
    rhs.p_size = 0;
}

template <typename T> vector<T>::vector(const vector<T> &rhs) : p_vals(nullptr), p_size(0)
{
    if (rhs.p_size == 0)
        return;
    p_vals = new T[rhs.p_size];
    p_size = rhs.p_size;
    std::copy(rhs.p_vals, rhs.p_vals + rhs.p_size, p_vals);
}

template <typename T> vector<T>::~vector() { delete[] p_vals; }

template <typename T> void vector<T>::resize(size_type n, const T &val)
{
    if (n == p_size)
        return;
    T *new_vals = nullptr;
    if (n > 0)
    {
        new_vals = new T[n];
        std::copy(p_vals, p_vals + std::min(p_size, n), new_vals);
        if (n > p_size)
            std::fill(new_vals + p_size, new_vals + n, val);
    }
    std::swap(new_vals, p_vals);
    delete[] new_vals;
    p_size = n;
}

template <typename T> vector<T> &vector<T>::operator=(const vector<T> &rhs)
{
    if (this == &rhs)
        return *this;
    resize(rhs.size());
    std::copy(rhs.p_vals, rhs.p_vals + rhs.p_size, p_vals);
    return *this;
}

template <typename T> vector<T> &vector<T>::operator=(vector<T> &&rhs) noexcept
{
    if (this == &rhs)
        return *this;
    delete[] p_vals;
    p_vals = nullptr;
    p_size = 0;
    std::swap(p_vals, rhs.p_vals);
    std::swap(p_size, rhs.p_size);
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator=(const internal::operant<ExpressionT> &exp)
{
    const std::size_t n = exp.size();
    if (size() != n)
        resize(n);
    for (std::size_t i = 0; i < n; ++i)
        p_vals[i] = exp.evaluate(i);
    return *this;
}

template <typename T> vector<T> &vector<T>::operator+=(const vector<T> &rhs)
{
    const std::size_t n = rhs.size();
    if (size() != n)
        resize(n);
    for (size_type i = 0; i < n; ++i)
    {
        p_vals[i] += rhs.p_vals[i];
    }
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator+=(const internal::operant<ExpressionT> &exp)
{
    const std::size_t n = exp.size();
    if (size() != n)
        resize(n);
    for (std::size_t i = 0; i < n; ++i)
        p_vals[i] += exp.evaluate(i);
    return *this;
}

template <typename T> vector<T> &vector<T>::operator-=(const vector<T> &rhs)
{
    const std::size_t n = rhs.size();
    if (size() != n)
        resize(n);
    for (size_type i = 0; i < n; ++i)
    {
        p_vals[i] -= rhs.p_vals[i];
    }
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator-=(const internal::operant<ExpressionT> &exp)
{
    const std::size_t n = exp.size();
    if (size() != n)
        resize(n);
    for (std::size_t i = 0; i < n; ++i)
        p_vals[i] -= exp.evaluate(i);
    return *this;
}

template <typename T> template <typename function> vector<T> &vector<T>::apply_func(function func)
{
    for (size_type i = 0; i < size(); ++i)
        p_vals[i] = func(p_vals[i]);
    return *this;
}

} // namespace la
#endif
