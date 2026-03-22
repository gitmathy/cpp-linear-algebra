/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/vector.hpp
/// @brief Declaration and definition of a vector class
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_VECTOR_HPP
#define LA_DATA_STRUCTURE_VECTOR_HPP

#include "la/data_structure/expressions/forward.hpp"
#include "la/data_structure/forward.hpp"
#include "la/util/file_io.hpp"
#include "la/util/memory.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace la {

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
    /// public variable members

    /// @brief Dimension of a matrix
    constexpr static size_type dimension = size_type(1);

    /// @brief A vector is dense
    constexpr static bool dense = false;

public:
    /// @brief Construct a vector of zero size
    explicit vector() : p_vals(nullptr), p_size(0) {}

    /// @brief Construct a vector of given size and initialize elements with a default value
    explicit vector(size_type n, const T &val = T());

    /// @brief Construct a static_vector
    template <size_type N>
    explicit vector(const static_vector<T, N> &static_vec);

    /// @brief Construct a vector with a list of values
    vector(const std::initializer_list<T> &init_list);

    /// @brief Move a vector
    explicit vector(vector<T> &&rhs) noexcept;

    /// @brief Copy constructor
    vector(const vector<T> &rhs);

    /// @brief Construct from expression
    ///
    /// Every element is set to the evaluated element, i.e., x(i) = exp.evaluate(i). This is
    /// used when writing code like x = y+z;
    template <typename ExpressionT>
    vector(const expressions::operant<ExpressionT> &exp);

    /// @brief Construct from iterators
    template <typename InputT,
              typename = typename std::enable_if<!std::is_integral<InputT>::value>::type>
    vector(InputT first, const InputT last);

    /// @brief Destructing a vector
    ~vector() { util::deallocate_aligned(p_vals); }

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
    constexpr inline size_type cols() const { return 1; }

    /// @brief Number of non-zeros
    inline size_type non_zeros() const { return p_size; }

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

    /// @brief Direct access to the memory. Use with caution
    inline T *vals() { return p_vals; }

    /// @brief Direct access to the memory. Use with caution
    inline T const *vals() const { return p_vals; }

    /// @brief Assign another vector
    vector<T> &operator=(const vector<T> &rhs);

    /// @brief Assign a scalar to all elements of a vector
    vector<T> &operator=(const T &rhs);

    /// @brief Assign another static_vector
    template <size_type N>
    vector<T> &operator=(const static_vector<T, N> &rhs);

    /// @brief Move assign a vector
    vector<T> &operator=(vector<T> &&rhs) noexcept;

    /// @brief Assign from expression
    template <typename ExpressionT>
    vector<T> &operator=(const expressions::operant<ExpressionT> &exp);

    /// @brief Assign from initializer list
    vector<T> &operator=(const std::initializer_list<T> &init_list);

    /// @brief Add another vector
    vector<T> &operator+=(const vector<T> &rhs);

    /// @brief Add from another expression
    template <typename ExpressionT>
    vector<T> &operator+=(const expressions::operant<ExpressionT> &exp);

    /// @brief Multiply with a scalar
    vector<T> &operator*=(const T &rhs);

    /// @brief Multiply (element wise) another vector
    vector<T> &operator*=(const vector<T> &rhs);

    /// @brief Multiply (element wise) from another expression
    template <typename ExpressionT>
    vector<T> &operator*=(const expressions::operant<ExpressionT> &exp);

    /// @brief Substract another vector
    vector<T> &operator-=(const vector<T> &rhs);

    /// @brief subtract from another expression
    template <typename ExpressionT>
    vector<T> &operator-=(const expressions::operant<ExpressionT> &exp);

    /// @brief Apply a function to every entry, i.e., x(i)=func(x(i))
    /// @tparam function, supports func(T)
    template <typename function>
    vector<T> &apply_func(function func);

    /// @brief Write a vector to a file (default in binary mode)
    void to_file(const std::string &filename, const bool binary = true) const;

    /// @brief Read vector from a file (default in binary mode)
    void from_file(const std::string &filename, const bool binary = true);
};

