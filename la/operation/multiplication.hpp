/// Part of the project "cpp-linear-algebra"
///
/// @file la/operation/multiplication.hpp
/// @brief Definition of multiplications of structures
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_OPERATIONS_MULTIPLICATION_HPP
#define LA_OPERATIONS_MULTIPLICATION_HPP

#include "la/algorithm/multiplication.hpp"
#include "la/data_structure/expressions/binary.hpp"
#include "la/data_structure/expressions/operant.hpp"
#include "la/data_structure/expressions/operations.hpp"
#include "la/data_structure/forward.hpp"
#include "la/data_structure/matrix.hpp"
#include "la/data_structure/sparse_matrix.hpp"
#include "la/data_structure/static_vector.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/types.hpp"

namespace la {

// vector

/// @brief vector * vector
template <typename T>
auto operator*(const vector<T> &left, const vector<T> &right);

/// @brief vector * scalar
template <typename T>
auto operator*(const vector<T> &left, const T &right);

/// @brief scalar * vector
template <typename T>
auto operator*(const T &left, const vector<T> &right);

/// @brief operant * vector
template <typename T, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const vector<T> &right);

/// @brief vector * operant
template <typename T, typename ExpT>
auto operator*(const vector<T> &left, const expressions::operant<ExpT> &right);

// static_vector

/// @brief static_vector * static_vector
template <typename T, size_type N>
auto operator*(const static_vector<T, N> &left, const static_vector<T, N> &right);

/// @brief static_vector * operant
template <typename T, size_type N, typename ExpT>
auto operator*(const static_vector<T, N> &left, const expressions::operant<ExpT> &right);

/// @brief operant * static_vector
template <typename T, size_type N, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const static_vector<T, N> &right);

/// @brief static_vector * scalar
template <typename T, size_type N>
auto operator*(const static_vector<T, N> &left, const T &right);

/// @brief scalar * static_vector
template <typename T, size_type N>
auto operator*(const T &left, const static_vector<T, N> &right);

// operant

/// @brief scalar * operant
template <typename T, typename ExpT>
auto operator*(const T &left, const expressions::operant<ExpT> &right);

/// @brief operant * scalar
template <typename T, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const T &right);

// matrix

/// @brief matrix * matrix
template <typename T>
expressions::matrix_multiply_op<matrix<T>, matrix<T>> operator*(const matrix<T> &left,
                                                                const matrix<T> &right);

/// @brief matrix * operant
template <typename T, typename ExpT>
auto operator*(const matrix<T> &left, const expressions::operant<ExpT> &right);

/// @brief operant * matrix
template <typename ExpT, typename T>
auto operator*(const expressions::operant<ExpT> &left, const matrix<T> &right);

/// @brief operant * operant
template <typename ExpLT, typename ExpRT>
auto operator*(const expressions::operant<ExpLT> &left, const expressions::operant<ExpRT> &right);

/// @brief matrix * vector
template <typename T>
auto operator*(const matrix<T> &left, const vector<T> &right);

/// @brief matrix * scalar
template <typename T>
auto operator*(const matrix<T> &left, const T &right);

/// @brief scalar * matrix
template <typename T>
auto operator*(const T &left, const matrix<T> &right);

// sparse matrix

/// @brief sparse_matrix * vector
template <typename T>
auto operator*(const sparse_matrix<T> &left, const vector<T> &right);

/// @brief sparse_matrix * matrix
template <typename T>
auto operator*(const sparse_matrix<T> &left, const matrix<T> &right);

/// @brief sparse_matrix * scalar
template <typename T>
auto operator*(const sparse_matrix<T> &left, const T &right);

/// @brief scalar * sparse_matrix
template <typename T>
auto operator*(const T &left, const sparse_matrix<T> &right);

/// @brief transposed sparse matrix * vector
template <typename T>
vector<T> transp_mult(const sparse_matrix<T> &left, const vector<T> &right);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// vector

