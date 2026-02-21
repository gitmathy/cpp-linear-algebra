/// Part of the project "cpp-linear-algebra"
///
/// @file includes/la.hpp
/// @brief Declaration and definition of linear algebra operations
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_LA_H
#define LA_LA_H

#include "includes/internal/binary.hpp"
#include "includes/internal/literal.hpp"
#include "includes/internal/operant.hpp"
#include "includes/internal/operations.hpp"
#include "includes/internal/unary.hpp"
#include "includes/matrix.hpp"
#include "includes/settings.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"
#include <algorithm>
#include <cmath>
#ifndef PARALLEL
#include <numeric>
#endif

namespace la {

/// ===============================================
/// N O R M S
/// ===============================================

/// @brief p-norm of a vector or matrix.
/// @return ||x||_p
template <unsigned int p = 2, typename la_type>
typename la_type::value_type norm(const la_type &x);

/// ===============================================
/// M I N U S
/// ===============================================

/// @brief -vector
template <typename T>
auto operator-(const vector<T> &right);

/// @brief -matrix
template <typename T>
auto operator-(const matrix<T> &right);

/// @brief -operant
template <typename ExpT>
auto operator-(const internal::operant<ExpT> &right);

/// ===============================================
/// A D D I T I O N
/// ===============================================

/// @brief vector + vector
template <typename T>
auto operator+(const vector<T> &left, const vector<T> &right);

/// @brief vector + operant
template <typename T, typename ExpT>
auto operator+(const vector<T> &left, const internal::operant<ExpT> &right);

/// @brief operant + vector
template <typename T, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const vector<T> &right);

/// @brief operant + operant
template <typename ExpLT, typename ExpRT>
auto operator+(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right);

/// @brief vector + scalar
template <typename T>
auto operator+(const vector<T> &left, const T &right);

/// @brief scalar + vector
template <typename T>
auto operator+(const T &left, const vector<T> &right);

/// @brief scalar + operant
template <typename T, typename ExpT>
auto operator+(const T &left, const internal::operant<ExpT> &right);

/// @brief operant + scalar
template <typename T, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const T &right);

/// @brief matrix + matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator+(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right);

/// @brief matrix + operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator+(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right);

/// @brief operant + matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right);

/// @brief matrix + scalar
template <typename T, storage_type StorageLeft>
auto operator+(const matrix<T, StorageLeft> &left, const T &right);

/// @brief scalar + matrix
template <typename T, storage_type StorageRight>
auto operator+(const T &left, const matrix<T, StorageRight> &right);

/// ===============================================
/// S U B T R A C T I O N
/// ===============================================

/// @brief vector - vector
template <typename T>
auto operator-(const vector<T> &left, const vector<T> &right);

/// @brief vector - operant
template <typename T, typename ExpT>
auto operator-(const vector<T> &left, const internal::operant<ExpT> &right);

/// @brief operant - vector
template <typename T, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const vector<T> &right);

/// @brief operant - operant
template <typename ExpLT, typename ExpRT>
auto operator-(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right);

/// @brief vector - scalar
template <typename T>
auto operator-(const vector<T> &left, const T &right);

/// @brief scalar - vector
template <typename T>
auto operator-(const T &left, const vector<T> &right);

/// @brief scalar - operant
template <typename T, typename ExpT>
auto operator-(const T &left, const internal::operant<ExpT> &right);

/// @brief operant - scalar
template <typename T, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const T &right);

/// @brief matrix - matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator-(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right);

/// @brief matrix - operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator-(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right);

/// @brief operant - matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right);

/// ===============================================
/// M U L T I P L I C A T I O N
/// ===============================================

/// @brief vector * vector
template <typename T>
auto operator*(const vector<T> &left, const vector<T> &right);

/// @brief vector * scalar
template <typename T>
auto operator*(const vector<T> &left, const T &right);

/// @brief scalar * vector
template <typename T>
auto operator*(const T &left, const vector<T> &right);

/// @brief scalar * operant
template <typename T, typename ExpT>
auto operator*(const T &left, const internal::operant<ExpT> &right);

/// @brief operant * scalar
template <typename T, typename ExpT>
auto operator*(const internal::operant<ExpT> &left, const T &right);

/// @brief operant * vector
template <typename T, typename ExpT>
auto operator*(const internal::operant<ExpT> &left, const vector<T> &right);

/// @brief vector * operant
template <typename T, typename ExpT>
auto operator*(const vector<T> &left, const internal::operant<ExpT> &right);

/// @brief matrix * matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator*(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right);

/// @brief matrix * operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator*(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right);

/// @brief operant * matrix
template <typename ExpT, typename T, storage_type StorageRight>
auto operator*(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right);

/// @brief operant * operant
template <typename ExpLT, typename ExpRT>
auto operator*(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right);

