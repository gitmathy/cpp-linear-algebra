/// Part of the project "cpp-linear-algebra"
///
/// @file la/operation/addition.hpp
/// @brief Definition adding structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_OPERATIONS_ADDITION_HPP
#define LA_OPERATIONS_ADDITION_HPP

#include "la/data_structure/expressions/binary.hpp"
#include "la/data_structure/expressions/operant.hpp"
#include "la/data_structure/expressions/operations.hpp"
#include "la/data_structure/expressions/traits.hpp"
#include "la/data_structure/forward.hpp"

namespace la {

// vector

/// @brief vector + vector
template <typename T>
auto operator+(const vector<T> &left, const vector<T> &right);

/// @brief vector + operant
template <typename T, typename ExpT>
auto operator+(const vector<T> &left, const expressions::operant<ExpT> &right);

/// @brief operant + vector
template <typename T, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const vector<T> &right);

/// @brief vector + scalar
template <typename T>
auto operator+(const vector<T> &left, const T &right);

/// @brief scalar + vector
template <typename T>
auto operator+(const T &left, const vector<T> &right);

// static_vector

/// @brief static_vector + static_vector
template <typename T, size_type N>
auto operator+(const static_vector<T, N> &left, const static_vector<T, N> &right);

/// @brief static_vector + operant
template <typename T, size_type N, typename ExpT>
auto operator+(const static_vector<T, N> &left, const expressions::operant<ExpT> &right);

/// @brief operant + static_vector
template <typename T, size_type N, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const static_vector<T, N> &right);

/// @brief static_vector + scalar
template <typename T, size_type N>
auto operator+(const static_vector<T, N> &left, const T &right);

/// @brief scalar + static_vector
template <typename T, size_type N>
auto operator+(const T &left, const static_vector<T, N> &right);

// operant

/// @brief operant + operant
template <typename ExpLT, typename ExpRT>
auto operator+(const expressions::operant<ExpLT> &left, const expressions::operant<ExpRT> &right);

/// @brief scalar + operant
template <typename T, typename ExpT>
auto operator+(const T &left, const expressions::operant<ExpT> &right);

/// @brief operant + scalar
template <typename T, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const T &right);

// matrix

/// @brief matrix + matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator+(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right);

/// @brief matrix + operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator+(const matrix<T, StorageLeft> &left, const expressions::operant<ExpT> &right);

/// @brief operant + matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const matrix<T, StorageRight> &right);

/// @brief matrix + scalar
template <typename T, storage_type StorageLeft>
auto operator+(const matrix<T, StorageLeft> &left, const T &right);

/// @brief scalar + matrix
template <typename T, storage_type StorageRight>
auto operator+(const T &left, const matrix<T, StorageRight> &right);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// vector

/// @brief vector + vector
template <typename T>
auto operator+(const vector<T> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<vector<T>, vector<T>,
                                           expressions::add_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + operant
template <typename T, typename ExpT>
auto operator+(const vector<T> &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        vector<T>, expressions::operant<ExpT>,
        expressions::add_operation<vector<T>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + vector
template <typename T, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, vector<T>,
        expressions::add_operation<expressions::operant<ExpT>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector + scalar
template <typename T>
auto operator+(const vector<T> &left, const T &right)
{
    typedef expressions::binary_expression<
        vector<T>, expressions::literal<T>,
        expressions::add_operation<vector<T>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + vector
template <typename T>
auto operator+(const T &left, const vector<T> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, vector<T>,
        expressions::add_operation<expressions::literal<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// static_vector

/// @brief static_vector + static_vector
template <typename T, size_type N>
auto operator+(const static_vector<T, N> &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, static_vector<T, N>,
        expressions::add_operation<static_vector<T, N>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief static_vector + operant
template <typename T, size_type N, typename ExpT>
auto operator+(const static_vector<T, N> &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, expressions::operant<ExpT>,
        expressions::add_operation<static_vector<T, N>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + static_vector
template <typename T, size_type N, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, static_vector<T, N>,
        expressions::add_operation<expressions::operant<ExpT>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief static_vector + scalar
template <typename T, size_type N>
auto operator+(const static_vector<T, N> &left, const T &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, expressions::literal<T>,
        expressions::add_operation<static_vector<T, N>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + static_vector
template <typename T, size_type N>
auto operator+(const T &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, static_vector<T, N>,
        expressions::add_operation<expressions::literal<T>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// operant

/// @brief operant + operant
template <typename ExpLT, typename ExpRT>
auto operator+(const expressions::operant<ExpLT> &left, const expressions::operant<ExpRT> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpLT>, expressions::operant<ExpRT>,
        expressions::add_operation<expressions::operant<ExpLT>, expressions::operant<ExpRT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + operant
template <typename T, typename ExpT>
auto operator+(const T &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, expressions::operant<ExpT>,
        expressions::add_operation<expressions::literal<T>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + scalar
template <typename T, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const T &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, expressions::literal<T>,
        expressions::add_operation<expressions::operant<ExpT>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// matrix

/// @brief matrix + matrix
template <typename T, storage_type StorageLeft, storage_type StorageRight>
auto operator+(const matrix<T, StorageLeft> &left, const matrix<T, StorageRight> &right)
{
    typedef expressions::binary_expression<
        matrix<T, StorageLeft>, matrix<T, StorageRight>,
        expressions::add_operation<matrix<T, StorageLeft>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + operant
template <typename T, storage_type StorageLeft, typename ExpT>
auto operator+(const matrix<T, StorageLeft> &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        matrix<T, StorageLeft>, expressions::operant<ExpT>,
        expressions::add_operation<matrix<T, StorageLeft>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant + matrix
template <typename T, storage_type StorageRight, typename ExpT>
auto operator+(const expressions::operant<ExpT> &left, const matrix<T, StorageRight> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, matrix<T, StorageRight>,
        expressions::add_operation<expressions::operant<ExpT>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix + scalar
template <typename T, storage_type StorageLeft>
auto operator+(const matrix<T, StorageLeft> &left, const T &right)
{
    typedef expressions::binary_expression<
        matrix<T, StorageLeft>, expressions::literal<T>,
        expressions::add_operation<matrix<T, StorageLeft>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar + matrix
template <typename T, storage_type StorageRight>
auto operator+(const T &left, const matrix<T, StorageRight> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, matrix<T, StorageRight>,
        expressions::add_operation<expressions::literal<T>, matrix<T, StorageRight>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

} // namespace la

#endif
