/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/solver.hpp
/// @brief Definition and declaration of solving linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_SOLVER_HPP
#define LA_ALGORITHM_SOLVER_HPP
namespace la {
namespace algorithm {

// template <typename T, storage_type StorageT>
// void lu_decomposition<T, StorageT>::solve(vector<T> &x, const vector<T> &rhs)
// {
//     const size_type n = p_a.rows();
//     if (n != rhs.rows()) {
//         throw util::error("rhs of wrong size", "algorithm:lup");
//     }
//     if (x.rows() != n) {
//         x.allocate(n);
//     }

//     // 1. Forward pass
//     T sum;
//     for (size_type i = 0; i < n; ++i) {
//         sum = T(0);
//         for (size_type j = 0; j < i; ++j) {
//             sum += p_a(p_p(i), +j) * x(j);
//         }
//         x(i) = rhs(p_p(i)) - sum;
//     }

//     // 2. Backward pass
//     for (signed_size_type i = signed_size_type(n - 1); i >= 0; --i) {
//         sum = T(0);
//         for (size_type j = size_type(i + 1); j < n; ++j) {
//             sum += p_a(p_p(i), j) * x(j);
//         }
//         x(i) = (x(i) - sum) / p_a(p_p(i), i);
//     }
// }

// template <typename T, storage_type StorageT>
// vector<T> lu_decomposition<T, StorageT>::solve(const vector<T> &rhs)
// {
//     vector<T> x(0);
//     solve(x, rhs);
//     return x;
// }

} // namespace algorithm
} // namespace la
#endif