/// @brief vector * vector
template <typename T>
auto operator*(const vector<T> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<vector<T>, vector<T>,
                                           expressions::mult_operation<vector<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector * scalar
template <typename T>
auto operator*(const vector<T> &left, const T &right)
{
    typedef expressions::binary_expression<
        vector<T>, expressions::literal<T>,
        expressions::mult_operation<vector<T>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * vector
template <typename T>
auto operator*(const T &left, const vector<T> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, vector<T>,
        expressions::mult_operation<expressions::literal<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * vector
template <typename T, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, vector<T>,
        expressions::mult_operation<expressions::operant<ExpT>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief vector * operant
template <typename T, typename ExpT>
auto operator*(const vector<T> &left, const expressions::operant<ExpT> &right)
{
    {
        typedef expressions::binary_expression<
            vector<T>, expressions::operant<ExpT>,
            expressions::mult_operation<vector<T>, expressions::operant<ExpT>>>
            new_bin_exp_type;
        return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
    }
}

// static_vector

/// @brief static_vector * static_vector
template <typename T, size_type N>
auto operator*(const static_vector<T, N> &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, static_vector<T, N>,
        expressions::mult_operation<static_vector<T, N>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief static_vector * operant
template <typename T, size_type N, typename ExpT>
auto operator*(const static_vector<T, N> &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, expressions::operant<ExpT>,
        expressions::mult_operation<static_vector<T, N>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * static_vector
template <typename T, size_type N, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, static_vector<T, N>,
        expressions::mult_operation<expressions::operant<ExpT>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief static_vector * scalar
template <typename T, size_type N>
auto operator*(const static_vector<T, N> &left, const T &right)
{
    typedef expressions::binary_expression<
        static_vector<T, N>, expressions::literal<T>,
        expressions::mult_operation<static_vector<T, N>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * static_vector
template <typename T, size_type N>
auto operator*(const T &left, const static_vector<T, N> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, static_vector<T, N>,
        expressions::mult_operation<expressions::literal<T>, static_vector<T, N>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// operant

/// @brief operant * scalar
template <typename T, typename ExpT>
auto operator*(const expressions::operant<ExpT> &left, const T &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, expressions::literal<T>,
        expressions::mult_operation<expressions::operant<ExpT>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * operant
template <typename T, typename ExpT>
auto operator*(const T &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, expressions::operant<ExpT>,
        expressions::mult_operation<expressions::literal<T>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// matrix

/// @brief matrix * matrix
template <typename T>
expressions::matrix_multiply_op<matrix<T>, matrix<T>> operator*(const matrix<T> &left,
                                                                const matrix<T> &right)
{
    return {left, right};
}

/// @brief matrix * operant
template <typename T, typename ExpT>
auto operator*(const matrix<T> &left, const expressions::operant<ExpT> &right)
{
    typedef expressions::binary_expression<
        matrix<T>, expressions::operant<ExpT>,
        expressions::mult_operation<matrix<T>, expressions::operant<ExpT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * matrix
template <typename ExpT, typename T>
auto operator*(const expressions::operant<ExpT> &left, const matrix<T> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpT>, matrix<T>,
        expressions::mult_operation<expressions::operant<ExpT>, matrix<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief operant * operant
template <typename ExpLT, typename ExpRT>
auto operator*(const expressions::operant<ExpLT> &left, const expressions::operant<ExpRT> &right)
{
    typedef expressions::binary_expression<
        expressions::operant<ExpLT>, expressions::operant<ExpRT>,
        expressions::mult_operation<expressions::operant<ExpLT>, expressions::operant<ExpRT>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix * vector
template <typename T>
auto operator*(const matrix<T> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<matrix<T>, vector<T>,
                                           expressions::mult_operation<matrix<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief matrix * scalar
template <typename T>
auto operator*(const matrix<T> &left, const T &right)
{
    typedef expressions::binary_expression<
        matrix<T>, expressions::literal<T>,
        expressions::mult_operation<matrix<T>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * matrix
template <typename T>
auto operator*(const T &left, const matrix<T> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, matrix<T>,
        expressions::mult_operation<expressions::literal<T>, matrix<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

// sparse matrix

/// @brief sparse_matrix * vector
template <typename T>
auto operator*(const sparse_matrix<T> &left, const vector<T> &right)
{
    typedef expressions::binary_expression<sparse_matrix<T>, vector<T>,
                                           expressions::mult_operation<sparse_matrix<T>, vector<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief sparse_matrix * matrix
template <typename T>
auto operator*(const sparse_matrix<T> &left, const matrix<T> &right)
{
    typedef expressions::binary_expression<sparse_matrix<T>, matrix<T>,
                                           expressions::mult_operation<sparse_matrix<T>, matrix<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief sparse_matrix * scalar
template <typename T>
auto operator*(const sparse_matrix<T> &left, const T &right)
{
    typedef expressions::binary_expression<
        sparse_matrix<T>, expressions::literal<T>,
        expressions::mult_operation<sparse_matrix<T>, expressions::literal<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief scalar * sparse_matrix
template <typename T>
auto operator*(const T &left, const sparse_matrix<T> &right)
{
    typedef expressions::binary_expression<
        expressions::literal<T>, sparse_matrix<T>,
        expressions::mult_operation<expressions::literal<T>, sparse_matrix<T>>>
        new_bin_exp_type;
    return expressions::operant<new_bin_exp_type>(new_bin_exp_type(left, right));
}

/// @brief transposed sparse matrix * vector
template <typename T>
vector<T> transp_mult(const sparse_matrix<T> &left, const vector<T> &right)
{
    vector<T> y(left.cols());
    algorithm::transpose_matrix_multiplication<T>::multiply(left, right, y, true);
    return y;
}

} // namespace la
#endif
