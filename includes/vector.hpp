#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include "includes/assert.hpp"
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

    /// @brief Allocate memory and set size
    /// @param n Size of the vector
    void allocate(size_type n);

public:
    /// @brief Construct a vector of zero size
    explicit vector() : p_vals(nullptr), p_size(0) {}

    /// @brief Construct a vector of given size, initialize elements with 0 (parameter m for alignment with matrix, but
    /// is ignored)
    explicit vector(size_type n, size_type m = 0);

    /// @brief Constructing a vector with default values
    /// @param n Size of the vector
    /// @param val Default value
    vector(size_type n, const T &val);

    /// @brief Move a vector
    explicit vector(vector<T> &&rhs) noexcept;

    /// @brief Copy constructor
    vector(const vector<T> &rhs);

    /// @brief Construct from expression
    template <typename ExpressionT> vector(const internal::operant<ExpressionT> &exp);

    /// @brief Destructing a vector
    ~vector() { delete[] p_vals; }

    /// @brief Resize a vector. Set all elements to default value
    /// @param n New size
    /// @param val default value
    void resize(size_type n, const T &val = T(0));

    /// @brief Get the size of the vector
    inline size_type rows() const { return p_size; }

    /// @brief Vectors only have one column
    inline size_type cols() const { return 1; }

    /// @brief A vector is one dimensional
    inline size_type dimension() const { return 1; }

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
    inline iterator end() { return p_vals + p_size; }

    /// @brief Constant iterator to begin
    inline citerator begin() const { return p_vals; }
    /// @brief Constant iterator to end
    inline citerator end() const { return p_vals + p_size; }

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

    /// @brief Apply a function to every entry, i.e., x(i)=func(x(i))
    /// @tparam function, supports func(T)
    template <typename function> vector<T> &apply_func(function func);
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T> void vector<T>::allocate(size_type n)
{
    if (p_vals != nullptr)
    {
        delete[] p_vals;
    }
    p_vals = new T[n];
    p_size = n;
}

template <typename T> vector<T>::vector(size_type n, size_type) : p_vals(nullptr), p_size(0)
{
    allocate(n);
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = T(0);
}

template <typename T> vector<T>::vector(size_type n, const T &val) : p_vals(nullptr), p_size(0)
{
    allocate(n);
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = val;
}

// take ownership and leave rhs in a valid empty state
template <typename T> vector<T>::vector(vector<T> &&rhs) noexcept : p_vals(rhs.p_vals), p_size(rhs.p_size)
{
    rhs.p_vals = nullptr;
    rhs.p_size = 0;
}

template <typename T> vector<T>::vector(const vector<T> &rhs) : p_vals(nullptr), p_size(0) { *this = rhs; }

template <typename T>
template <typename ExpressionT>
vector<T>::vector(const internal::operant<ExpressionT> &exp) : p_vals(nullptr), p_size(0)
{
    *this = exp;
}

template <typename T> void vector<T>::resize(size_type n, const T &val)
{
    allocate(n);
    std::fill(p_vals, p_vals + n, val);
}

template <typename T> inline const T &vector<T>::operator()(const size_type i) const
{
    BOUNDARY_ASSERT(i < p_size, "Index out of bound: vector read element");
    return p_vals[i];
}

template <typename T> inline T &vector<T>::operator()(const size_type i)
{
    BOUNDARY_ASSERT(i < p_size, "Index out of bound: vector write element");
    return p_vals[i];
}

template <typename T> vector<T> &vector<T>::operator=(const vector<T> &rhs)
{
    if (this == &rhs)
        return *this;
    allocate(rhs.p_size);
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
    SHAPE_ASSERT(exp.cols() == 1, "Invalid shape for vector = operant (2d)");
    const size_type n = exp.rows();
    if (p_size != n)
        allocate(n);
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = exp.evaluate(i);
    return *this;
}

template <typename T> vector<T> &vector<T>::operator+=(const vector<T> &rhs)
{
    SHAPE_ASSERT(p_size == rhs.rows(), "Invalid shape for vector += vector");
    for (size_type i = 0; i < p_size; ++i)
    {
        p_vals[i] += rhs.p_vals[i];
    }
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator+=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(rows() == exp.rows() && cols() == exp.cols(), "Invalid shape for vector += operant");
    for (size_type i = 0; i < p_size; ++i)
        p_vals[i] += exp.evaluate(i);
    return *this;
}

template <typename T> vector<T> &vector<T>::operator-=(const vector<T> &rhs)
{
    SHAPE_ASSERT(p_size == rhs.p_size, "Invalid shape for vector -= vector");
    for (size_type i = 0; i < p_size; ++i)
    {
        p_vals[i] -= rhs.p_vals[i];
    }
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator-=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(rows() == exp.rows() && cols() == exp.cols(), "Invalid shape for vector -= operant");
    for (size_type i = 0; i < p_size; ++i)
        p_vals[i] -= exp.evaluate(i);
    return *this;
}

template <typename T> template <typename function> vector<T> &vector<T>::apply_func(function func)
{
    for (size_type i = 0; i < p_size; ++i)
        p_vals[i] = func(p_vals[i]);
    return *this;
}

} // namespace la
#endif
