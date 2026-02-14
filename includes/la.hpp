#ifndef LA_LA_H
#define LA_LA_H

#include "includes/internal/binary.hpp"
#include "includes/internal/operant.hpp"
#include "includes/internal/operations.hpp"
#include "includes/types.hpp"
#include "includes/vector.hpp"

namespace la
{

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

/// ===============================================
/// S U B T R A C T I O N
/// ===============================================

template <typename T> vector<T> operator-(const vector<T> &left, const vector<T> &right);

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

// ADDITION
//---------

template <typename T> auto operator+(const vector<T> &left, const vector<T> &right)
{
    typedef internal::binary_expression<vector<T>, vector<T>, internal::add_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return internal::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + operant
template <typename T, typename ExpT> vector<T> operator+(const vector<T> &left, const internal::operant<ExpT> &right)
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

// SUBSTRACTION
//-------------

template <typename T> vector<T> operator-(const vector<T> &left, const vector<T> &right)
{
    vector<T> result(left);
    return result -= right;
}

} // namespace la
#endif
