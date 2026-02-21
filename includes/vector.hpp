/// Part of the project "cpp-linear-algebra"
///
/// @file includes/vector.hpp
/// @brief Declaration and definition of a vector class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include "includes/assert.hpp"
#include "includes/settings.hpp"
#include "includes/types.hpp"
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <ranges>

namespace la {

namespace internal {
/// @brief Forward declaration to not include internals
/// @tparam ExpressionT
template <typename ExpressionT>
class operant;
} // namespace internal

/// @brief Defining a vector used for numerical computations. All elements are stored in a plain
/// array
/// @tparam T Type of every element
template <typename T>
class vector
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
    /// @brief Construct a vector of zero size
    explicit vector() : p_vals(nullptr), p_size(0) {}

    /// @brief Construct a vector of given size and initialize elements with a default value
    explicit vector(size_type n, const T &val = T(0));

    /// @brief Construct a vector with a list of values
    vector(const std::initializer_list<T> &init_list);

    /// @brief Move a vector
    explicit vector(vector<T> &&rhs) noexcept;

    /// @brief Copy constructor
    vector(const vector<T> &rhs);

    /// @brief Construct from expression
    ///
    /// Every element is set to the evaluated element, i.e., x(i) = exp.evaluate(i). This is used
    /// when writing code like x = y+z;
    template <typename ExpressionT>
    vector(const internal::operant<ExpressionT> &exp);

    /// @brief Destructing a vector
    ~vector() { delete[] p_vals; }

    /// @brief Allocate memory and set size
    /// WARNING: elements are not assigned!
    /// @param n Size of the vector
    void allocate(size_type n);

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
    template <typename ExpressionT>
    vector<T> &operator=(const internal::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    vector<T> &operator=(const std::initializer_list<T> &init_list);

    /// @brief Add another vector
    vector<T> &operator+=(const vector<T> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT>
    vector<T> &operator+=(const internal::operant<ExpressionT> &exp);

    /// @brief Substract another vector
    vector<T> &operator-=(const vector<T> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT>
    vector<T> &operator-=(const internal::operant<ExpressionT> &exp);

    /// @brief Apply a function to every entry, i.e., x(i)=func(x(i))
    /// @tparam function, supports func(T)
    template <typename function>
    vector<T> &apply_func(function func);

    /// @brief Write a vector to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true);

    /// @brief Read vector from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

/// ===============================================
/// P U B L I C   F U N C T I O N S
/// ===============================================

/// @brief Write a vector to an output stream
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &vec);

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T>
void vector<T>::allocate(size_type n)
{
    if (p_vals != nullptr) {
        delete[] p_vals;
    }
    p_vals = new T[n];
    p_size = n;
}

template <typename T>
vector<T>::vector(size_type n, const T &val) : p_vals(nullptr), p_size(0)
{
    resize(n, val);
}

template <typename T>
vector<T>::vector(const std::initializer_list<T> &init_list) : p_vals(nullptr), p_size(0)
{
    *this = init_list;
}

// take ownership and leave rhs in a valid empty state
template <typename T>
vector<T>::vector(vector<T> &&rhs) noexcept : p_vals(rhs.p_vals), p_size(rhs.p_size)
{
    rhs.p_vals = nullptr;
    rhs.p_size = 0;
}

template <typename T>
vector<T>::vector(const vector<T> &rhs) : p_vals(nullptr), p_size(0)
{
    *this = rhs;
}

template <typename T>
template <typename ExpressionT>
vector<T>::vector(const internal::operant<ExpressionT> &exp) : p_vals(nullptr), p_size(0)
{
    *this = exp;
}

template <typename T>
void vector<T>::resize(size_type n, const T &val)
{
    allocate(n);
#ifdef PARALLEL
    std::fill(execution::par_unseq, p_vals, p_vals + n, val);
#else
    std::fill(p_vals, p_vals + n, val);
#endif
}

template <typename T>
inline const T &vector<T>::operator()(const size_type i) const
{
    BOUNDARY_ASSERT(i < p_size, "Index out of bound: vector read element");
    return p_vals[i];
}

template <typename T>
inline T &vector<T>::operator()(const size_type i)
{
    BOUNDARY_ASSERT(i < p_size, "Index out of bound: vector write element");
    return p_vals[i];
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    allocate(rhs.p_size);
#ifdef PARALLEL
    std::copy(execution::par_unseq, rhs.p_vals, rhs.p_vals + rhs.p_size, p_vals);
#else
    std::copy(rhs.p_vals, rhs.p_vals + rhs.p_size, p_vals);
#endif
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
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
    if (p_size != n) {
        allocate(n);
    }
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] = exp.evaluate(i); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] = exp.evaluate(i); });
#endif
    // ALTERNATIVE 1: plain for loop are pretty well here.
    // for (size_type i = 0; i < n; ++i)
    // {
    //     p_vals[i] = exp.evaluate(i);
    // }
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const std::initializer_list<T> &init_list)
{
    allocate(init_list.size());
#ifdef PARALLEL
    std::copy(execution::par_unseq, init_list.begin(), init_list.end(), p_vals);
#else
    std::copy(init_list.begin(), init_list.end(), p_vals);
#endif
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator+=(const vector<T> &rhs)
{
    SHAPE_ASSERT(p_size == rhs.rows(), "Invalid shape for vector += vector");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator+=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(rows() == exp.rows() && cols() == exp.cols(),
                 "Invalid shape for vector += operant");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] += exp.evaluate(i); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] += exp.evaluate(i); });