/// @brief matrix * vector
template <typename T, storage_type StorageLeft>
auto operator*(const matrix<T, StorageLeft> &left, const vector<T> &right);

/// @brief matrix * scalar
template <typename T, storage_type StorageLeft>
auto operator*(const matrix<T, StorageLeft> &left, const T &right);

/// @brief scalar * matrix
template <typename T, storage_type StorageRight>
auto operator*(const T &left, const matrix<T, StorageRight> &right);

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

// NORMS
//------

// Some performance improvements for different common norms such as 1-, 2-, and max-norm.
template <unsigned int p, typename la_type>
typename la_type::value_type norm(const la_type &x)
{
    typedef typename la_type::value_type T;
    T result = T(0);
    if constexpr (p == 1) {
#ifdef PARALLEL
        result = std::transform_reduce(execution::par_unseq, // Parallel and unsequenced execution
                                       x.begin(), x.end(), T(0), std::plus<T>(),
                                       [](const T val) { return std::abs(val); });
#else
        result = std::accumulate(x.begin(), x.end(), T(0),
                                 [](const T sum, const T val) { return sum + std::abs(val); });
#endif
        return result;
    }
    if constexpr (p == 2) {
#ifdef PARALLEL
        result =
            std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                  x.begin(), x.end(), T(0), std::plus<T>(),
                                  [](const T val) { return std::abs(val * val); });
#else
        result = std::accumulate(x.begin(), x.end(), T(0), [](const T sum, const T val) {
            return sum + std::abs(val * val);
        });
#endif
        return std::sqrt(result);
    }
    if constexpr (p == LA_UINT_MAX) {
        result = std::abs(*std::max_element(
#if PARALLEL
            std::execution::par_unseq,
#endif
            x.begin(), x.end(), [](T a, T b) { return std::abs(a) < std::abs(b); }));
        return result;
    }
#ifdef PARALLEL
    result = std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                   x.begin(), x.end(), T(0), std::plus<T>(),
                                   [](const T val) { return std::pow(std::abs(val), p); });
#else
    result = std::accumulate(x.begin(), x.end(), T(0), [](const T sum, const T val) {
        return sum + std::pow(std::abs(val), p);
    });
#endif
    return std::pow(result, 1. / p);
}

// MINUS
//---------

