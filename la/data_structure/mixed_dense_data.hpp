/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/mixed_dense_data.hpp
/// @brief Implementations of function using mixed dense data structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_MIXED_DENSE_DATA_HPP
#define LA_DATA_STRUCTURE_MIXED_DENSE_DATA_HPP

#include "la/data_structure/expressions/operations.hpp"
#include "la/data_structure/matrix.hpp"
#include "la/data_structure/static_vector.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"

namespace la {

// Member of vector
// ----------------

template <typename T>
template <size_type N>
vector<T>::vector(const static_vector<T, N> &static_vec) : p_vals(nullptr), p_size(0)
{
    *this = static_vec;
}

template <typename T>
template <size_type N>
vector<T> &vector<T>::operator=(const static_vector<T, N> &rhs)
{
    allocate(rhs.rows());
    std::copy(rhs.begin(), rhs.end(), p_vals);
    return *this;
}

// Member of static_vector
// -----------------------

template <typename T, size_type N>
static_vector<T, N>::static_vector(const vector<T> &vec)
{
    *this = vec;
}

template <typename T, size_type N>
static_vector<T, N> &static_vector<T, N>::operator=(const vector<T> &rhs)
{
    SHAPE_ASSERT(rhs.rows() >= N, "Assigning static_vector from too small vector");
    std::copy(rhs.begin(), rhs.begin() + N, p_vals);
    return *this;
}

// Member of matrix
// ----------------

template <typename T>
template <typename MatTypeLeft, typename MatTypeRight>
matrix<T> &
matrix<T>::operator=(const expressions::matrix_multiply_op<MatTypeLeft, MatTypeRight> &mat_mult)
{
    matrix<T> temp = algorithm::matrix_multiplication<T>::multiply(mat_mult.left, mat_mult.right);
    *this = std::move(temp);
    return *this;
}

} // namespace la

#endif