#endif
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator-=(const vector<T> &rhs)
{
    SHAPE_ASSERT(p_size == rhs.p_size, "Invalid shape for vector -= vector");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] -= rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator-=(const internal::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(rows() == exp.rows() && cols() == exp.cols(),
                 "Invalid shape for vector -= operant");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] -= exp.evaluate(i); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] -= exp.evaluate(i); });
#endif
    return *this;
}

template <typename T>
template <typename function>
vector<T> &vector<T>::apply_func(function func)
{
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &func](size_type i) { this->p_vals[i] = func(this->p_vals[i]); });
#endif
    return *this;
}

template <typename T>
void vector<T>::to_file(const std::string &filename, const bool binary)
{
    std::ios_base::openmode mode = binary ? std::ios::out : std::ios::binary | std::ios::out;
    std::ofstream ofs(filename, mode);
    if (!ofs) {
        throw error("Cannot open file for write.", "file_io");
    }
    if (binary) {
        ofs.write(reinterpret_cast<const char *>(&p_size), sizeof(size_type));
        ofs.write(reinterpret_cast<const char *>(p_vals), p_size * sizeof(T));
    } else {
        ofs << p_size << ' ';
        std::copy(p_vals, p_vals + p_size, std::ostream_iterator<T>(ofs, " "));
    }
}

template <typename T>
void vector<T>::from_file(const std::string &filename, const bool binary)
{
    std::ios_base::openmode mode = binary ? std::ios::in : std::ios::binary | std::ios::in;
    std::ifstream ifs(filename, mode);
    if (!ifs) {
        throw error("Cannot open file for read.", "file_io");
    }
    // Read size information
    size_type size;
    if (binary) {
        ifs.read(reinterpret_cast<char *>(&size), sizeof(size_type));
        if (!ifs) {
            throw error("Cannot read header for read.", "file_io");
        }
    } else {
        if (!(ifs >> size)) {
            throw error("Cannot read header for read.", "file_io");
        }
    }
    allocate(size);
    if (binary) {
        ifs.read(reinterpret_cast<char *>(p_vals), p_size * sizeof(T));
        if (!ifs) {
            throw error("Cannot read data.", "file_io");
        }
    } else {
        T value;
        for (size_type i = 0; i < p_size; ++i) {
            if (ifs >> value) {
                (*this)(i) = value;
            } else {
                throw error("Cannot read data.", "file_io");
            }
        }
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &vec)
{
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

} // namespace la
#endif
