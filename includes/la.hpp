#ifndef LA_LA_H
#define LA_LA_H

#include "includes/internal/binary.hpp"
#include "includes/internal/literal.hpp"
#include "includes/internal/operant.hpp"
#include "includes/internal/operations.hpp"
#include "includes/matrix.hpp"
#include "includes/settings.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"
#include <algorithm>
#include <cmath>
#include <execution>

namespace la
{

/// ===============================================
/// N O R M S
/// ===============================================

/// @brief p-norm of a vector or matrix.
/// @return ||x||_p
template <unsigned int p = 2, typename la_type> typename la_type::value_type norm(const la_type &x);

/// ===============================================
/// A D D I T I O N
/// ===============================================

/// @brief vector + vector
template <typename T> auto operator+(const vector<T> &left, const vector<T> &right);

/// @brief vector + operant
template <typename T, typename ExpT> auto operator+(const vector<T> &left, const internal::operant<ExpT> &right);

/// @brief operant + vector
template <typename T, typename ExpT> auto operator+(const internal::operant<ExpT> &left, const vector<T> &right);

/// @brief operant + operant
template <typename ExpLT, typename ExpRT>
auto operator+(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right);

/// @brief vector + scalar
template <typename T> auto operator+(const vector<T> &left, const T &right);

/// @brief scalar + vector
template <typename T> auto operator+(const T &left, const vector<T> &right);

/// @brief scalar + operant
template <typename T, typename ExpT> auto operator+(const T &left, const internal::operant<ExpT> &right);

/// @brief operant + scalar
template <typename T, typename ExpT> auto operator+(const internal::operant<ExpT> &left, const T &right);

/// @brief matrix + matrix
template <typename T, storage_type storage_left, storage_type storage_right>
auto operator+(const matrix<T, storage_left> &left, const matrix<T, storage_right> &right);

/// @brief matrix + operant
template <typename T, storage_type storage_left, typename ExpT>
auto operator+(const matrix<T, storage_left> &left, const internal::operant<ExpT> &right);

/// @brief operant + matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const matrix<T, storage_right> &right);

/// @brief matrix + scalar
template <typename T, storage_type storage_left, typename ExpT>
auto operator+(const matrix<T, storage_left> &left, const T &right);

/// @brief scalar + matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator+(const T &left, const matrix<T, storage_right> &right);

/// ===============================================
/// S U B T R A C T I O N
/// ===============================================

/// @brief vector - vector
template <typename T> auto operator-(const vector<T> &left, const vector<T> &right);

/// @brief vector - operant
template <typename T, typename ExpT> auto operator-(const vector<T> &left, const internal::operant<ExpT> &right);

/// @brief operant - vector
template <typename T, typename ExpT> auto operator-(const internal::operant<ExpT> &left, const vector<T> &right);

/// @brief operant - operant
template <typename ExpLT, typename ExpRT>
auto operator-(const internal::operant<ExpLT> &left, const internal::operant<ExpRT> &right);

/// @brief vector - scalar
template <typename T> auto operator-(const vector<T> &left, const T &right);

/// @brief scalar - vector
template <typename T> auto operator-(const T &left, const vector<T> &right);

/// @brief scalar - operant
template <typename T, typename ExpT> auto operator-(const T &left, const internal::operant<ExpT> &right);

/// @brief operant - scalar
template <typename T, typename ExpT> auto operator-(const internal::operant<ExpT> &left, const T &right);

/// @brief matrix - matrix
template <typename T, storage_type storage_left, storage_type storage_right>
auto operator-(const matrix<T, storage_left> &left, const matrix<T, storage_right> &right);

/// @brief matrix - operant
template <typename T, storage_type storage_left, typename ExpT>
auto operator-(const matrix<T, storage_left> &left, const internal::operant<ExpT> &right);

/// @brief operant - matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const matrix<T, storage_right> &right);

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

// NORMS
//------

// Some performance improvements for different common norms such as 1-, 2-, and max-norm.
template <unsigned int p, typename la_type> typename la_type::value_type norm(const la_type &x)
{
    typedef typename la_type::value_type T;
    auto first = x.begin();
    T result = T(0);
    if constexpr (p == 1)
    {
        result =
            std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                  x.begin(), x.end(), 0.0, std::plus<T>(), [](const T val) { return std::abs(val); });
        return result;
    }
    if constexpr (p == 2)
    {
        result = std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                       x.begin(), x.end(), 0.0, std::plus<T>(),
                                       [](const T val) { return std::abs(val * val); });
        return std::sqrt(result);
    }
    if constexpr (p == LA_UINT_MAX)
    {
        for (; first != x.end(); ++first)
            result = std::max(std::abs(*first), result);
        return result;
    }
    result = std::transform_reduce(std::execution::par_unseq, // Parallel and unsequenced execution
                                   x.begin(), x.end(), 0.0, std::plus<T>(),
                                   [](const T val) { return std::pow(std::abs(val), p); });
    return std::pow(result, 1. / p);
}

// ADDITION
//---------