// ===============================================
// P U B L I C   F U N C T I O N S
// ===============================================

/// @brief Write a vector to an output stream
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &vec);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T>
void vector<T>::allocate(size_type n)
{
    LOG_DEBUG("Allocating memory for vector: " << (n * sizeof(T)) << " B");
    util::deallocate_aligned(p_vals); // Includes a check on nullptr
    p_vals = util::allocate_aligned<T>(n);
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
vector<T>::vector(vector<T> &&rhs) noexcept : p_vals(nullptr), p_size(0)
{
    *this = std::move(rhs);
}

template <typename T>
vector<T>::vector(const vector<T> &rhs) : p_vals(nullptr), p_size(0)
{
    *this = rhs;
}

template <typename T>
template <typename ExpressionT>
vector<T>::vector(const expressions::operant<ExpressionT> &exp) : p_vals(nullptr), p_size(0)
{
    *this = exp;
}

template <typename T>
template <typename InputT, typename>
vector<T>::vector(InputT first, const InputT last) : p_vals(nullptr), p_size(0)
{
    allocate(std::distance(first, last));
    std::copy(
#ifdef PARALLEL
        execution::par_unseq
#endif
            first,
        last, p_vals);
}

template <typename T>
void vector<T>::resize(size_type n, const T &val)
{
    LOG_DEBUG("Resizing vector to (" << n << ')');
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
    LOG_TRACE("Read access to vector at position " << i);
    return p_vals[i];
}

template <typename T>
inline T &vector<T>::operator()(const size_type i)
{
    BOUNDARY_ASSERT(i < p_size, "Index out of bound: vector write element");
    LOG_TRACE("Write access to vector at position " << i);
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
    util::deallocate_aligned(p_vals);
    p_vals = nullptr;
    p_size = 0;
    std::swap(p_vals, rhs.p_vals);
    std::swap(p_size, rhs.p_size);
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const T &rhs)
{
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] = rhs; });
#else
    std::for_each(range.begin(), range.end(), [this, &rhs](size_type i) { this->p_vals[i] = rhs; });
#endif

    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator=(const expressions::operant<ExpressionT> &exp)
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
vector<T> &vector<T>::operator+=(const expressions::operant<ExpressionT> &exp)
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
vector<T> &vector<T>::operator*=(const T &rhs)
{
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs; });
#endif
    return *this;
}

template <typename T>
vector<T> &vector<T>::operator*=(const vector<T> &rhs)
{
    SHAPE_ASSERT(p_size == rhs.rows(), "Invalid shape for vector *= vector");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs.p_vals[i]; });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] *= rhs.p_vals[i]; });
#endif
    return *this;
}

template <typename T>
template <typename ExpressionT>
vector<T> &vector<T>::operator*=(const expressions::operant<ExpressionT> &exp)
{
    SHAPE_ASSERT(rows() == exp.rows() && cols() == exp.cols(),
                 "Invalid shape for vector *= operant");
    auto range = std::views::iota(size_type(0), p_size);
#ifdef PARALLEL
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] *= exp.evaluate(i); });
#else
    std::for_each(range.begin(), range.end(),
                  [this, &exp](size_type i) { this->p_vals[i] *= exp.evaluate(i); });
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
vector<T> &vector<T>::operator-=(const expressions::operant<ExpressionT> &exp)
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
void vector<T>::to_file(const std::string &filename, const bool binary) const
{
    util::file_writer writer(filename, binary);
    writer.append(p_size);
    writer.append(p_vals, p_size);
}

template <typename T>
void vector<T>::from_file(const std::string &filename, const bool binary)
{
    util::file_reader reader(filename, binary);
    // Read size information
    size_type rows = size_type(0);
    reader.get(rows);
    // Allocate memory
    allocate(rows);
    reader.get(p_vals, rows);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &vec)
{
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

} // namespace la
#endif
