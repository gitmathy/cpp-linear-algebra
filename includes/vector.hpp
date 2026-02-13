#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include "includes/types.hpp"
#include <algorithm>

namespace la
{

/// @brief Defining a vector used for numerical computations
/// @tparam T Type of every element
template <typename T> class vector
{
private:
    /// @brief The values of the vector
    T *p_vals;
    /// @brief Dimension of the vector
    size_type p_size;

public:
    /// @brief Constructing a vector with default values
    /// @param n Size of the vector
    /// @param val Default value
    vector(size_type n, const T &val = T(0));

    /// @brief Destructing a vector
    ~vector();

    /// @brief Get i'th element for reading
    inline const T &operator()(const size_type i) const { return p_vals[i]; }

    /// @brief Get i'th element for writing
    inline T &operator()(const size_type i) { return p_vals[i]; }

    /// @brief Get the size of the vector
    inline size_type size() const { return p_size; }

    /// @brief Resize a vector. If the vecotr becomes "bigger", fill values with the default value
    /// @param n New size
    /// @param val default value
    void resize(size_type n, const T &val = T(0));
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T> vector<T>::vector(size_type n, const T &val) : p_vals(new T[n]), p_size(n)
{
    for (size_type i = 0; i < n; ++i)
        p_vals[i] = val;
}

template <typename T> vector<T>::~vector() { delete[] p_vals; }

template <typename T> void vector<T>::resize(size_type n, const T &val)
{
    if (n == p_size)
        return;
    T *new_vals = new T[n];
    std::copy(p_vals, p_vals + std::min(p_size, n), new_vals);
    for (size_type i = p_size; i < n; ++i)
    {
        new_vals[i] = val;
    }
    p_size = n;
    std::swap(new_vals, p_vals);
    delete[] new_vals;
}

} // namespace la
#endif