/// @brief vector + vector
template <typename T> auto operator+(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>, internal::add_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + operant
template <typename T, typename ExpT> auto operator+(const vector<T> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<vector<T>, internal::operant<ExpT>,
                                        internal::add_operation<vector<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + vector
template <typename T, typename ExpT> auto operator+(const internal::operant<ExpT> &left, const vector<T> &right)
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
    typedef internal::binary_expression<internal::operant<ExpLT>, internal::operant<ExpRT>,
                                        internal::add_operation<internal::operant<ExpLT>, internal::operant<ExpRT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + scalar
template <typename T> auto operator+(const vector<T> &left, const T &right)
{
    typedef internal::binary_expression<vector<T>, internal::literal<T>,
                                        internal::add_operation<vector<T>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + vector
template <typename T> auto operator+(const T &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::literal<T>, vector<T>,
                                        internal::add_operation<internal::literal<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + operant
template <typename T, typename ExpT> auto operator+(const T &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<internal::literal<T>, internal::operant<ExpT>,
                                        internal::add_operation<internal::literal<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + scalar
template <typename T, typename ExpT> auto operator+(const internal::operant<ExpT> &left, const T &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, internal::literal<T>,
                                        internal::add_operation<internal::operant<ExpT>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + matrix
template <typename T, storage_type storage_left, storage_type storage_right>
auto operator+(const matrix<T, storage_left> &left, const matrix<T, storage_right> &right)
{
    typedef internal::binary_expression<matrix<T, storage_left>, matrix<T, storage_right>,
                                        internal::add_operation<matrix<T, storage_left>, matrix<T, storage_right>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + operant
template <typename T, storage_type storage_left, typename ExpT>
auto operator+(const matrix<T, storage_left> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<matrix<T, storage_left>, internal::operant<ExpT>,
                                        internal::add_operation<matrix<T, storage_left>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator+(const internal::operant<ExpT> &left, const matrix<T, storage_right> &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, matrix<T, storage_right>,
                                        internal::add_operation<internal::operant<ExpT>, matrix<T, storage_right>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + scalar
template <typename T, storage_type storage_left, typename ExpT>
auto operator+(const matrix<T, storage_left> &left, const T &right)
{
    typedef internal::binary_expression<matrix<T, storage_left>, internal::literal<T>,
                                        internal::add_operation<matrix<T, storage_left>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator+(const T &left, const matrix<T, storage_right> &right)
{
    typedef internal::binary_expression<internal::literal<T>, matrix<T, storage_right>,
                                        internal::add_operation<internal::literal<T>, matrix<T, storage_right>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// SUBSTRACTION
//-------------

/// @brief vector - vector
template <typename T> auto operator-(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>, internal::sub_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector - operant
template <typename T, typename ExpT> auto operator-(const vector<T> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<vector<T>, internal::operant<ExpT>,
                                        internal::sub_operation<vector<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - vector
template <typename T, typename ExpT> auto operator-(const internal::operant<ExpT> &left, const vector<T> &right)
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
    typedef internal::binary_expression<internal::operant<ExpLT>, internal::operant<ExpRT>,
                                        internal::sub_operation<internal::operant<ExpLT>, internal::operant<ExpRT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector - scalar
template <typename T> auto operator-(const vector<T> &left, const T &right)
{
    typedef internal::binary_expression<vector<T>, internal::literal<T>,
                                        internal::sub_operation<vector<T>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar - vector
template <typename T> auto operator-(const T &left, const vector<T> &right)
{
    typedef internal::binary_expression<internal::literal<T>, vector<T>,
                                        internal::sub_operation<internal::literal<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar - operant
template <typename T, typename ExpT> auto operator-(const T &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<internal::literal<T>, internal::operant<ExpT>,
                                        internal::sub_operation<internal::literal<T>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - scalar
template <typename T, typename ExpT> auto operator-(const internal::operant<ExpT> &left, const T &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, internal::literal<T>,
                                        internal::sub_operation<internal::operant<ExpT>, internal::literal<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix - matrix
template <typename T, storage_type storage_left, storage_type storage_right>
auto operator-(const matrix<T, storage_left> &left, const matrix<T, storage_right> &right)
{
    typedef internal::binary_expression<matrix<T, storage_left>, matrix<T, storage_right>,
                                        internal::sub_operation<matrix<T, storage_left>, matrix<T, storage_right>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix - operant
template <typename T, storage_type storage_left, typename ExpT>
auto operator-(const matrix<T, storage_left> &left, const internal::operant<ExpT> &right)
{
    typedef internal::binary_expression<matrix<T, storage_left>, internal::operant<ExpT>,
                                        internal::sub_operation<matrix<T, storage_left>, internal::operant<ExpT>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant - matrix
template <typename T, storage_type storage_right, typename ExpT>
auto operator-(const internal::operant<ExpT> &left, const matrix<T, storage_right> &right)
{
    typedef internal::binary_expression<internal::operant<ExpT>, matrix<T, storage_right>,
                                        internal::sub_operation<internal::operant<ExpT>, matrix<T, storage_right>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

} // namespace la
#endif
