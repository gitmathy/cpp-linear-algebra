/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/lu_decomposition.hpp
/// @brief Definition and declaration decomposition algorithms
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_LU_DECOMPOSITION_HPP
#define LA_ALGORITHM_LU_DECOMPOSITION_HPP

#include "la/data_structure/matrix.hpp"
#include "la/data_structure/vector.hpp"
#include "la/util/constants.hpp"
#include "la/util/error.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <ranges>

namespace la {
namespace algorithm {

template <typename T, storage_type StorageT = ROW_WISE>
class lu_decomposition
{
private:
    /// @brief Decomposed matrix
    matrix<T, StorageT> p_a;

    /// @brief Permutation
    vector<size_type> p_p;

public:
    /// @brief Decompose the matrix A
    /// @tparam MatStorageT Storage type of matrix A
    /// @param A to be decomposed
    template <storage_type MatStorageT>
    explicit lu_decomposition(const matrix<T, MatStorageT> &A);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    void solve(vector<T> &x, const vector<T> &rhs);

    /// @brief Solve the system with rhs
    /// @param rhs right hand side
    /// @return A^-1*rhs
    vector<T> solve(const vector<T> &rhs);

    /// @brief Decompose the matrix p_a and determine permutation
    void decompose();
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T, storage_type StorageT>
template <storage_type MatStorageT>
lu_decomposition<T, StorageT>::lu_decomposition(const matrix<T, MatStorageT> &A) : p_a(A), p_p(0)
{
    decompose();
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::decompose()
{
    const size_type n = p_a.rows();
    if (n != p_a.cols()) {
        throw util::error("No LU decomposition for rectangular matrices", "algorithm:lup");
    }
    // Initialize permutation
    auto my_iota = std::views::iota(size_type(0), p_a.rows());
    p_p.resize(n);
    // TODO: Assign values in constructor of vector
    std::copy(my_iota.begin(), my_iota.end(), p_p.begin());

    T max_val = T(0), val; // used for pivot search
    size_type pivot_row;   // used for pivot search

    for (size_type k = 0; k < n; ++k) {
        // 1. Pivot search
        pivot_row = k;
        max_val = T(0);
        for (size_t j = k; j < n; ++j) {
            val = std::abs(p_a(p_p(j), k));
            if (val > max_val) {
                max_val = val;
                pivot_row = j;
            }
        }

        // Check if the matrix is not irregular
        if (max_val < util::EPS) {
            throw util::error("No LU decomposition for irregular matrices", "algorithm:lup");
        }

        // 2. Swap permutation
        std::swap(p_p(k), p_p(pivot_row));

        // 3. Eliminate
        const size_type row_k = p_p(k);
        const T pivot_inv = T(1) / p_a(row_k, k);
        for (size_type i = k + 1; i < n; ++i) {
            const size_type row_i = p_p(i);
            const double factor = (p_a(row_i, k) *= pivot_inv);
            for (size_type j = k + 1; j < n; ++j) {
                p_a(row_i, j) -= factor * p_a(row_k, j);
            }
        }
    }
}

template <typename T, storage_type StorageT>
void lu_decomposition<T, StorageT>::solve(vector<T> &x, const vector<T> &rhs)
{
    const size_type n = p_a.rows();
    if (n != rhs.rows()) {
        throw util::error("rhs of wrong size", "algorithm:lup");
    }
    if (x.rows() != n) {
        x.allocate(n);
    }

    // 1. Forward pass
    T sum;
    for (size_type i = 0; i < n; ++i) {
        sum = T(0);
        for (size_type j = 0; j < i; ++j) {
            sum += p_a(p_p(i), +j) * x(j);
        }
        x(i) = rhs(p_p(i)) - sum;
    }

    // 2. Backward pass
    for (signed_size_type i = signed_size_type(n - 1); i >= 0; --i) {
        sum = T(0);
        for (size_type j = size_type(i + 1); j < n; ++j) {
            sum += p_a(p_p(i), j) * x(j);
        }
        x(i) = (x(i) - sum) / p_a(p_p(i), i);
    }
}

template <typename T, storage_type StorageT>
vector<T> lu_decomposition<T, StorageT>::solve(const vector<T> &rhs)
{
    vector<T> x(0);
    solve(x, rhs);
    return x;
}

} // namespace algorithm
} // namespace la

#endif