/// @brief -vector
template <typename T>
auto operator-(const vector<T> &right)
{
    typedef internal::unary_expression<vector<T>, internal::minus_operation<vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

/// @brief -matrix
template <typename T>
auto operator-(const matrix<T> &right)
{
    typedef internal::unary_expression<matrix<T>, internal::minus_operation<matrix<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

/// @brief -operant
template <typename ExpT>
auto operator-(const internal::operant<ExpT> &right)
{
    typedef internal::unary_expression<internal::operant<ExpT>,
                                       internal::minus_operation<internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(right));
}

// ADDITION
//---------

/// @brief vector + vector
template <typename T>
auto operator+(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>,
                                        internal::add_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + operant
template <typename T, typename ExpT>
auto operator+(const vector<T> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<vector<T>, internal::operant<ExpT>,
                                        internal::add_operation<vector<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + vector
template <typename T, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, vector<T>,
                                        internal::add_operation<internal::operant<ExpT>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + operant
template <typename ExpLT, typename ExpRT>
auto operator+(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpLT>, internal::operant<ExpRT>,
        internal::add_operation<internal::operant<ExpLT>, internal::operant<ExpRT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + scalar
template <typename T>
auto operator+(const vector<T> &left, const T &right)
{
    typedef internal::binary_expression<vector<T>, internal::literal<T>,
                                        internal::add_operation<vector<T>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + vector
template <typename T>
auto operator+(const T &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::literal<T>, vector<T>,
                                        internal::add_operation<internal::literal<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + operant
template <typename T, typename ExpT>
auto operator+(const T &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        internal::literal<T>, internal::operant<ExpT>,
        internal::add_operation<internal::literal<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + scalar
template <typename T, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const T &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, internal::literal<T>,
        internal::add_operation<internal::operant<ExpT>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator+(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, matrix<T, StorageRight>,
        internal::add_operation<matrix<T, StorageLeft>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator+(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, internal::operant<ExpT>,
        internal::add_operation<matrix<T, StorageLeft>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, matrix<T, StorageRight>,
        internal::add_operation<internal::operant<ExpT>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + scalar
template <typename T, storage_type StorageLeft>
auto operator+(const matrix<T, StorageLeft> &left, const T &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, internal::literal<T>,
        internal::add_operation<matrix<T, StorageLeft>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + matrix
template <typename T, storage_type StorageRight>
auto operator+(const T &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        internal::literal<T>, matrix<T, StorageRight>,
        internal::add_operation<internal::literal<T>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// SUBSTRACTION
//-------------

/// @brief vector - vector
template <typename T>
auto operator-(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>,
                                        internal::sub_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector - operant
template <typename T, typename ExpT>
auto operator-(const vector<T> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<vector<T>, internal::operant<ExpT>,
                                        internal::sub_operation<vector<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - vector
template <typename T, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, vector<T>,
                                        internal::sub_operation<internal::operant<ExpT>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - operant
template <typename ExpLT, typename ExpRT>
auto operator-(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpLT>, internal::operant<ExpRT>,
        internal::sub_operation<internal::operant<ExpLT>, internal::operant<ExpRT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector - scalar
template <typename T>
auto operator-(const vector<T> &left, const T &right)
{
    typedef internal::binary_expression<vector<T>, internal::literal<T>,
                                        internal::sub_operation<vector<T>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar - vector
template <typename T>
auto operator-(const T &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::literal<T>, vector<T>,
                                        internal::sub_operation<internal::literal<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar - operant
template <typename T, typename ExpT>
auto operator-(const T &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        internal::literal<T>, internal::operant<ExpT>,
        internal::sub_operation<internal::literal<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - scalar
template <typename T, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const T &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, internal::literal<T>,
        internal::sub_operation<internal::operant<ExpT>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix - matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator-(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, matrix<T, StorageRight>,
        internal::sub_operation<matrix<T, StorageLeft>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix - operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator-(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, internal::operant<ExpT>,
        internal::sub_operation<matrix<T, StorageLeft>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, matrix<T, StorageRight>,
        internal::sub_operation<internal::operant<ExpT>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// MULTIPLICATION
//---------------

/// @brief vector * vector
template <typename T>
auto operator*(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>,
                                        internal::mult_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector * scalar
template <typename T>
auto operator*(const vector<T> &left, const T &right)
{
    typedef internal::binary_expression<vector<T>, internal::literal<T>,
                                        internal::mult_operation<vector<T>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * vector
template <typename T>
auto operator*(const T &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::literal<T>, vector<T>,
                                        internal::mult_operation<internal::literal<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * operant
template <typename T, typename ExpT>
auto operator*(const T &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        internal::literal<T>, internal::operant<ExpT>,
        internal::mult_operation<internal::literal<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * scalar
template <typename T, typename ExpT>
auto operator*(const internal::operant<ExpT> &left, const T &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, internal::literal<T>,
        internal::mult_operation<internal::operant<ExpT>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * vector
template <typename T, typename ExpT>
auto operator*(const internal::operant<ExpT> &left, const vector<T> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, vector<T>,
        internal::mult_operation<internal::operant<ExpT>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector * operant
template <typename T, typename ExpT>
auto operator*(const vector<T> &left, const internal::operant<ExpT> &right)
{
    {
        typedef internal::binary_expression<
            vector<T>, internal::operant<ExpT>,
            internal::mult_operation<vector<T>, internal::operant<ExpT>>>
            new_bin_exp_type;
        return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
    }
}

/// @brief matrix * matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator*(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, matrix<T, StorageRight>,
        internal::mult_operation<matrix<T, StorageLeft>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix * operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator*(const matrix<T, StorageLeft> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, internal::operant<ExpT>,
        internal::mult_operation<matrix<T, StorageLeft>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * matrix
template <typename ExpT, typename T, storage_type StorageRight>
auto operator*(const internal::operant<ExpT> &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpT>, matrix<T, StorageRight>,
        internal::mult_operation<internal::operant<ExpT>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * operant
template <typename ExpLT, typename ExpRT>
auto operator*(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right)
{
    typedef internal::binary_expression<
        internal::operant<ExpLT>, internal::operant<ExpRT>,
        internal::mult_operation<internal::operant<ExpLT>, internal::operant<ExpRT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix * vector
template <typename T, storage_type StorageLeft>
auto operator*(const matrix<T, StorageLeft> &left, const vector<T> &right)
{
    typedef internal::binary_expression<matrix<T, StorageLeft>, vector<T>,
                                        internal::mult_operation<matrix<T, StorageLeft>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix * scalar
template <typename T, storage_type StorageLeft>
auto operator*(const matrix<T, StorageLeft> &left, const T &right)
{
    typedef internal::binary_expression<
        matrix<T, StorageLeft>, internal::literal<T>,
        internal::mult_operation<matrix<T, StorageLeft>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * matrix
template <typename T, storage_type StorageRight>
auto operator*(const T &left, const matrix<T, StorageRight> &right)
{
    typedef internal::binary_expression<
        internal::literal<T>, matrix<T, StorageRight>,
        internal::mult_operation<internal::literal<T>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

} // namespace la
#endif
